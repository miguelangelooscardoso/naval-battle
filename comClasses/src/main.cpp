#include "../include/Jogador.h"
#include "../include/Embarcacao.h"

#include <iostream>
#include <sstream> // to use stringstream
#include <locale>
// #include <vector>
#include <limits>    // std::numeric_limits
#include <windows.h> // adicionar som e cor

#define LINHAS 10
#define COLUNAS 10
#define TIPOS_DE_EMBARCACAO 5

void gerarEmbarcacoes(Embarcacao *embarcacao, char tabuleiro[LINHAS][COLUNAS])
{
    bool escritaPossivel;

    // Usando *embarcacoes para acessar o vetor
    for (int k = 0; k < TIPOS_DE_EMBARCACAO; k++) // para cada um das embarcações
    {
        for (int l = 0; l < (embarcacao + k)->quantidade; l++)
        {
            do
            {
                int xAleatorio = rand() % LINHAS;  // Linha aleatória
                int yAleatorio = rand() % COLUNAS; // Coluna aleatória

                int direcao = rand() % 2; // Direção aleatória (0 = horizontal, 1 = vertical)

                escritaPossivel = true;

                // Verifica se a embarcação cabe na posição aleatória
                for (int i = 0; i < (embarcacao)[k].tamanho; i++)
                { // Acesso ao vetor com ponteiro
                    if (direcao == 1)
                    { // vertical
                        if (xAleatorio + i >= LINHAS || tabuleiro[xAleatorio + i][yAleatorio] != ' ')
                        {
                            escritaPossivel = false;
                            break;
                        }
                    }
                    else
                    { // horizontal
                        if (yAleatorio + i >= COLUNAS || tabuleiro[xAleatorio][yAleatorio + i] != ' ')
                        {
                            escritaPossivel = false;
                            break;
                        }
                    }
                }

                // Se a posição for válida, coloca a embarcação no tabuleiro
                if (escritaPossivel)
                {
                    for (int j = 0; j < (embarcacao)[k].tamanho; j++)
                    { // Acesso ao vetor com ponteiro
                        if (direcao == 1)
                        { // vertical
                            tabuleiro[xAleatorio + j][yAleatorio] = (embarcacao)[k].tipo;
                        }
                        else
                        { // horizontal
                            tabuleiro[xAleatorio][yAleatorio + j] = (embarcacao)[k].tipo;
                        }
                    }
                }
            } while (!escritaPossivel); // Tenta novamente até encontrar uma posição válida
        }
    }
}

void jogo(Jogador *jogador1, Jogador *jogador2, Embarcacao *embarcacoes, bool isComputer) // para um único jogador
{

    jogador1->inicializarMatriz(jogador1->tabuleiro); // tabuleiro, jogador 1
    jogador2->inicializarMatriz(jogador2->tabuleiro); // tabuleiro, jogador 2

    jogador1->inicializarMatriz(jogador1->tentativas); // tentativas, jogador 1
    jogador1->inicializarMatriz(jogador2->tentativas); // tentativas, jogador 2

    // inicializarEmbarcacoes(embarcacoes);
    // embarcacoes[0] = {'A', 5, 1}; // Acorvado
    // embarcacoes[1] = {'B', 4, 1}; // Cruzador
    // embarcacoes[2] = {'C', 3, 2}; // Contratorpedeiro
    // embarcacoes[3] = {'D', 2, 3}; // Submarino
    // embarcacoes[4] = {'E', 1, 4}; // Patrulha

    gerarEmbarcacoes(embarcacoes, jogador1->tabuleiro); // embarcações, jogador 1
    gerarEmbarcacoes(embarcacoes, jogador2->tabuleiro); // embarcações, jogador2

    char c;
    bool jogarNovamente = true;
    jogador1->ativo = true;
    jogador2->ativo = false;

    while (true)
    {
        system("cls");

        if (jogador1->ativo)
        {
            jogador1->turnoJogador(jogador1, jogador2, &jogarNovamente, false);
        }
        else if (jogador2->ativo)
        {
            if (isComputer)
            {
                jogador2->turnoJogador(jogador2, jogador1, &jogarNovamente, true); // computador
            }
            else
            {
                jogador2->turnoJogador(jogador2, jogador1, &jogarNovamente, false); // jogador 2
            }
        }

        std::cout << "\tPressione 'Enter' para a ir para jogada seguinte." << std::endl;
        std::cout << "\t>";
        std::cin.ignore(); // Limpa o buffer de entrada
    }
}

