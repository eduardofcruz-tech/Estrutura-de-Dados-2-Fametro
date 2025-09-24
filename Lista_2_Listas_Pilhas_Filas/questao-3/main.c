#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

// Função para imprimir o trace da pilha
void trace_pilha(Pilha* p) {
    if (vazia(p)) {
        printf("A pilha esta vazia.\n");
        return;
    }
    
    printf("\n--- Stack Trace ---\n");
    Frame *atual = p->topo;
    int nivel = 0;
    while (atual != NULL) {
        printf("Nivel %d: Func: %s, SP: %d\n", nivel, atual->func, atual->sp);
        atual = atual->baixo;
        nivel++;
    }
    printf("---------------------\n");
}

int main() {
    Pilha pilha;
    pilha_init(&pilha);
    
    char comando[10], nome_func[48];
    int sp;
    
    printf("Comandos disponiveis:\nCALL <nomeFunc> <sp>\nRET\nPEEK\nTRACE\nEXIT\n");
    
    while (1) {
        printf("> ");
        scanf("%s", comando);

        if (strcmp(comando, "CALL") == 0) {
            scanf("%s %d", nome_func, &sp);
            if (push(&pilha, nome_func, sp)) {
                printf("Frame para a funcao '%s' empilhado.\n", nome_func);
            } else {
                printf("Erro ao alocar memoria para o frame.\n");
            }
        } else if (strcmp(comando, "RET") == 0) {
            Frame frame_removido;
            if (pop(&pilha, &frame_removido)) {
                printf("Frame da funcao '%s' desempilhado.\n", frame_removido.func);
            } else {
                printf("Erro: A pilha esta vazia. Não ha frames para desempilhar.\n");
            }
        } else if (strcmp(comando, "PEEK") == 0) {
            Frame frame_topo;
            if (peek(&pilha, &frame_topo)) {
                printf("Topo da pilha: Func: %s, SP: %d\n", frame_topo.func, frame_topo.sp);
            } else {
                printf("A pilha esta vazia.\n");
            }
        } else if (strcmp(comando, "TRACE") == 0) {
            trace_pilha(&pilha);
        } else if (strcmp(comando, "EXIT") == 0) {
            printf("Finalizando a aplicaçao.\n");
            limpar(&pilha);
            break;
        } else {
            printf("Comando invalido.\n");
        }
    }
    
    return 0;
}