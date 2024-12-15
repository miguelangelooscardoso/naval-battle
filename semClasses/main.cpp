#include <iostream>
#include <sstream> // to use stringstream
#include <locale>
#include <windows.h> // beep sound
// #include <mmsystem.h> // play sound

using namespace std;

#define LINHAS 10
#define COLUNAS 10
#define TIPOS_DE_EMBARCACAO 5

// #pragma comment(lib, "winmm.lib"); //    https://stackoverflow.com/questions/9961949/playsound-in-c-console-application

typedef struct jogador
{
    string nome;
    char tabuleiro[LINHAS][COLUNAS];
    char tentativas[LINHAS][COLUNAS];
    int numeroJogadas;
    int pontos; // número de acertos
    bool ativo;
} JOGADOR;

typedef struct embarcacao
{
    char tipo;      // tipo de embarcação (letra)
    int tamanho;    // tamanho da embarcação (número)
    int quantidade; //
} EMBARCACAO;

// void inicializarTabuleiro(char tabuleiro[LINHAS][COLUNAS]);
// void inicializarTentativas(char tentativas[LINHAS][COLUNAS]);
void inicializarMatriz(char matriz[LINHAS][COLUNAS]);
void inicializarJogador(JOGADOR *jogador, string nome);
void inicializarEmbarcacoes(EMBARCACAO *embarcacao);
//  void imprimirTabuleiro(char tabuleiro[LINHAS][COLUNAS]);
void imprimir(char tabuleiro[LINHAS][COLUNAS], char tentativas[LINHAS][COLUNAS]);
// void gerarEmbarcacoes(char tabuleiro[LINHAS][COLUNAS]);
void gerarEmbarcacoes(EMBARCACAO *embarcacao, char tabuleiro[LINHAS][COLUNAS]);
//  void inserirTentativas(char tabuleiro[LINHAS][COLUNAS], char tentativas[LINHAS][COLUNAS]);
// bool inserirTentativas(JOGADOR *jogador, int *acertou);
bool inserirTentativas(JOGADOR *jogador);
// void jogo(JOGADOR *jogador1, JOGADOR *jogador2);
// void jogo(JOGADOR *jogador1, JOGADOR *jogador2, EMBARCACAO *embarcacoes);
// void jogo(JOGADOR *jogador1, JOGADOR *jogador2, EMBARCACAO *embarcacoes, int *acertou);
void jogo(JOGADOR *jogador1, JOGADOR *jogador2, EMBARCACAO *embarcacoes);
void turnoJogador(JOGADOR *jogador, JOGADOR *adversario, bool *jogarNovamente);
void menu(JOGADOR *jogador1, JOGADOR *jogador2, EMBARCACAO *embarcacoes);
void SetTextColor(int color); // cor

int main()
{
    setlocale(LC_ALL, "pt_PT.UTF-8");
    srand(time(0)); // necessário para gerar um x,y aleatório
    // char tabuleiro[LINHAS][COLUNAS];
    // char tentativas[LINHAS][COLUNAS];

    // int acertou = 0;

    JOGADOR jogador1;
    jogador1.nome = "Jogador 1"; // Atribuição direta de nome usando std::string
    jogador1.pontos = 0;
    jogador1.numeroJogadas = 0;

    JOGADOR jogador2;
    jogador2.nome = "Jogador 2"; // Atribuição direta de nome usando std::string
    jogador2.pontos = 0;
    jogador2.numeroJogadas = 0;

    PlaySound(TEXT("exemplo.wav"), NULL, SND_FILENAME | SND_ASYNC); // compile as 'g++ main.cpp -o main -lwinmm'

    EMBARCACAO embarcacoes[TIPOS_DE_EMBARCACAO];
    // jogo(&jogador1, &jogador2, embarcacoes, &acertou);
    menu(&jogador1, &jogador2, embarcacoes);
    //  player vs computador (permitir ao jogador posicionar os seus barcos)
    //  contar quantos barcos já afundaram
    //  exibir resultados ao utilizador
    //  usar som e enumeração para saber se navio já afundou ou não (enum)
    //  https://mixkit.co/free-sound-effects/
    //  vetor é um ponteiro para um array de dimensão desconhecida (vetor estátivo vs vetor dinâmico)
    //  número de jogadas não deve alterar caso o jogador insira algo inválido ou o mesmo input
    //  preciso de adicionar tentativas do jogador 2 no tabuleiro do jogador 1 e vice-versa
    //  preciso de verificar condição de acerto em todas as embarcações
    //  não existe condição de empate certo (???)
    //  temporizador (ou temporizador individual i.e. para cada jogador com várias pausas, não faz sentido temporizar o tempo total de jogo)
    //  falta adicionar classes, vetor dinâmico às embarcações
    //  malloc e realloc para representar as tentativas talvez
    //  jogar contra computador
    //  pausar jogo, retomar jogo a partir de ficheiro
    //  falta-me acrescentar o número de embarcações de cada tipo
    //  condição de saída (acertou em todos ou o limite de jogadas esgotou)
    //  multi-player

    //  caracter a piscar até selecionar quadrado para selecionar campo

    return 0;
}

