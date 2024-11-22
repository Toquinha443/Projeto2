#ifndef JOGADORCOMPUTADOR_H
#define JOGADORCOMPUTADOR_H

#include "Jogador.h"
#include "Tabuleiro.h"
#include <iostream>

class JogadorComputador : public Jogador {
private:
    // Variável para armazenar a última jogada
    std::pair<int, int> ultimaJogada;

public:
    JogadorComputador(const std::string& nome, char simbolo) : Jogador(nome, simbolo), ultimaJogada(-1, -1) {}

    void jogar() override {
        // Método virtual não usado diretamente
    }

    void jogarAutomaticamente(Tabuleiro& tabuleiro) {
        // 1. Tenta vencer
        if (fazerJogadaInteligente(tabuleiro, simbolo)) return;

        // 2. Tenta bloquear o oponente
        char oponente = (simbolo == 'X') ? 'O' : 'X';
        if (fazerJogadaInteligente(tabuleiro, oponente)) return;

        // 3. Joga no centro se estiver disponível
        if (tabuleiro.fazerJogada(1, 1, simbolo)) {
            ultimaJogada = {1, 1};  // Atualiza a última jogada
            std::cout << nome << " jogou no centro (1, 1).\n";
            return;
        }

        // 4. Joga em qualquer posição disponível (aleatório)
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (tabuleiro.fazerJogada(i, j, simbolo)) {
                    ultimaJogada = {i, j};  // Atualiza a última jogada
                    std::cout << nome << " jogou na posição (" << i << ", " << j << ").\n";
                    return;
                }
            }
        }
    }

    // Método para obter a última jogada
    std::pair<int, int> getUltimaJogada() const {
        return ultimaJogada;
    }

private:
    // Verifica se pode vencer ou bloquear
    bool fazerJogadaInteligente(Tabuleiro& tabuleiro, char jogador) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (tabuleiro.testeJogada(i, j, jogador)) {
                    tabuleiro.fazerJogada(i, j, simbolo);
                    ultimaJogada = {i, j};  // Atualiza a última jogada
                    std::cout << nome << " jogou inteligentemente na posição (" << i << ", " << j << ").\n";
                    return true;
                }
            }
        }
        return false;
    }
};

#endif
