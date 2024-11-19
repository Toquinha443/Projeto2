#include "./headers/JogadorHumano.h"
#include "./headers/JogadorComputador.h"
#include "./headers/Jogo.h"
#include <iostream>
#include <string>

// Função para exibir o menu inicial
void exibirMenu() {
    std::cout << "=====================\n";
    std::cout << "       MENU          \n";
    std::cout << "=====================\n";
    std::cout << "1. Single Player\n";
    std::cout << "2. Multiplayer\n";
    std::cout << "3. Como jogar\n";
    std::cout << "4. Sair\n";
    std::cout << "=====================\n";
    std::cout << "Escolha uma opção: ";
}

// Função para exibir as instruções de "Como jogar"
void exibirComoJogar() {
    std::cout << "\n===== COMO JOGAR =====\n";
    std::cout << "Este é um jogo da velha modificado. Cada jogador tem 3 peças.\n";
    std::cout << "O objetivo é formar uma linha de três peças em sequência horizontal,\n";
    std::cout << "vertical ou diagonal.\n";
    std::cout << "\n- Cada jogador pode colocar no máximo 3 peças no tabuleiro.\n";
    std::cout << "- Quando o jogador tenta colocar uma peça além de 3, a peça mais antiga\n";
    std::cout << "  será removida para dar lugar à nova.\n";
    std::cout << "\nPara jogar, insira as coordenadas da linha e da coluna.\n";
    std::cout << "=======================\n\n";
}

// Função principal
int main() {
    int opcao = 0;

    do {
        exibirMenu();
        std::cin >> opcao;

        switch (opcao) {
        case 1: {
            std::cout << "\nIniciando Single Player...\n";
            Jogador* jogador1 = new JogadorHumano("Jogador 1", 'X');
            Jogador* jogador2 = new JogadorComputador("Computador", 'O');

            try {
                Jogo jogo(jogador1, jogador2);
                jogo.jogar();
            } catch (const std::exception& e) {
                std::cerr << "Erro: " << e.what() << "\n";
            }
            break;
        }
        case 2: {
            std::cout << "\nIniciando Multiplayer...\n";
            Jogador* jogador1 = new JogadorHumano("Jogador 1", 'X');
            Jogador* jogador2 = new JogadorHumano("Jogador 2", 'O');

            try {
                Jogo jogo(jogador1, jogador2);
                jogo.jogar();
            } catch (const std::exception& e) {
                std::cerr << "Erro: " << e.what() << "\n";
            }
            break;
        }
        case 3: {
            int voltar = 0;
            while (voltar != 1) {
                exibirComoJogar();
                std::cout << "Digite 1 para voltar ao menu principal: ";
                std::cin >> voltar;
                if (voltar != 1) {
                    std::cout << "Opção inválida! Digite 1 para voltar.\n";
                }
            }
            break;
        }
        case 4:
            std::cout << "Saindo do jogo. Até mais!\n";
            break;
        default:
            std::cout << "Opção inválida! Tente novamente.\n";
            break;
        }
    } while (opcao != 4);

    return 0;
}
