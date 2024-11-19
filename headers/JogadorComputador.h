#ifndef JOGADORCOMPUTADOR_H
#define JOGADORCOMPUTADOR_H

#include "Jogador.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class JogadorComputador : public Jogador {
public:
    JogadorComputador(const std::string& nome, char simbolo) : Jogador(nome, simbolo) {}
    void jogar() override {
        srand(time(0));
        int linha = rand() % 3;
        int coluna = rand() % 3;
        std::cout << nome << " jogou na posição (" << linha << ", " << coluna << ").\n";
    }
};

#endif
