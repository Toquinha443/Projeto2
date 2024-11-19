#include "../headers/JogadorComputador.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void JogadorComputador::jogar() {
    srand(time(0));
    int linha = rand() % 3;
    int coluna = rand() % 3;
    std::cout << nome << " jogou na posição (" << linha << ", " << coluna << ").\n";
}
