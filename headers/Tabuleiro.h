#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <iostream>
#include <vector>
#include <utility> // Necessário para std::pair

class Tabuleiro {
private:
    char grid[3][3]; // Representa o tabuleiro 3x3
    std::vector<std::pair<int, int>> jogadas; // Histórico de jogadas (linha, coluna)

public:
    Tabuleiro() {
        // Inicializa o tabuleiro com espaços vazios
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                grid[i][j] = ' ';
            }
        }
    }

    void exibir() const {
        // Exibe o tabuleiro no console
        std::cout << "\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << grid[i][j] << (j < 2 ? " | " : "");
            }
            std::cout << "\n";
            if (i < 2) {
                std::cout << "---------\n";
            }
        }
        std::cout << "\n";
    }

    bool fazerJogada(int linha, int coluna, char simbolo) {
        // Verifica se a posição é válida e está vazia
        if (linha < 0 || linha >= 3 || coluna < 0 || coluna >= 3 || grid[linha][coluna] != ' ') {
            return false; // Jogada inválida
        }

        // Se o tabuleiro estiver cheio, remove a jogada mais antiga
        if (jogadas.size() == 9) {
            std::pair<int, int> jogadaAntiga = jogadas.front(); // Obtém a jogada mais antiga
            int linhaAntiga = jogadaAntiga.first;
            int colunaAntiga = jogadaAntiga.second;

            grid[linhaAntiga][colunaAntiga] = ' '; // Remove o símbolo mais antigo
            jogadas.erase(jogadas.begin()); // Remove a jogada do histórico
        }

        // Registra a nova jogada
        grid[linha][coluna] = simbolo;
        jogadas.emplace_back(linha, coluna); // Adiciona ao histórico de jogadas
        return true;
    }

    bool verificarVitoria(char simbolo) const {
        // Verifica linhas e colunas
        for (int i = 0; i < 3; ++i) {
            if ((grid[i][0] == simbolo && grid[i][1] == simbolo && grid[i][2] == simbolo) ||
                (grid[0][i] == simbolo && grid[1][i] == simbolo && grid[2][i] == simbolo)) {
                return true;
            }
        }

        // Verifica diagonais
        return (grid[0][0] == simbolo && grid[1][1] == simbolo && grid[2][2] == simbolo) ||
               (grid[0][2] == simbolo && grid[1][1] == simbolo && grid[2][0] == simbolo);
    }
};

#endif
