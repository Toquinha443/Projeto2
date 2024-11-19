#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>

class Jogador {
protected:
    std::string nome;
    char simbolo;

public:
    Jogador(const std::string& nome, char simbolo) : nome(nome), simbolo(simbolo) {}
    virtual ~Jogador() = default;

    std::string getNome() const { return nome; }
    char getSimbolo() const { return simbolo; }

    virtual void jogar() = 0; // Método virtual puro
};

#endif
