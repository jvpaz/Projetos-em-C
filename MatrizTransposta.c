#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **Transcreve(int **p, int alt, int lar);
void insereValores(int **p, int alt, int lar);
void liberarMemoria(int **p, int alt);

int main(void){

    int largura, altura, **transposta;

    printf("Insira a largura e altura da matriz: ");
    scanf("%d %d", &largura, &altura);

    int **matriz = (int**)malloc(altura * sizeof(int*));
    for (int i = 0; i < altura; i++)
    {
        matriz[i] = (int*)malloc(largura * sizeof(int));
    }

    insereValores(matriz, altura, largura);
    transposta = Transcreve(matriz, altura, largura);

    printf("Original\n");
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    printf("Transposta\n");
    for (int i = 0; i < largura; i++)
    {
        for (int j = 0; j < altura; j++)
        {
            printf("%d ", transposta[i][j]);
        }
        printf("\n");
    }
    

    liberarMemoria(matriz, altura);
    liberarMemoria(transposta, largura);
    

    return 0;
}

int **Transcreve(int **p, int alt, int lar)
{
    int **temp = (int**)malloc(lar * sizeof(int*));
    for (int i = 0; i < lar; i++)
    {
        temp[i] = (int*)malloc(alt * sizeof(int));
    }

    for (int i = 0; i < alt; i++)
    {
        for (int j = 0; j < lar; j++)
        {
            temp[j][i] = p[i][j];
        }
    }

    return temp;
}

void insereValores(int **p, int alt, int lar)
{
    srand(time(NULL));

    for (int i = 0; i < alt; i++)
    {
        for (int j = 0; j < lar; j++)
        {
            p[i][j] = rand() % 8 + 1;
        }
        
    }  
}

void liberarMemoria(int **p, int alt)
{
    for (int i = 0; i < alt; i++)
    {
        free(p[i]);
    }
    free(p);
}