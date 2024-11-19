#ifndef JOGADORCOMPUTADOR_H
#define JOGADORCOMPUTADOR_H

#include "Jogador.h"
#include "Tabuleiro.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class JogadorComputador : public Jogador {
public:
    JogadorComputador(const std::string& nome, char simbolo) : Jogador(nome, simbolo) {
        srand(time(0));
    }

    void jogar() override {
        // Este método não é usado diretamente, mas é necessário devido ao polimorfismo.
    }

    void jogarAutomaticamente(Tabuleiro& tabuleiro) {
        int linha, coluna;
        while (true) {
            linha = rand() % 3;
            coluna = rand() % 3;
            if (tabuleiro.fazerJogada(linha, coluna, simbolo)) {
                std::cout << nome << " jogou automaticamente na posição (" << linha << ", " << coluna << ")\n";
                break;
            }
        }
    }
};

#endif
