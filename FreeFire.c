#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_ITENS 10

// -----------------------------------------------------------
// Critérios de ordenação (enum)
// -----------------------------------------------------------
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} CriterioOrdenacao;

// -----------------------------------------------------------
// Estrutura principal do item
// -----------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // NOVO
} Item;

// -----------------------------------------------------------
// Protótipos
// -----------------------------------------------------------
void adicionarItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void ordenarItens(Item mochila[], int total, CriterioOrdenacao criterio, int *comparacoes);
void removerItem(Item mochila[], int *total);
void buscarBinaria(Item mochila[], int total);

// -----------------------------------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n=============== NIVEL MESTRE ===============\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar mochila\n");
        printf("5. Buscar item (Busca Binaria)\n");
        printf("6. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                adicionarItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4: {
                int criterio, comps = 0;
                printf("\n1 - Ordenar por nome\n");
                printf("2 - Ordenar por tipo\n");
                printf("3 - Ordenar por prioridade\n");
                printf("Escolha o criterio: ");
                scanf("%d", &criterio);

                ordenarItens(mochila, total, criterio, &comps);

                printf("\nOrdenacao concluida!\n");
                printf("Comparacoes realizadas: %d\n", comps);
                break;
            }
            case 5:
                buscarBinaria(mochila, total);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while(opcao != 6);

    return 0;
}

// -----------------------------------------------------------
// Adiciona item com prioridade
// -----------------------------------------------------------
void adicionarItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;

    printf("Nome: ");
    scanf("%29s", novo.nome);

    printf("Tipo: ");
    scanf("%19s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);

    mochila[*total] = novo;
    (*total)++;

    printf("Item adicionado.\n");
}

// -----------------------------------------------------------
// Listagem completa
// -----------------------------------------------------------
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\n=============== ITENS ===============\n");
    printf("%-12s %-12s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prior.");

    for (int i = 0; i < total; i++) {
        printf("%-12s %-12s %-10d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

// -----------------------------------------------------------
// Remove item por nome
// -----------------------------------------------------------
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("Nenhum item para remover.\n");
        return;
    }

    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%29s", nome);

    int pos = -1;

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item nao encontrado.\n");
        return;
    }

    for (int i = pos; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;

    printf("Item removido.\n");
}

// -----------------------------------------------------------
// Ordenação usando insertion sort
// -----------------------------------------------------------
void ordenarItens(Item mochila[], int total, CriterioOrdenacao criterio, int *comparacoes) {

    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;

            int cmp = 0;

            if (criterio == ORDENAR_NOME)
                cmp = strcmp(chave.nome, mochila[j].nome);
            else if (criterio == ORDENAR_TIPO)
                cmp = strcmp(chave.tipo, mochila[j].tipo);
            else if (criterio == ORDENAR_PRIORIDADE)
                cmp = chave.prioridade - mochila[j].prioridade;

            if (cmp < 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }

        mochila[j + 1] = chave;
    }
}

// -----------------------------------------------------------
// Busca Binária por nome (somente se estiver ordenado por nome)
// -----------------------------------------------------------
void buscarBinaria(Item mochila[], int total) {
    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    // verificar se está ordenado por nome
    for (int i = 1; i < total; i++) {
        if (strcmp(mochila[i].nome, mochila[i - 1].nome) < 0) {
            printf("A mochila nao esta ordenada por nome. Ordene antes.\n");
            return;
        }
    }

    char nome[30];
    printf("Nome do item a buscar: ");
    scanf("%29s", nome);

    int inicio = 0, fim = total - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(nome, mochila[meio].nome);

        if (cmp == 0) {
            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            return;
        }

        if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Item nao encontrado.\n");
}
