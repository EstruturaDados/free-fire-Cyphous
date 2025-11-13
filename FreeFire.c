#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// -------------------------------------------------------------
// Estrutura que representa um item da mochila
// -------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// -------------------------------------------------------------
// Funções principais
// -------------------------------------------------------------
void adicionarItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n============= MOCHILA - NIVEL AVENTUREIRO =============\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item por nome\n");  // NOVO NO NIVEL AVENTUREIRO
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa enter pendente

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
            case 4:
                buscarItem(mochila, total);
                break;
            case 5:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 5);

    return 0;
}

// -------------------------------------------------------------
// Adiciona um item
// -------------------------------------------------------------
void adicionarItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("A mochila esta cheia!\n");
        return;
    }

    Item novo;

    printf("Nome do item: ");
    scanf("%29s", novo.nome);

    printf("Tipo do item: ");
    scanf("%19s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*total] = novo;
    (*total)++;

    printf("Item adicionado!\n");
}

// -------------------------------------------------------------
// Remove item pelo nome
// -------------------------------------------------------------
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    scanf("%29s", nome);

    int pos = -1;

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item nao encontrado!\n");
        return;
    }

    for (int i = pos; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;

    printf("Item removido!\n");
}

// -------------------------------------------------------------
// Lista todos os itens da mochila
// -------------------------------------------------------------
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("\n=========== LISTAGEM DE ITENS ===========\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Qtd");

    for (int i = 0; i < total; i++) {
        printf("%-20s %-15s %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// -------------------------------------------------------------
// Busca sequencial por nome (NOVO NÍVEL AVENTUREIRO)
// -------------------------------------------------------------
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome do item para buscar: ");
    scanf("%29s", nome);

    int encontrado = 0; // flag

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            printf("\n----- ITEM ENCONTRADO -----\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado.\n");
    }
}