void inicializarMatriz(char matriz[LINHAS][COLUNAS]) // tabuleiro ou tentativas
{

    for (int i = 0; i < LINHAS; i++) // linhas
    {
        for (int j = 0; j < COLUNAS; j++) // colunas
        {
            matriz[i][j] = ' ';
        }
    }
}

// void inicializarTentativas(char tentativas[LINHAS][COLUNAS])
// {
//     for (int i = 0; i < LINHAS; i++) // linhas
//     {
//         for (int j = 0; j < COLUNAS; j++) // colunas
//         {
//             tentativas[i][j] = ' ';
//         }
//     }
// }

void inicializarJogador(JOGADOR *jogador, string nome)
{
    jogador->nome = nome;                   //    *(jogador.nome)
    inicializarMatriz(jogador->tabuleiro);  //    *(jogador.tabuleiro)
    inicializarMatriz(jogador->tentativas); //   *(jogador.tentativas)
}

void SetTextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void imprimir(char tabuleiro[LINHAS][COLUNAS], char tentativas[LINHAS][COLUNAS])
{
    // 1 tabuleiro de cada vez (!!!)

    // for (int k = 0; k < COLUNAS; k++)
    // {
    //     cout << "[" << k + 1 << "]";
    // }
    // cout << endl;

    // for (int i = 0; i < LINHAS; i++)
    // {
    //     for (int j = 0; j < COLUNAS; j++)
    //     {
    //         cout << "[" << tabuleiro[i][j] << "]";
    //     }
    //     cout << "[" << char('A' + i) << "]" << endl;
    // }

    SetTextColor(14);
    // tentativas e tabuleiro lado a lado
    for (int k = 0; k < COLUNAS; k++)
    {
        cout << "[" << k + 1 << "]"; // numeração da matriz tabuleiro
    }
    cout << "     "; // espaço entre os índices dois tabuleiros (espaço entre [10] e [1])
    for (int k = 0; k < COLUNAS; k++)
    {
        cout << "[" << k + 1 << "]"; // numeração da matriz tentativas
    }
    cout << endl;

    SetTextColor(7);
    for (int i = 0; i < LINHAS; i++) // imprime ambos os tabuleiroe tentativas linha a linha
    {

        for (int j = 0; j < COLUNAS; j++) // tabuleiro
        {
            // cout << "[" << tabuleiro[i][j] << "]";
            cout << "[";
            if (tabuleiro[i][j] == 'X')
            {
                SetTextColor(12); // vermelho se 'X'
            }
            else if (tabuleiro[i][j] == '~')
            {
                SetTextColor(11); // azul aqua
            }
            // else
            // {
            //     SetTextColor(7); // default se 'A, B, C, D, E ...'
            // }

            cout << tabuleiro[i][j];
            SetTextColor(7);
            cout << "]";
        }

        SetTextColor(14);
        cout << "[" << char('A' + i) << "]"; // imprime a letra correspondente à linha do primeiro tabuleiro (letra A-J)
        SetTextColor(7);
        cout << "   "; // espaço entre tabuleiro e tenativas

        for (int j = 0; j < COLUNAS; j++) // tentativas
        {

            cout << "[";
            if (tentativas[i][j] == 'O')
            {
                SetTextColor(12); // vermelho se 'O'
            }
            else
            {
                SetTextColor(10); // verde se A, B, C, D, E
            }

            cout << tentativas[i][j];
            SetTextColor(7);
            cout << "]";
        }
        SetTextColor(14);
        cout << "[" << char('A' + i) << "]" << endl; // imprime a letra correspondente à linha do primeiro tabuleiro (letra A-J)
        SetTextColor(7);
    }
    cout << "\tAs suas embarcações: \t\tAs suas tentativas:" << endl;
}

