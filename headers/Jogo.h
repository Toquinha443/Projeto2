#ifndef JOGO_H
#define JOGO_H

#include "Jogador.h"
#include "Tabuleiro.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <queue>

class Jogo
{
private:
    Tabuleiro tabuleiro;                                            // Tabuleiro do jogo
    std::vector<Jogador *> jogadores;                               // Vetor de jogadores (humanos ou computador)
    std::ofstream log;                                              // Arquivo para registrar o log do jogo
    std::vector<std::queue<std::pair<int, int>>> jogadasPorJogador; // Fila de jogadas para cada jogador

public:
    Jogo(Jogador *jogador1, Jogador *jogador2)
    {
        // Adiciona os jogadores ao vetor
        jogadores.push_back(jogador1);
        jogadores.push_back(jogador2);
        jogadasPorJogador.resize(2); // Inicializa uma fila para cada jogador

        // Abre o arquivo de log
        log.open("log.txt", std::ios::out);
        if (!log.is_open())
        {
            throw std::runtime_error("Erro ao abrir o arquivo de log.");
        }
    }

    ~Jogo()
    {
        log.close(); // Fecha o log ao final do jogo
        for (auto jogador : jogadores)
        {
            delete jogador; // Libera a memória dos jogadores
        }
    }

    void jogar()
    {
        int rodada = 0;

        while (true)
        {
            tabuleiro.exibir();

            Jogador *jogadorAtual = jogadores[rodada % 2];
            int indiceJogador = rodada % 2;

            if (JogadorComputador *computador = dynamic_cast<JogadorComputador *>(jogadorAtual))
            {
                computador->jogarAutomaticamente(tabuleiro);
                log << "Rodada " << rodada + 1 << ": " << computador->getNome()
                    << " jogou automaticamente com '" << computador->getSimbolo() << "'\n";

                if (jogadasPorJogador[indiceJogador].size() == 3)
                {
                    auto jogadaMaisAntiga = jogadasPorJogador[indiceJogador].front();
                    jogadasPorJogador[indiceJogador].pop();
                    tabuleiro.removerPeca(jogadaMaisAntiga.first, jogadaMaisAntiga.second);
                }

                auto ultimaJogada = computador->getUltimaJogada();
                jogadasPorJogador[indiceJogador].push(ultimaJogada);
            }
            else
            {
                while (true)
                {
                    std::cout << "\033[1;32m" << jogadorAtual->getNome() << " (" << jogadorAtual->getSimbolo() << ") é a sua vez.\033[0m\n";
                    std::cout << "Digite a linha e a coluna para jogar: ";

                    int linha, coluna;
                    std::cin >> linha >> coluna;

                    if (tabuleiro.fazerJogada(linha, coluna, jogadorAtual->getSimbolo()))
                    {
                        log << "Rodada " << rodada + 1 << ": " << jogadorAtual->getNome()
                            << " jogou em (" << linha << ", " << coluna << ") com '" << jogadorAtual->getSimbolo() << "'\n";

                        if (jogadasPorJogador[indiceJogador].size() == 3)
                        {
                            auto jogadaMaisAntiga = jogadasPorJogador[indiceJogador].front();
                            jogadasPorJogador[indiceJogador].pop();
                            tabuleiro.removerPeca(jogadaMaisAntiga.first, jogadaMaisAntiga.second);
                        }

                        jogadasPorJogador[indiceJogador].push({linha, coluna});
                        break;
                    }
                    else
                    {
                        std::cout << "\033[1;31mJogada inválida! Tente novamente.\033[0m\n";
                    }
                }
            }

            if (tabuleiro.verificarVitoria(jogadorAtual->getSimbolo()))
            {
                tabuleiro.exibir();
                std::cout << "\033[1;33m" << jogadorAtual->getNome() << " venceu! Parabéns!\033[0m\n";
                log << jogadorAtual->getNome() << " venceu o jogo.\n";
                break;
            }

            rodada++;
        }
    }
};

#endif