void menu(Jogador *jogador1, Jogador *jogador2, Embarcacao *embarcacoes)
{
    int opcao;

    while (true)
    {
        if (std::cin.fail()) // precaver possíveis inputs inválidos
        {
            // std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Por favor, insira um número de 1 a 4." << std::endl;
            // continue;
        }

        system("cls");

        std::cout << "\t====================================" << std::endl;
        std::cout << "\t       *** Menu Principal ***" << std::endl;
        std::cout << "\t====================================" << std::endl;
        std::cout << "\t 1. Jogador vs. Jogador" << std::endl;
        std::cout << "\t 2. Jogador vs. Computador" << std::endl;
        std::cout << "\t 3. Ajuda" << std::endl;
        std::cout << "\t 4. Sair" << std::endl;
        std::cout << "\t====================================" << std::endl;
        std::cout << "\t Escolha uma opção (1-4): ";

        std::cin >> opcao;

        system("cls");

        switch (opcao)
        {
        case 1:
            jogo(jogador1, jogador2, embarcacoes, false);
            break;
        case 2:
            jogo(jogador1, jogador2, embarcacoes, true);
            break;
        case 3:
            std::cout << "\t========================================================================================================================= " << std::endl;
            std::cout << "\t                                                             *** Ajuda ***                                                " << std::endl;
            std::cout << "\t=========================================================================================================================" << std::endl;
            std::cout << std::endl;
            std::cout << "\t1. Afunde todas as embarcações inimigas do adversário e conquiste a vitória." << std::endl;
            std::cout << "\t2. O tabuleiro com as suas embarcações e tentativas do adversário aparecerá à direita." << std::endl;
            std::cout << "\t3. As suas tentativas aparecerão à esquerda, e é nesse tabuleiro que você deve selecionar onde pretende acertar." << std::endl;
            std::cout << "\t4. As embarcações, tanto do adversário quanto do jogador, são geradas automaticamente no início do jogo." << std::endl;
            std::cout << "\t5. Caso acerte numa embarcação do adversário, você terá a chance de jogar novamente." << std::endl;
            std::cout << "\t6. O jogo possui 5 tipos de embarcações:" << std::endl;
            std::cout << "\t   - Acorvado ('A') - 1 unidade, tamanho 5 (5 células)." << std::endl;
            std::cout << "\t   - Cruzador ('B') - 1 unidade, tamanho 4 (4 células)." << std::endl;
            std::cout << "\t   - Contratorpedeiro ('C') - 2 unidades, tamanho 3 (6 células no total)." << std::endl;
            std::cout << "\t   - Submarino ('D') - 3 unidades, tamanho 2 (6 células no total)." << std::endl;
            std::cout << "\t   - Patrulha ('E') - 4 unidades, tamanho 1 (4 células no total)." << std::endl;
            std::cout << "\t7. O número total de células ocupadas pelas embarcações é 25, sendo o tabuleiro 10x10 (100 células)." << std::endl;
            std::cout << "\t8. Ganha quem primeiro afundar todas as embarcações do adversário." << std::endl;
            std::cout << "\t========================================================================================================================= " << std::endl;
            std::cout << "\t Pressione Enter para voltar ao menu.                                                                                                              " << std::endl;
            std::cout << "\t=========================================================================================================================" << std::endl;
            std::cout << "\t>";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignora tudo antes do 'Enter'
            std::cin.get();                                                     // espera por pressionar 'Enter'
            break;
        case 4:
            std::cout << "Saiu do programa!" << std::endl;
            exit(0);
            break;
        default:
            std::cout << "Opção inválida. Escolha outra opção." << std::endl;
        }
    }
}

int main()
{

    // compilar com src e include:
    // g++ src/main.cpp src/Jogador.cpp src/Embarcacao.cpp -o main -Iinclude -lwinmm

    setlocale(LC_ALL, "pt_PT.UTF-8");
    srand(time(0)); // necessário para gerar um x,y aleatório

    // Sound during the execution of the entire game (https://stackoverflow.com/questions/19895468/background-music-in-c)!
    // Sounds from: https://sound-effects.bbcrewind.co.uk/
    // Backgroudn sound from https://www.youtube.com/watch?v=VReGLwDPMpE
    PlaySound(TEXT("audio/background.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); // compile as 'g++ main.cpp -o main -lwinmm'
    Jogador jogador1("Jogador 1");
    Jogador jogador2("Jogador 2");

    // vector<Embarcacao> embarcacoes;
    Embarcacao embarcacoes[TIPOS_DE_EMBARCACAO] = {
        Embarcacao('A', 5, 1), // Acorvado
        Embarcacao('B', 4, 1), // Cruzador
        Embarcacao('C', 3, 2), // Contratorpedeiro
        Embarcacao('D', 2, 3), // Submarino
        Embarcacao('E', 1, 4)  // Patrulha
    };

    // jogo(&jogador1, &jogador2, embarcacoes);
    menu(&jogador1, &jogador2, embarcacoes);

    return 0;
}
