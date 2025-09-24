#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializa a fila, definindo os ponteiros de início e fim como NULL
void inicializar(Fila* f) {
    f->ini = NULL;
    f->fim = NULL;
}

// Adiciona um novo cliente no final da fila
void enfileirar(Fila* f, Cliente c) {
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    if (novo == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }
    strcpy(novo->id, c.id);
    novo->qtd = c.qtd;
    novo->prox = NULL;

    if (f->fim != NULL) {
        f->fim->prox = novo;
    } else {
        f->ini = novo;
    }
    f->fim = novo;
}

// Remove o cliente do início da fila e retorna seus dados
bool desenfileirar(Fila* f, Cliente *out) {
    if (f->ini == NULL) {
        return false;
    }

    Cliente *temp = f->ini;
    strcpy(out->id, temp->id);
    out->qtd = temp->qtd;

    f->ini = temp->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }
    
    free(temp);
    return true;
}

// Verifica se a fila está vazia
bool vazia(Fila* f) {
    return f->ini == NULL;
}

// Libera a memória de todos os nós da fila
void limpar(Fila* f) {
    Cliente *atual = f->ini;
    while (atual != NULL) {
        Cliente *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    f->ini = NULL;
    f->fim = NULL;
}