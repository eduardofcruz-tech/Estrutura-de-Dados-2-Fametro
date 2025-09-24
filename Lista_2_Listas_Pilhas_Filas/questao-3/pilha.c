#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializa a pilha, definindo o ponteiro do topo como NULL
void pilha_init(Pilha* p) {
    p->topo = NULL;
}

// Empilha um novo frame no topo da pilha
bool push(Pilha* p, const char *func, int sp) {
    Frame *novo_frame = (Frame*) malloc(sizeof(Frame));
    if (novo_frame == NULL) {
        return false; // Erro de alocação de memória
    }
    strcpy(novo_frame->func, func);
    novo_frame->sp = sp;
    novo_frame->baixo = p->topo;
    p->topo = novo_frame;
    return true;
}

// Desempilha e retorna o frame do topo
bool pop(Pilha* p, Frame *out) {
    if (vazia(p)) {
        return false;
    }
    Frame *temp = p->topo;
    strcpy(out->func, temp->func);
    out->sp = temp->sp;
    
    p->topo = temp->baixo;
    free(temp);
    return true;
}

// Retorna o frame do topo sem removê-lo
bool peek(Pilha* p, Frame *out) {
    if (vazia(p)) {
        return false;
    }
    strcpy(out->func, p->topo->func);
    out->sp = p->topo->sp;
    return true;
}

// Verifica se a pilha está vazia
bool vazia(Pilha* p) {
    return p->topo == NULL;
}

// Libera a memória de todos os frames da pilha
void limpar(Pilha* p) {
    Frame *atual = p->topo;
    while (atual != NULL) {
        Frame *temp = atual;
        atual = atual->baixo;
        free(temp);
    }
    p->topo = NULL;
}