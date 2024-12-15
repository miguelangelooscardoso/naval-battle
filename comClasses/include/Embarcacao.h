#ifndef EMBARCACAO_H
#define EMBARCACAO_H

// #include <vector>

class Embarcacao
{
public:
    char tipo;   // tipo de embarcação (letra)
    int tamanho; // tamanho da embarcação (número)
    int quantidade;

public:
    Embarcacao(char tipo, int tamanho, int quantidade); // construtor
    void inicializarEmbarcacoes(Embarcacao *embarcacao);
};
#endif