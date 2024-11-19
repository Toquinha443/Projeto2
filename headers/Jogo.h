#ifndef JOGO_H
#define JOGO_H

#include "Jogador.h"
#include "Tabuleiro.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <queue> 

class Jogo {
private:
    Tabuleiro tabuleiro;                       // Tabuleiro do jogo
    std::vector<Jogador*> jogadores;           // Vetor de jogadores (humanos ou computador)
    std::ofstream log;                         // Arquivo para registrar o log do jogo
    std::vector<std::queue<std::pair<int, int>>> jogadasPorJogador; // Fila de jogadas para cada jogador

public:
    Jogo(Jogador* jogador1, Jogador* jogador2) {
        // Adiciona os jogadores ao vetor
        jogadores.push_back(jogador1);
        jogadores.push_back(jogador2);
        jogadasPorJogador.resize(2); // Inicializa uma fila para cada jogador

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

        // Inicializa o vetor de filas para rastrear as jogadas de cada jogador
        while (true) {
            // Exibe o tabuleiro
            tabuleiro.exibir();

            // Alterna entre os jogadores (rodada % 2)
            Jogador* jogadorAtual = jogadores[rodada % 2];
            int indiceJogador = rodada % 2;

            // Verifica se o jogador atual é um computador
            if (JogadorComputador* computador = dynamic_cast<JogadorComputador*>(jogadorAtual)) {
                computador->jogarAutomaticamente(tabuleiro);
                log << "Rodada " << rodada + 1 << ": " << computador->getNome()
                    << " jogou automaticamente com '" << computador->getSimbolo() << "'\n";
                
                // Se o computador já tiver 3 peças, remove a mais antiga
                if (jogadasPorJogador[indiceJogador].size() == 3) {
                    auto jogadaMaisAntiga = jogadasPorJogador[indiceJogador].front();
                    jogadasPorJogador[indiceJogador].pop(); // Remove a mais antiga da fila
                    tabuleiro.removerPeca(jogadaMaisAntiga.first, jogadaMaisAntiga.second); // Remove do tabuleiro
                }

                // Adiciona a nova jogada à fila do computador
                auto ultimaJogada = computador->getUltimaJogada(); // Assumindo que a última jogada foi salva no computador
                jogadasPorJogador[indiceJogador].push(ultimaJogada);
            } else {
                // Jogada do jogador humano
                while (true) {
                    std::cout << jogadorAtual->getNome() << " (" << jogadorAtual->getSimbolo() << ") jogue:\n";
                    int linha, coluna;
                    std::cin >> linha >> coluna;

                    // Verifica se a jogada é válida
                    if (tabuleiro.fazerJogada(linha, coluna, jogadorAtual->getSimbolo())) {
                        // Registra a jogada no log
                        log << "Rodada " << rodada + 1 << ": " << jogadorAtual->getNome()
                            << " jogou em (" << linha << ", " << coluna << ") com '" << jogadorAtual->getSimbolo() << "'\n";

                        // Se o jogador já tiver 3 peças, remove a mais antiga
                        if (jogadasPorJogador[indiceJogador].size() == 3) {
                            auto jogadaMaisAntiga = jogadasPorJogador[indiceJogador].front();
                            jogadasPorJogador[indiceJogador].pop(); // Remove a mais antiga da fila
                            tabuleiro.removerPeca(jogadaMaisAntiga.first, jogadaMaisAntiga.second); // Remove do tabuleiro
                        }

                        // Adiciona a nova jogada à fila
                        jogadasPorJogador[indiceJogador].push({linha, coluna});
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
            // if (tabuleiro.verificarEmpateImediato()) {
            //     tabuleiro.exibir();
            //     std::cout << "Empate! Reiniciando o tabuleiro...\n";
            //     log << "Empate! Reiniciando o tabuleiro...\n";
            //     tabuleiro = Tabuleiro(); // Reinicia o tabuleiro
            //     rodada = -1;             // Redefine a rodada (próxima será 0)
            // }

            rodada++;
        }
}

};

#endif
