#include "../headers/JogadorHumano.h"
#include "../headers/JogadorComputador.h"
#include "../headers/Jogo.h"
#include <iostream>

int main() {
    // Configuração dos jogadores
    Jogador* jogador1 = new JogadorHumano("Jogador 1", 'X');
    Jogador* jogador2 = new JogadorComputador("Computador", 'O');

    // Criação e execução do jogo
    try {
        Jogo jogo(jogador1, jogador2);
        jogo.jogar();
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << "\n";
    }

    return 0;
}
