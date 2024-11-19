#ifndef JOGO_H
#define JOGO_H

#include "Jogador.h"
#include "Tabuleiro.h"
#include <fstream>
#include <vector>
#include <iostream>

class Jogo {
private:
    Tabuleiro tabuleiro;
    std::vector<Jogador*> jogadores;
    std::ofstream log;

public:
    Jogo(Jogador* jogador1, Jogador* jogador2) {
        jogadores.push_back(jogador1);
        jogadores.push_back(jogador2);
        log.open("log.txt", std::ios::out);
        if (!log.is_open()) {
            throw std::runtime_error("Erro ao abrir o arquivo de log.");
        }
    }

    ~Jogo() {
        log.close();
        for (auto jogador : jogadores) {
            delete jogador;
        }
    }

    void jogar() {
        int rodada = 0;
        while (true) {
            tabuleiro.exibir();
            Jogador* jogadorAtual = jogadores[rodada % 2];

            if (JogadorComputador* computador = dynamic_cast<JogadorComputador*>(jogadorAtual)) {
                // Jogada automática do computador
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

            if (tabuleiro.verificarVitoria(jogadorAtual->getSimbolo())) {
                tabuleiro.exibir();
                std::cout << jogadorAtual->getNome() << " venceu!\n";
                log << jogadorAtual->getNome() << " venceu o jogo.\n";
                break;
            }
            rodada++;
        }
    }
};

#endif
