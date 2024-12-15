// #include "Jogador.h"
#include "../include/Jogador.h"
#include <iostream>
#include <sstream>   // to use stringstream
#include <windows.h> // adicionar som e cor

Jogador::Jogador(std::string nome)
{
    this->nome = nome;
    inicializarMatriz(this->tabuleiro);
    inicializarMatriz(this->tentativas);
    this->numeroJogadas = 0;
    this->pontos = 0;
    this->ativo = false;
}

void Jogador::definirCor(int cor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

void Jogador::inicializarMatriz(char matriz[LINHAS][COLUNAS]) // tabuleiro ou tentativas
{

    for (int i = 0; i < LINHAS; i++) // linhas
    {
        for (int j = 0; j < COLUNAS; j++) // colunas
        {
            matriz[i][j] = ' ';
        }
    }
}

void Jogador::imprimir(char tabuleiro[LINHAS][COLUNAS], char tentativas[LINHAS][COLUNAS])
{

    definirCor(14);
    // tentativas e tabuleiro lado a lado
    for (int k = 0; k < COLUNAS; k++)
    {
        std::cout << "[" << k + 1 << "]"; // numeração da matriz tabuleiro
    }
    std::cout << "     "; // espaço entre os índices dois tabuleiros (espaço entre [10] e [1])
    for (int k = 0; k < COLUNAS; k++)
    {
        std::cout << "[" << k + 1 << "]"; // numeração da matriz tentativas
    }
    std::cout << std::endl;

    definirCor(7);
    for (int i = 0; i < LINHAS; i++) // imprime ambos os tabuleiroe tentativas linha a linha
    {

        for (int j = 0; j < COLUNAS; j++) // tabuleiro
        {
            // cout << "[" << tabuleiro[i][j] << "]";
            std::cout << "[";
            if (tabuleiro[i][j] == 'X')
            {
                definirCor(12); // vermelho se 'X'
            }
            else if (tabuleiro[i][j] == '~')
            {
                definirCor(11); // azul aqua
            }

            std::cout << tabuleiro[i][j];
            definirCor(7);
            std::cout << "]";
        }

        definirCor(14);
        std::cout << "[" << char('A' + i) << "]"; // imprime a letra correspondente à linha do primeiro tabuleiro (letra A-J)
        definirCor(7);
        std::cout << "   "; // espaço entre tabuleiro e tenativas

        for (int j = 0; j < COLUNAS; j++) // tentativas
        {

            std::cout << "[";
            if (tentativas[i][j] == 'O')
            {
                definirCor(12); // vermelho se 'O'
            }
            else
            {
                definirCor(10); // verde se A, B, C, D, E
            }

            std::cout << tentativas[i][j];
            definirCor(7);
            std::cout << "]";
        }
        definirCor(14);
        std::cout << "[" << char('A' + i) << "]" << std::endl; // imprime a letra correspondente à linha do primeiro tabuleiro (letra A-J)
        definirCor(7);
    }
    std::cout << "\tAs suas embarcações: \t\tAs suas tentativas:" << std::endl;
}

bool Jogador::inserirTentativas(Jogador *jogador)
{
    std::string entrada;
    char bra1, ket1, bra2, ket2, letra;
    int numero;

    bool jogarNovamente = false; // regra geral

    // std::cout << "\tIntroduza a sua tentativa na forma [letra][número]." << std::endl;
    std::cout << "\tIntroduza a sua tentativa na forma LetraNúmero." << std::endl;
    std::cout << "\t>";
    getline(std::cin, entrada);

    if (entrada == "q")
    {
        std::cout << "Saiu do jogo." << std::endl;
        exit(0);
    }

    std::stringstream processarEntrada(entrada); // processa o formato de entrada
    // processarEntrada >> bra1 >> letra >> ket1 >> bra2 >> numero >> ket2;
    processarEntrada >> letra >> numero;

    // cout << "Número Inserido: " << numero << endl;

    if (processarEntrada.fail())
    {
        std::cout << "\tO processamento do formato de entrada falhou." << std::endl;
    }
    // else if (bra1 != '[' || ket1 != ']' || bra2 != '[' || ket2 != ']')
    // {
    //     std::cout << "\tFormato incorreto. Tente novamente." << std::endl;
    // }

    if (letra >= 'A' && letra <= 'J' && numero >= 1 && numero <= 10)
    {
        // procurar indice da letra e do número
        int indiceLinha = letra - 'A';
        int indiceColuna = numero - 1;

        if (jogador->tentativas[indiceLinha][indiceColuna] == ' ')
        {
            if (jogador->tabuleiro[indiceLinha][indiceColuna] != ' ')
            {
                jogador->tentativas[indiceLinha][indiceColuna] = jogador->tabuleiro[indiceLinha][indiceColuna]; // 1
                jogador->tabuleiro[indiceLinha][indiceColuna] = 'X';
                // Beep(400, 100); // 400 Hz for 100 milliseconds
                jogador->pontos++;
                jogarNovamente = true;
                PlaySound(TEXT("audio/hit.wav"), NULL, SND_FILENAME); // só estou a conseguir colocar este som síncrono.
            }
            else
            {
                jogador->tentativas[indiceLinha][indiceColuna] = 'O'; // 0
                jogador->tabuleiro[indiceLinha][indiceColuna] = '~';
                jogarNovamente = false;
                PlaySound(TEXT("audio/miss.wav"), NULL, SND_FILENAME);
            }

            PlaySound(TEXT("audio/background.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            jogador->numeroJogadas++;
        }
        else
        {
            std::cout << "\tJogada repetida, tente outra." << std::endl;
            jogarNovamente = true;
        }
    }
    else
    {
        std::cout << "\tDeve escolher uma letra de A-H e um número de 1-10" << std::endl;
        jogarNovamente = true;
    }

    return jogarNovamente;
}

bool Jogador::tentativasComputador(Jogador *computador)
{
    char letra;
    int numero;
    bool jogarNovamente = true;
    bool jogadaValida = false;

    srand(time(0));
    do
    {
        letra = 'A' + rand() % 10; // Gera letra aleatória de [A-J]
        numero = rand() % 10 + 1;  // Gera número aleatório de [1-10]

        int indiceLinha = letra - 'A'; // Converte letra em índice [0-9]
        int indiceColuna = numero - 1; // Converte número em índice [0-9]

        if (indiceLinha >= 0 && indiceLinha < 10 && indiceColuna >= 0 && indiceColuna < 10)
        {
            if (computador->tentativas[indiceLinha][indiceColuna] == ' ')
            {
                if (computador->tabuleiro[indiceLinha][indiceColuna] != ' ')
                {
                    computador->tentativas[indiceLinha][indiceColuna] = computador->tabuleiro[indiceLinha][indiceColuna];
                    computador->tabuleiro[indiceLinha][indiceColuna] = 'X';
                    computador->pontos++;
                    PlaySound(TEXT("audio/hit.wav"), NULL, SND_FILENAME);
                    return true;
                }
                else
                {
                    computador->tentativas[indiceLinha][indiceColuna] = 'O';
                    computador->tabuleiro[indiceLinha][indiceColuna] = '~';
                    PlaySound(TEXT("audio/miss.wav"), NULL, SND_FILENAME);
                    return false;
                }
                // PlaySound(TEXT("audio/background.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            }
        }
    } while (false);
    return false;
}

void Jogador::turnoJogador(Jogador *jogador, Jogador *oponente, bool *jogarNovamente, bool isComputer)
{
    if (isComputer)
    {
        std::cout << "\t\t\tÉ a sua vez do ";
        definirCor(1);
        std::cout << "Computador"; // jogador->nome;
        definirCor(7);
        std::cout << "!" << std::endl;
        imprimir(oponente->tabuleiro, jogador->tentativas);
        *jogarNovamente = tentativasComputador(jogador);
        PlaySound(TEXT("audio/background.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); // tenho que colocar som aqui após computador jogar
        // cout << "Jogar Novamente? " << (jogarNovamente ? "true" : "false") << endl;
        system("cls");
        imprimir(oponente->tabuleiro, jogador->tentativas);
        std::cout << "\tJogador 1: " << jogador->pontos << " pontos\t\tComputador: " << oponente->pontos << " pontos." << std::endl;
    }
    else
    {
        std::cout << "\t\t\tÉ a sua vez do ";
        definirCor(1);
        std::cout << jogador->nome;
        definirCor(7);
        std::cout << "!" << std::endl;
        imprimir(oponente->tabuleiro, jogador->tentativas);
        *jogarNovamente = inserirTentativas(jogador);
        // cout << "Jogar Novamente? " << (jogarNovamente ? "true" : "false") << endl;
        system("cls");
        imprimir(oponente->tabuleiro, jogador->tentativas);
        std::cout << "\tJogador 1: " << jogador->pontos << " pontos\t\tJogador 2: " << oponente->pontos << " pontos." << std::endl;
    }

    if (!*jogarNovamente)
    {
        jogador->ativo = false;
        oponente->ativo = true;
    }

    std::cout << "\tNúmero de Jogadas Jogador 1: " << jogador->numeroJogadas << std::endl;

    verificarVitoria(jogador, oponente);
}

void Jogador::verificarVitoria(Jogador *jogador, Jogador *oponente)
{
    if (jogador->pontos == 25)
    {
        std::cout << "\t" << jogador->nome << " won!" << std::endl;
        exit(0);
    }

    if (oponente->pontos == 25)
    {
        std::cout << "\t" << oponente->nome << " won!" << std::endl;
        exit(0);
    }
}
