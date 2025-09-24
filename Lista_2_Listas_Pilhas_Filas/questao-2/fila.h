#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

// Estrutura para representar um cliente
typedef struct Cliente {
    char id[24];
    int qtd;
    struct Cliente *prox;
} Cliente;

// Estrutura para a fila de clientes
typedef struct {
    Cliente *ini, *fim;
} Fila;

// Protótipos das funções da fila
void inicializar(Fila* f);
void enfileirar(Fila* f, Cliente c);
bool desenfileirar(Fila* f, Cliente *out);
bool vazia(Fila* f);
void limpar(Fila* f);

#endif