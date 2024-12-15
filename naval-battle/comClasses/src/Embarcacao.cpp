#include "../include/Embarcacao.h"
// #include <vector>

Embarcacao::Embarcacao(char tipo, int tamanho, int quantidade)
{
    this->tipo = tipo;
    this->tamanho = tamanho;
    this->quantidade = quantidade;
}

void Embarcacao::inicializarEmbarcacoes(Embarcacao *embarcacao)
{
    // manter apenas a declaração de vetor como vector<Embarcacao>,
    // já que está usando a classe vector (do C++ STL) para armazenar as embarcações.

    // vector<Embarcacao> embarcacoes = {
    //     Embarcacao('A', 5, 1),
    //     Embarcacao('B', 4, 2),
    //     Embarcacao('C', 3, 3),
    //     Embarcacao('D', 2, 4),
    //     Embarcacao('E', 1, 5)
    // };

    // int tamanho[] = {5, 4, 3, 2, 1};          // acorvado, cruzador, contratorpedeiro, submarino, patrulha
    // int quantidade[] = {1, 1, 2, 3, 4};       // acorvado, cruzador, contratorpedeiro, submarino, patrulha
    // char letra[] = {'A', 'B', 'C', 'D', 'E'}; // acorvado, cruzador, contratorpedeiro, submarino, patrulha

    // int total = 0;
    // for (int i = 0; i < size(tamanho); i++)
    // {
    //     total += tamanho[i] * quantidade[i];
    // }
    // cout << size(tamanho) << endl; // tamanho do vetor
    // cout << total << endl;         // 25 alvos possíveis out of 100!

    // EMBARCACAO embarcacoes[5] = {
    //     {'A', 5, 1}, // Acorvado
    //     {'B', 4, 1}, // Cruzador
    //     {'C', 3, 2}, // Contratorpedeiro
    //     {'D', 2, 3}, // Submarino
    //     {'E', 1, 4}  // Patrulha
    // };

    embarcacao[0] = {'A', 5, 1}; // A - Acorvado (tamanho 5)
    embarcacao[1] = {'B', 4, 1}; // B - Cruzador (tamanho 4)
    embarcacao[2] = {'C', 3, 2}; // C - Contratorpedeiro (tamanho 3, quantidade 2)
    embarcacao[3] = {'D', 2, 3}; // D - Submarino (tamanho 2, quantidade 3)
    embarcacao[4] = {'E', 1, 4}; // E - Patrulha (tamanho 1, quantidade 4)
}
