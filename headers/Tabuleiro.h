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
        // Verifica se a posição é válida e está vazia
        if (linha < 0 || linha >= 3 || coluna < 0 || coluna >= 3 || grid[linha][coluna] != ' ') {
            return false; // Jogada inválida
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

    bool testeJogada(int linha, int coluna, char simbolo) {
        // Verifica se a posição é válida
        if (linha < 0 || linha >= 3 || coluna < 0 || coluna >= 3 || grid[linha][coluna] != ' ') {
            return false;
        }

        // Faz a jogada temporariamente
        grid[linha][coluna] = simbolo;

        // Verifica se a jogada resultaria em vitória
        bool resultado = verificarVitoria(simbolo);

        // Reverte a jogada (volta o tabuleiro ao estado original)
        grid[linha][coluna] = ' ';
        return resultado;
    }

    bool verificarEmpateImediato() {
        // O empate só pode ser validado se houver pelo menos 8 jogadas feitas
        if (jogadas.size() < 8) {
            return false; // Não é possível determinar empate com menos de 8 jogadas
        }

        // Verifica se ainda existem jogadas que podem levar a uma vitória
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[i][j] == ' ') { // Posição vazia
                    // Testa a jogada para cada jogador ('X' e 'O')
                    if (testeJogada(i, j, 'X') || testeJogada(i, j, 'O')) {
                        return false; // Ainda há uma jogada que pode levar à vitória
                    }
                }
            }
        }

        return true; // Não há mais jogadas que podem levar à vitória
    }

    void removerPeca(int linha, int coluna) {
        if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3) {
            grid[linha][coluna] = ' '; // Limpa a posição no tabuleiro
        }
    }
};

#endif