void inicializarEmbarcacoes(EMBARCACAO *embarcacao)
{
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

void gerarEmbarcacoes(EMBARCACAO *embarcacao, char tabuleiro[LINHAS][COLUNAS])
{

    bool escritaPossivel;
    for (int k = 0; k < TIPOS_DE_EMBARCACAO; k++) // para cada um das embarcações
    {
        for (int l = 0; l < (embarcacao + k)->quantidade; l++)
        {
            do
            {
                int xAleatorio = rand() % LINHAS;  // gera um número aleatório entre 0 e LINHAS-1 i.e. indíce de linhas
                int yAleatorio = rand() % COLUNAS; // gera um número aleatório entre 0 e COLUNAS-1 i.e. indíce de colunas

                int direcao = rand() % 2; // i.e. gera direção aleatória horizontal ou vertical (0 ou 1)

                escritaPossivel = true;
                for (int i = 0; i < (embarcacao + k)->tamanho; i++)
                {

                    if (direcao == 1) // vertical
                    {
                        if (xAleatorio + i >= LINHAS || tabuleiro[xAleatorio + i][yAleatorio] != ' ') // não ultrapassa índice de colunas ou está lá outro barco
                        {
                            escritaPossivel = false;
                            break;
                        }
                    }
                    else if (direcao == 0) // horizontal
                    {
                        if (yAleatorio + i >= COLUNAS || tabuleiro[xAleatorio][yAleatorio + i] != ' ') // não ultrapassa índice de linhas ou está lá outro barco
                        {
                            escritaPossivel = false;
                            break;
                        }
                    }
                }

                if (escritaPossivel)
                {
                    for (int j = 0; j < (embarcacao + k)->tamanho; j++)
                    {
                        if (direcao == 1) // vertical
                        {
                            tabuleiro[xAleatorio + j][yAleatorio] = (embarcacao + k)->tipo;
                        }
                        else if (direcao == 0) // horizontal
                        {
                            tabuleiro[xAleatorio][yAleatorio + j] = (embarcacao + k)->tipo;
                        }
                    }
                }
            } while (!escritaPossivel);
        }
    }
}

// bool inserirTentativas(JOGADOR *jogador, int *acertou)
bool inserirTentativas(JOGADOR *jogador)
{
    string entrada;
    char bra1, ket1, bra2, ket2, letra;
    int numero;

    bool jogarNovamente = false; // regra geral

    // while (numeroJogadas < maximoJogadas)
    // {

    cout << "\tIntroduza a sua tentativa na forma [letra][número]." << endl;
    cout << "\t>";
    getline(cin, entrada);

    if (entrada == "q")
    {
        cout << "Saiu do jogo." << endl;
        //  imprimirTabuleiro(tabuleiro);
        exit(0);
    }

    stringstream processarEntrada(entrada); // processa o formato de entrada
    processarEntrada >> bra1 >> letra >> ket1 >> bra2 >> numero >> ket2;

    // cout << "Número Inserido: " << numero << endl;

    if (processarEntrada.fail())
    {
        cout << "\tO processamento do formato de entrada falhou." << endl;
    }
    else if (bra1 != '[' || ket1 != ']' || bra2 != '[' || ket2 != ']')
    {
        cout << "\tFormato incorreto. Tente novamente." << endl;
    }

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
                Beep(400, 100); // 400 Hz for 100 milliseconds

                // (*acertou)++;
                jogador->pontos++;
                jogarNovamente = true;
                // if (*acertou == 25)
                // {
                //     cout << "You won!" << endl;
                //     exit(0);
                // }
                // cout << "acertou: " << acertou << endl;
            }
            else
            {
                jogador->tentativas[indiceLinha][indiceColuna] = 'O'; // 0
                jogador->tabuleiro[indiceLinha][indiceColuna] = '~';
                jogarNovamente = false;
            }
            // cout << "acertou: " << acertou <<endl;
            jogador->numeroJogadas++;
            // numeroJogadas++;
            // imprimir(tabuleiro, tentativas);

            // if (!jogarNovamente)
            // {
            //     jogador->tabuleiro[indiceLinha][indiceColuna] = 'X';
            // }
        }
        else
        {
            cout << "\tJogada repetida, tente outra." << endl;
            jogarNovamente = true;
        }
    }
    else
    {
        cout << "\tDeve escolher uma letra de A-H e um número de 1-10" << endl;
        jogarNovamente = true;
    }

    return jogarNovamente;
    // }
}

