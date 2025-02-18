#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define linhasMAX 1024

void adicionarTarefa(FILE *Arq, const char *texto)
{
    Arq = fopen("Tarefas.txt","a");
    fprintf(Arq, "%s|0\n", texto);

    fclose(Arq);
}

void removerTarefa(FILE *Arq, int num)
{
    Arq = fopen("Tarefas.txt","r");
    int quantidadeTarefas = 0;
    char tarefasTemp[50][linhasMAX];

    while (fgets(tarefasTemp[quantidadeTarefas], linhasMAX, Arq) != NULL)
    {
        quantidadeTarefas++;
    }
    fclose(Arq);

    Arq = fopen("Tarefas.txt","w");

    for (int i = 0; i < quantidadeTarefas; i++)
    {
        if (i != num - 1)
        {
            fprintf(Arq, "%s", tarefasTemp[i]);
        }
    }
    fclose(Arq);
}

void listarTarefas(FILE *Arq)
{
    char tarefasTemp[linhasMAX];
    int i = 0;
    Arq = fopen("Tarefas.txt","r");

    while (fgets(tarefasTemp, linhasMAX, Arq) != NULL)
    {
        char *tokenTarefa = strtok(tarefasTemp, "|");
        char *tokenSituacao = strtok(NULL, "|");

        int situacao = atoi(tokenSituacao);

        printf("\n%d - %s[%s]", i + 1, tokenTarefa, situacao ? "Concluida" : "Em Andamento");
        i++;
    }
    
}

void editarSituacao(FILE *Arq, int num)
{
    Arq = fopen("Tarefas.txt","r");
    int quantidadeTarefas = 0;
    char tarefasTemp[50][linhasMAX];

    while (fgets(tarefasTemp[quantidadeTarefas], linhasMAX, Arq) != NULL)
    {
        quantidadeTarefas++;
    }
    fclose(Arq);

    Arq = fopen("Tarefas.txt","w");

    char *token = strchr(tarefasTemp[num - 1], "|");
    *(token + 1) = '1';

    for (int i = 0; i < quantidadeTarefas; i++)
    {
        fprintf(Arq, "%s", tarefasTemp[i]);
    }

    fclose(Arq);
}

void limparTela()
{
    #if defined(___linux___) || (__unix__)
    system("clear");
    #endif

    #if defined (__WIN32)
    system("cls");
    #endif
}

int main(void){

    FILE *Arq;
    int op = 0;
    char texto[linhasMAX];
    int num;


    do
    {
        limparTela();
        printf("Informe a operacao a ser selecionada:\n");
        printf("1 - Adicionar Tarefa\n");
        printf("2 - Listar Tarefa\n");
        printf("3 - Editar Tarefa\n");
        printf("4 - Deletar Tarefa\n");
        printf("0 - Fechar Programa\n");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
        limparTela();
        printf("Informe a tarefa a ser adicionada: ");
        fgets(texto, linhasMAX, stdin);
        texto[strcspn(texto, "\n")] = 0;

            adicionarTarefa(Arq, texto);
            break;

        case 2:
            limparTela();
            listarTarefas(Arq);
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n');
            break;

        case 3:
        limparTela();
            printf("Informe o numero da tarefa a ter sua situacao alterada: ");
            scanf("%d", &num);
            getchar();
            editarSituacao(Arq, num);
            break;

        case 4:
        limparTela();
            printf("Informe o numero da tarefa a ser deletada: ");
            scanf("%d", &num);
            getchar();
            removerTarefa(Arq, num);
            break;

        case 0:
            printf("Saindo...\n");
            return 0;
            break;
        
        default:
        limparTela();
            printf("Operacao informada invalida!\n");
            break;
        }
    } while(op);

    return 0;
}