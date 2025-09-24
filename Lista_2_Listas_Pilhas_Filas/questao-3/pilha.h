#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

// Estrutura para representar um frame na pilha de execução
typedef struct Frame {
    char func[48];
    int sp;
    struct Frame *baixo;
} Frame;

// Estrutura para a pilha de frames
typedef struct {
    Frame *topo;
} Pilha;

// Protótipos das funções da pilha
void pilha_init(Pilha* p);
bool push(Pilha* p, const char *func, int sp);
bool pop(Pilha* p, Frame *out);
bool peek(Pilha* p, Frame *out);
bool vazia(Pilha* p);
void limpar(Pilha* p);

#endif