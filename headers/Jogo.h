#ifndef JOGO_H
#define JOGO_H

#include "Jogador.h"
#include "Tabuleiro.h"
#include <fstream>
#include <vector>
#include <iostream>

class Jogo {
private:
    Tabuleiro tabuleiro;                       // Tabuleiro do jogo
    std::vector<Jogador*> jogadores;           // Vetor de jogadores (humanos ou computador)
    std::ofstream log;                         // Arquivo para registrar o log do jogo

public:
    Jogo(Jogador* jogador1, Jogador* jogador2) {
        // Adiciona os jogadores ao vetor
        jogadores.push_back(jogador1);
        jogadores.push_back(jogador2);

        // Abre o arquivo de log
        log.open("log.txt", std::ios::out);
        if (!log.is_open()) {
            throw std::runtime_error("Erro ao abrir o arquivo de log.");
        }
    }

    ~Jogo() {
        log.close(); // Fecha o log ao final do jogo
        for (auto jogador : jogadores) {
            delete jogador; // Libera a memória dos jogadores
        }
    }

    void jogar() {
        int rodada = 0;
        while (true) {
            // Exibe o tabuleiro
            tabuleiro.exibir();

            // Alterna entre os jogadores (rodada % 2)
            Jogador* jogadorAtual = jogadores[rodada % 2];

            // Verifica se o jogador atual é um computador
            if (JogadorComputador* computador = dynamic_cast<JogadorComputador*>(jogadorAtual)) {
                computador->jogarAutomaticamente(tabuleiro);
                log << "Rodada " << rodada + 1 << ": " << computador->getNome()
                    << " jogou automaticamente com '" << computador->getSimbolo() << "'\n";
            } else {
                // Jogada do jogador humano
                while (true) {
                    std::cout << jogadorAtual->getNome() << " (" << jogadorAtual->getSimbolo() << ") jogue:\n";
                    int linha, coluna;
                    std::cin >> linha >> coluna;

                    if (tabuleiro.fazerJogada(linha, coluna, jogadorAtual->getSimbolo())) {
                        log << "Rodada " << rodada + 1 << ": " << jogadorAtual->getNome()
                            << " jogou em (" << linha << ", " << coluna << ") com '" << jogadorAtual->getSimbolo() << "'\n";
                        break;
                    } else {
                        std::cout << "Jogada inválida! Tente novamente.\n";
                    }
                }
            }

            // Verifica se houve vitória
            if (tabuleiro.verificarVitoria(jogadorAtual->getSimbolo())) {
                tabuleiro.exibir();
                std::cout << jogadorAtual->getNome() << " venceu!\n";
                log << jogadorAtual->getNome() << " venceu o jogo.\n";
                break;
            }

            // Verifica se há empate imediato
            if (tabuleiro.verificarEmpateImediato()) {
                tabuleiro.exibir();
                std::cout << "Empate! Reiniciando o tabuleiro...\n";
                log << "Empate! Reiniciando o tabuleiro...\n";
                tabuleiro = Tabuleiro(); // Reinicia o tabuleiro
                rodada = -1;             // Redefine a rodada (próxima será 0)
            }

            rodada++;
        }
    }
};

#endif
