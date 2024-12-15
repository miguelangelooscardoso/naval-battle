#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>

#define LINHAS 10
#define COLUNAS 10

class Jogador
{
public:
    std::string nome;
    char tabuleiro[LINHAS][COLUNAS];
    char tentativas[LINHAS][COLUNAS];
    int numeroJogadas;
    int pontos; // número de acertos
    bool ativo;

public:
    Jogador(std::string nome); // construtor

    void definirCor(int color);
    void inicializarMatriz(char matriz[LINHAS][COLUNAS]);
    void imprimir(char tabuleiro[LINHAS][COLUNAS], char tentativas[LINHAS][COLUNAS]);
    bool inserirTentativas(Jogador *jogador);
    bool tentativasComputador(Jogador *computador);
    void turnoJogador(Jogador *jogador, Jogador *oponente, bool *jogarNovamente, bool isComputer);
    void verificarVitoria(Jogador *jogador, Jogador *oponente);
};

#endif