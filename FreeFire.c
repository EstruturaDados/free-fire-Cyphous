#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// -----------------------------------------------------------
// Representa um item da mochila
// -----------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// -----------------------------------------------------------
// Funções do sistema
// -----------------------------------------------------------
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n================ INVENTARIO =================\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer do Enter

        switch(opcao) {
            case 1:
                inserirItem(mochila, &total);
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
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 5);

    return 0;
}

// -----------------------------------------------------------
// Adiciona um item ao inventário
// -----------------------------------------------------------
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("A mochila esta cheia!\n");
        return;
    }

    Item novo;

    printf("Nome do item: ");
    scanf("%29s", novo.nome);

    printf("Tipo do item (arma, municao, cura...): ");
    scanf("%19s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*total] = novo;
    (*total)++;

    printf("Item adicionado com sucesso!\n");
}

// -----------------------------------------------------------
// Remove item pelo nome
// -----------------------------------------------------------
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a ser removido: ");
    scanf("%29s", nome);

    int encontrado = -1;

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item nao encontrado!\n");
        return;
    }

    // Desloca os itens para "tapar o buraco"
    for (int i = encontrado; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;

    printf("Item removido com sucesso!\n");
}

// -----------------------------------------------------------
// Lista todos os itens cadastrados
// -----------------------------------------------------------
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("\n=========== ITENS NA MOCHILA ===========\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");

    for (int i = 0; i < total; i++) {
        printf("%-20s %-15s %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// -----------------------------------------------------------
// Busca sequencial por um item
// -----------------------------------------------------------
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item que deseja buscar: ");
    scanf("%29s", nome);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("Item nao encontrado.\n");
}
