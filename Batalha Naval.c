#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void criarTabuleiros(int tabuleiro[2][10][10], int gabarito[2][10][10]);
void limparTela();
void mostrarGabarito(int gabarito[2][10][10]);
void verificarNavios(int gabarito[2][10][10]);
void inicializarNavios(int gabarito[2][10][10], int x, int y, int embarcacao, int orientacao, int jogador);
void mostrarTabuleiro(int tabuleiro[2][10][10]);
void jogada(int tabuleiro[2][10][10], int gabarito[2][10][10], char *barco[], int pontuacao[2][2]);

int main(void)
{
    srand(time(NULL));
    int tabuleiro[2][10][10], gabarito[2][10][10], pontuacao[2][2] = {0};
    char *barcos[] = {"Agua", "Porta-Avioes", "Navio-Tanque", "ContraTorpedeiro", "Submarino"};

        criarTabuleiros(tabuleiro, gabarito);
        verificarNavios(gabarito);
        jogada(tabuleiro, gabarito, barcos, pontuacao);
        limparTela();
        mostrarGabarito(gabarito);
        
        if (pontuacao[1][1] == 15)
            printf("\n\nJogador 1 ganhou!");
        else
            printf("\n\nJogador 2 ganhou!");
        
    return 0;
}

void criarTabuleiros(int tabuleiro[2][10][10], int gabarito[2][10][10])
{
    memset(tabuleiro, -1, sizeof(int) * 2 * 10 * 10); 
    memset(gabarito, 0, sizeof(int) * 2 * 10 * 10);

}

void verificarNavios(int gabarito[2][10][10])
{
    int x, y, embarcacao = 0, tamanhoTabuleiro = 10, orientacao = 0;

    for (int jogador = 0; jogador < 2; jogador++)
    {
 
    while(embarcacao < 5)
    {
       x = rand() % tamanhoTabuleiro;
       y = rand() % tamanhoTabuleiro;

        orientacao = rand() % 2;

        int podeInserir = 1;

        if (orientacao == 0 && (y + (6 - embarcacao - 1) < tamanhoTabuleiro)) //Verifica quadrantes horizontalmente
            {
                
                for (int i = 0; i < 6 - embarcacao; i++)
                {
                    if (gabarito[jogador][x][y + i] != 0)
                    {
                        podeInserir = 0;
                        break;
                    }
                }
                if (podeInserir)
                {
                    inicializarNavios(gabarito, x, y, embarcacao, orientacao, jogador);
                    embarcacao++;
                }
            }
            else if (orientacao == 1 && (x + (6 - embarcacao - 1) < tamanhoTabuleiro)) //Verifica quadrantes verticalmente
            {
                for (int i = 0; i < 6 - embarcacao; i++)
                {
                    if (gabarito[jogador][x + i][y] != 0)
                    {
                        podeInserir = 0;
                        break;
                    }
                }
                if (podeInserir)
                {
                    inicializarNavios(gabarito, x, y, embarcacao, orientacao, jogador);
                    embarcacao++;
                }
            }
        }
        embarcacao = 0;
    }
}

void inicializarNavios(int gabarito[2][10][10], int x, int y, int embarcacao, int orientacao, int jogador)
{
    if (orientacao == 0) //Insere as embarcações horizontalmente
    {
        for (int i = 0; i < 6 - embarcacao; i++)
        {
            gabarito[jogador][x][y + i] = embarcacao;
        }
    }
    else //Insere as embarcações verticalmente
    {
        for (int i = 0; i < 6 - embarcacao; i++)
        {
            gabarito[jogador][x + i][y] = embarcacao;
        }
    }
}

void mostrarTabuleiro(int tabuleiro[2][10][10])
{
       for (int i = 0; i < 1; i++) 
    {
        for (int j = 0; j < 10; j++)
        {
            printf("\n");
            for (int h = 0; h < 10; h++)
            {
                    printf("%02d ", tabuleiro[i][j][h]);
            }
            printf("\t");
            for (int m = 0; m < 10; m++)
            {
                    printf("%02d ", tabuleiro[i + 1][j][m]);
            }
            
        }
    }
}

void jogada(int tabuleiro[2][10][10], int gabarito[2][10][10], char *barco[], int pontuacao[2][2])
{
    char *nomeEmbarcacao;
    int coordenadaX = 0, coordenadaY = 0, jogador = 0;
    
    while (pontuacao[0][0] != 15 && pontuacao[1][1] != 15)
    {
        mostrarTabuleiro(tabuleiro);
        printf("\nJogador %d realiza jogada nos quadrantes: ", jogador + 1);
        scanf("%d %d", &coordenadaX, &coordenadaY);

        coordenadaX--;
        coordenadaY--;
        
        nomeEmbarcacao = barco[gabarito[jogador][coordenadaX][coordenadaY]];
        limparTela();
        printf("\nJogador %d acertou %s", jogador + 1, nomeEmbarcacao);

        tabuleiro[jogador][coordenadaX][coordenadaY] = gabarito[jogador][coordenadaX][coordenadaY];

        if (gabarito[jogador][coordenadaX][coordenadaY] != 0)
        {
            pontuacao[jogador][jogador] += 1;
        }

        jogador = 1 - jogador;
    }
}

void mostrarGabarito(int gabarito[2][10][10])
{
        for (int i = 0; i < 1; i++)
        {
            printf("\n");
            for (int j = 0; j < 10; j++)
            {
                printf("\n");
                for (int h = 0; h < 10; h++)
                {
                    
                    printf("%02d ", gabarito[i][j][h]);
                }
                printf("\t");
                for (int  m = 0; m < 10; m++)
                {
                    printf("%02d ", gabarito[i + 1][j][m]);
                }
            }
        }
}

void limparTela(){
    #if defined(__linux__) || defined(__unix__)
        system("clear");
    #endif

    #if defined(_WIN32)
        system("cls");
    #endif
}