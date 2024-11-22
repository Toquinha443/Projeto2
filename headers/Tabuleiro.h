#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <iostream>
#include <vector>
#include <utility>

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
        jogadas.clear(); // Limpa o histórico de jogadas
    }

    void exibir() const {
        // Exibe o tabuleiro no console com estilo
        std::cout << "\033[1;36m"; // Cor ciano brilhante
        std::cout << "\n    0   1   2\n"; // Índices das colunas
        std::cout << "  -------------\n";
        for (int i = 0; i < 3; ++i) {
            std::cout << i << " | "; // Índice da linha
            for (int j = 0; j < 3; ++j) {
                // Exibe os símbolos com cores diferentes
                if (grid[i][j] == 'X') {
                    std::cout << "\033[1;31mX"; // Cor vermelha brilhante
                } else if (grid[i][j] == 'O') {
                    std::cout << "\033[1;34mO"; // Cor azul brilhante
                } else {
                    std::cout << " ";
                }
                std::cout << "\033[1;36m"; // Restaura a cor padrão
                std::cout << (j < 2 ? " | " : " "); // Separadores
            }
            std::cout << "\n  -------------\n";
        }
        std::cout << "\033[0m"; // Restaura as cores padrão do terminal
    }

    bool fazerJogada(int linha, int coluna, char simbolo) {
        if (linha < 0 || linha >= 3 || coluna < 0 || coluna >= 3 || grid[linha][coluna] != ' ') {
            return false;
        }
        grid[linha][coluna] = simbolo;
        jogadas.emplace_back(linha, coluna);
        return true;
    }

    bool verificarVitoria(char simbolo) const {
        for (int i = 0; i < 3; ++i) {
            if ((grid[i][0] == simbolo && grid[i][1] == simbolo && grid[i][2] == simbolo) ||
                (grid[0][i] == simbolo && grid[1][i] == simbolo && grid[2][i] == simbolo)) {
                return true;
            }
        }
        return (grid[0][0] == simbolo && grid[1][1] == simbolo && grid[2][2] == simbolo) ||
               (grid[0][2] == simbolo && grid[1][1] == simbolo && grid[2][0] == simbolo);
    }

    bool verificarEmpateImediato() {
        if (jogadas.size() < 8) {
            return false;
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[i][j] == ' ') {
                    if (testeJogada(i, j, 'X') || testeJogada(i, j, 'O')) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool testeJogada(int linha, int coluna, char simbolo) {
        if (linha < 0 || linha >= 3 || coluna < 0 || coluna >= 3 || grid[linha][coluna] != ' ') {
            return false;
        }
        grid[linha][coluna] = simbolo;
        bool resultado = verificarVitoria(simbolo);
        grid[linha][coluna] = ' ';
        return resultado;
    }
};

#endif