void jogo(JOGADOR *jogador1, JOGADOR *jogador2, EMBARCACAO *embarcacoes) // para um único jogador
{
    // JOGADOR jogador1;
    // jogador1.nome = "Jogador 1"; // atribuição direta usando string
    // jogo(&jogador1);

    // JOGADOR jogador2;
    // jogador2.nome = "Jogador 2"; // atribuição direta usando string
    // jogo(&jogador1);

    inicializarJogador(jogador1, jogador1->nome);
    inicializarJogador(jogador2, jogador2->nome);

    inicializarMatriz(jogador1->tabuleiro); //  tabuleiro, jogador 1
    inicializarMatriz(jogador2->tabuleiro); //   tabuleiro, jogador 2

    inicializarMatriz(jogador1->tentativas); // tentativas, jogador 1
    inicializarMatriz(jogador2->tentativas); // tentativas, jogador 2

    inicializarEmbarcacoes(embarcacoes);

    gerarEmbarcacoes(embarcacoes, jogador1->tabuleiro); // embarcações, jogador 1
    gerarEmbarcacoes(embarcacoes, jogador2->tabuleiro); // embarcações, jogador2

    char c;
    bool jogarNovamente = true;
    jogador1->ativo = true;
    jogador2->ativo = false;
    // jogador1->numeroJogadas = 0;
    // jogador2->numeroJogadas = 0;

    while (1)
    {
        system("cls");
        // é possível escrever mais uma função que encapsule as duas partes do if
        if (jogador1->ativo)
        {
            turnoJogador(jogador1, jogador2, &jogarNovamente);
        }
        else if (jogador2->ativo)
        {
            turnoJogador(jogador2, jogador1, &jogarNovamente);
        }

        cout << "\tPressione 'Enter' para a ir para jogada seguinte." << endl;
        cout << "\t>";
        cin.get(c);
    }
}

void turnoJogador(JOGADOR *jogador, JOGADOR *oponente, bool *jogarNovamente)
{
    cout << "\t\t\tÉ a sua vez ";
    SetTextColor(1);
    cout << jogador->nome;
    SetTextColor(7);
    cout << "!" << endl;
    imprimir(oponente->tabuleiro, jogador->tentativas);
    *jogarNovamente = inserirTentativas(jogador);
    // cout << "Jogar Novamente? " << (jogarNovamente ? "true" : "false") << endl;
    system("cls");
    imprimir(oponente->tabuleiro, jogador->tentativas);
    cout << "\tJogador 1: " << jogador->pontos << " pontos\t\tJogador 2: " << oponente->pontos << " pontos." << endl;

    if (!*jogarNovamente)
    {
        jogador->ativo = false;
        oponente->ativo = true;
    }

    // jogador1->numeroJogadas++;
    cout << "\tNúmero de Jogadas Jogador 1: " << jogador->numeroJogadas << endl;

    // if (*acertou == 25)
    if (jogador->pontos == 25)
    {
        cout << "\t" << jogador->nome << " won!" << endl;
        exit(0);
    }

    //  não faz sentido jogar jogador contra jogador com limite de jogadas
    // if (jogador1->numeroJogadas == 75)
    // {
    //     cout << "Game Over" << endl;
    //     exit(0);
    // }
}
void menu(JOGADOR *jogador1, JOGADOR *jogador2, EMBARCACAO *embarcacoes)
{
    int opcao;
    int ch;

    while (1)
    {
        system("cls");

        // pressione qualquer tecla para voltar ao menu principal

        printf("====================================\n");
        printf("       *** Menu Principal ***\n");
        printf("====================================\n");
        printf(" 1. Jogador vs Jogador\n");
        printf(" 2. Jogador vs Computador\n");
        printf(" 3. Ajudar\n");
        printf(" 4. Sair\n");
        printf("====================================\n");
        printf(" Escolha uma opção (1-3): ");

        scanf("%d", &opcao);

        system("cls");
        switch (opcao)
        {
        case 1:
            jogo(jogador1, jogador2, embarcacoes);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            printf("4. Sair");
            exit(0);
        default:
            printf("Escolha outra opção.");
        }
        ch = getchar();
    }
}
