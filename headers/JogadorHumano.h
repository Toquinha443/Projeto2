#ifndef JOGADORHUMANO_H
#define JOGADORHUMANO_H

#include "Jogador.h"
#include <iostream>

class JogadorHumano : public Jogador {
public:
    JogadorHumano(const std::string& nome, char simbolo) : Jogador(nome, simbolo) {}
    void jogar() override {
        std::cout << nome << " é um jogador humano.\n";
    }
};

#endif
