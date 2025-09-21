#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COD_LEN 16
#define NOME_LEN 64
#define MAX_CMD_LEN 256

typedef struct Produto {
    char codigo[COD_LEN];
    char nome[NOME_LEN];
    int qtd;
    float preco;
    struct Produto *prox;
} Produto;

// Protótipos das funções
Produto* criar_no(const char *codigo, const char *nome, int qtd, float preco);
Produto* inserir_inicio(Produto *L, Produto p);
Produto* inserir_ordenado_por_codigo(Produto *L, Produto p);
Produto* remover_por_codigo(Produto *L, const char *codigo);
Produto* ajustar_quantidade(Produto *L, const char *codigo, int delta_qtd);
Produto* buscar(Produto *L, const char *codigo);
void listar(Produto *L);
Produto* limpar(Produto *L);
void relatorio(Produto *L);
void exibir_ajuda();
void processar_comando(Produto **L, const char *comando);
void ler_linha(char *linha, int max_len);

// --- Implementação das Funções da Lista Ligada ---

/**
 * @brief Cria um novo nó (Produto) e aloca memória para ele.
 */
Produto* criar_no(const char *codigo, const char *nome, int qtd, float preco) {
    Produto *novo = (Produto*) malloc(sizeof(Produto));
    if (novo == NULL) {
        perror("Erro ao alocar memória para o novo produto");
        return NULL;
    }
    strncpy(novo->codigo, codigo, COD_LEN - 1);
    novo->codigo[COD_LEN - 1] = '\0';
    strncpy(novo->nome, nome, NOME_LEN - 1);
    novo->nome[NOME_LEN - 1] = '\0';
    novo->qtd = qtd;
    novo->preco = preco;
    novo->prox = NULL;
    return novo;
}

/**
 * @brief Insere um novo produto no início da lista.
 */
Produto* inserir_inicio(Produto *L, Produto p) {
    Produto *novo = criar_no(p.codigo, p.nome, p.qtd, p.preco);
    if (novo == NULL) {
        return L;
    }
    novo->prox = L;
    return novo;
}

/**
 * @brief Insere um produto na lista de forma ordenada por código.
 * Se o código já existe, atualiza a quantidade, o nome e o preço.
 */
Produto* inserir_ordenado_por_codigo(Produto *L, Produto p) {
    Produto *atual = L;
    Produto *anterior = NULL;
    
    // Procura por um nó com o mesmo código ou a posição de inserção
    while (atual != NULL && strcmp(atual->codigo, p.codigo) < 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL && strcmp(atual->codigo, p.codigo) == 0) {
        // Código já existe, atualiza as informações
        atual->qtd = p.qtd;
        atual->preco = p.preco;
        strcpy(atual->nome, p.nome);
        printf("Produto com codigo '%s' atualizado.\n", p.codigo);
        return L;
    }

    // Cria e insere um novo nó
    Produto *novo = criar_no(p.codigo, p.nome, p.qtd, p.preco);
    if (novo == NULL) {
        return L;
    }

    if (anterior == NULL) {
        // Insere no início da lista
        novo->prox = L;
        printf("Produto '%s' adicionado no inicio.\n", novo->nome);
        return novo;
    } else {
        // Insere no meio ou no fim da lista
        novo->prox = atual;
        anterior->prox = novo;
        printf("Produto '%s' adicionado.\n", novo->nome);
        return L;
    }
}

/**
 * @brief Remove um produto da lista com base no código.
 */
Produto* remover_por_codigo(Produto *L, const char *codigo) {
    Produto *atual = L;
    Produto *anterior = NULL;

    while (atual != NULL && strcmp(atual->codigo, codigo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Produto com codigo '%s' nao encontrado.\n", codigo);
        return L;
    }

    if (anterior == NULL) {
        // Remove o primeiro elemento
        L = atual->prox;
    } else {
        // Remove um elemento no meio ou no fim
        anterior->prox = atual->prox;
    }

    printf("Produto '%s' removido.\n", atual->nome);
    free(atual);
    return L;
}

/**
 * @brief Ajusta a quantidade de um produto na lista.
 */
Produto* ajustar_quantidade(Produto *L, const char *codigo, int delta_qtd) {
    Produto *p = buscar(L, codigo);
    if (p == NULL) {
        printf("Produto com codigo '%s' nao encontrado.\n", codigo);
        return L;
    }

    if (p->qtd + delta_qtd < 0) {
        printf("Erro: A operacao resultaria em quantidade negativa.\n");
        return L;
    }

    p->qtd += delta_qtd;
    printf("Quantidade do produto '%s' ajustada para %d.\n", p->nome, p->qtd);
    return L;
}

/**
 * @brief Busca um produto na lista por código.
 */
Produto* buscar(Produto *L, const char *codigo) {
    Produto *atual = L;
    while (atual != NULL) {
        if (strcmp(atual->codigo, codigo) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

/**
 * @brief Lista todos os produtos na lista.
 */
void listar(Produto *L) {
    if (L == NULL) {
        printf("A lista de produtos esta vazia.\n");
        return;
    }
    
    printf("\n--- Catalogo de Produtos ---\n");
    Produto *atual = L;
    while (atual != NULL) {
        printf("  > Codigo: %s\n", atual->codigo);
        printf("    Nome: %s\n", atual->nome);
        printf("    Quantidade: %d\n", atual->qtd);
        printf("    Preco: R$%.2f\n", atual->preco);
        printf("    Valor Total: R$%.2f\n", atual->qtd * atual->preco);
        printf("---------------------------\n");
        atual = atual->prox;
    }
}

/**
 * @brief Libera toda a memória alocada para a lista.
 */
Produto* limpar(Produto *L) {
    Produto *atual = L;
    Produto *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    printf("Toda a lista de produtos foi limpa.\n");
    return NULL;
}

/**
 * @brief Gera um relatório de estoque.
 */
void relatorio(Produto *L) {
    if (L == NULL) {
        printf("Nenhum produto em estoque para gerar o relatorio.\n");
        return;
    }

    int itens_distintos = 0;
    float valor_total_estoque = 0.0;
    Produto *produto_maior_valor_imobilizado = NULL;
    float maior_valor = 0.0;

    Produto *atual = L;
    while (atual != NULL) {
        itens_distintos++;
        float valor_imobilizado = atual->qtd * atual->preco;
        valor_total_estoque += valor_imobilizado;

        if (valor_imobilizado > maior_valor) {
            maior_valor = valor_imobilizado;
            produto_maior_valor_imobilizado = atual;
        }
        atual = atual->prox;
    }

    printf("\n--- Relatorio de Estoque ---\n");
    printf("  > Total de itens distintos: %d\n", itens_distintos);
    printf("  > Valor total do estoque: R$%.2f\n", valor_total_estoque);
    if (produto_maior_valor_imobilizado != NULL) {
        printf("  > Produto com maior valor imobilizado:\n");
        printf("    - Codigo: %s\n", produto_maior_valor_imobilizado->codigo);
        printf("    - Nome: %s\n", produto_maior_valor_imobilizado->nome);
        printf("    - Valor: R$%.2f\n", maior_valor);
    }
    printf("---------------------------\n");
}

// --- Funções Auxiliares e Main ---

/**
 * @brief Exibe a lista de comandos disponíveis.
 */
void exibir_ajuda() {
    printf("\nComandos disponiveis:\n");
    printf("  ADD <cod> \"<nome>\" <qtd> <preco>  - Adiciona/atualiza um produto.\n");
    printf("  UPD <cod> <delta_qtd>            - Ajusta a quantidade de um produto.\n");
    printf("  DEL <cod>                        - Remove um produto.\n");
    printf("  FIND <cod>                       - Busca um produto por codigo.\n");
    printf("  LIST                             - Lista todos os produtos.\n");
    printf("  REL                              - Mostra o relatorio do estoque.\n");
    printf("  HELP                             - Exibe esta ajuda.\n");
    printf("  EXIT                             - Sair da aplicacao.\n");
}

/**
 * @brief Lê uma linha da entrada padrão, ignorando o restante se for muito longa.
 */
void ler_linha(char *linha, int max_len) {
    if (fgets(linha, max_len, stdin) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
    }
}

/**
 * @brief Processa o comando digitado pelo usuário.
 */
void processar_comando(Produto **L, const char *comando) {
    char cmd[10];
    char cod[COD_LEN];
    char nome[NOME_LEN];
    int qtd;
    float preco;
    int delta_qtd;
    
    // Usa sscanf para parsear o comando principal
    if (sscanf(comando, "%s", cmd) != 1) {
        return; // Comando vazio
    }

    for (int i = 0; cmd[i]; i++) {
        cmd[i] = toupper(cmd[i]);
    }

    if (strcmp(cmd, "ADD") == 0) {
        char *ptr_nome_inicio = strchr(comando, '"');
        if (ptr_nome_inicio == NULL) {
             printf("Erro de sintaxe. Use ADD <cod> \"<nome>\" <qtd> <preco>\n");
             return;
        }
        
        char *ptr_nome_fim = strchr(ptr_nome_inicio + 1, '"');
        if (ptr_nome_fim == NULL) {
             printf("Erro de sintaxe. Use ADD <cod> \"<nome>\" <qtd> <preco>\n");
             return;
        }

        // Extrai o nome
        int len_nome = ptr_nome_fim - ptr_nome_inicio - 1;
        if (len_nome >= NOME_LEN) {
            printf("Erro: Nome muito longo.\n");
            return;
        }
        strncpy(nome, ptr_nome_inicio + 1, len_nome);
        nome[len_nome] = '\0';

        // Pula para a próxima parte da string para ler qtd e preco
        char *ptr_resto = ptr_nome_fim + 1;
        
        // Extrai o código, qtd e preço
        if (sscanf(comando, "ADD %s", cod) != 1 || sscanf(ptr_resto, "%d %f", &qtd, &preco) != 2) {
             printf("Erro de sintaxe. Use ADD <cod> \"<nome>\" <qtd> <preco>\n");
             return;
        }
        
        Produto novo_produto;
        strncpy(novo_produto.codigo, cod, COD_LEN - 1);
        novo_produto.codigo[COD_LEN - 1] = '\0';
        strncpy(novo_produto.nome, nome, NOME_LEN - 1);
        novo_produto.nome[NOME_LEN - 1] = '\0';
        novo_produto.qtd = qtd;
        novo_produto.preco = preco;

        *L = inserir_ordenado_por_codigo(*L, novo_produto);
    } else if (strcmp(cmd, "UPD") == 0) {
        if (sscanf(comando, "UPD %s %d", cod, &delta_qtd) != 2) {
            printf("Erro de sintaxe. Use UPD <cod> <delta_qtd>\n");
        } else {
            *L = ajustar_quantidade(*L, cod, delta_qtd);
        }
    } else if (strcmp(cmd, "DEL") == 0) {
        if (sscanf(comando, "DEL %s", cod) != 1) {
            printf("Erro de sintaxe. Use DEL <cod>\n");
        } else {
            *L = remover_por_codigo(*L, cod);
        }
    } else if (strcmp(cmd, "FIND") == 0) {
        if (sscanf(comando, "FIND %s", cod) != 1) {
            printf("Erro de sintaxe. Use FIND <cod>\n");
        } else {
            Produto *p = buscar(*L, cod);
            if (p != NULL) {
                printf("\n--- Produto Encontrado ---\n");
                printf("  > Codigo: %s\n", p->codigo);
                printf("    Nome: %s\n", p->nome);
                printf("    Quantidade: %d\n", p->qtd);
                printf("    Preco: R$%.2f\n", p->preco);
                printf("--------------------------\n");
            } else {
                printf("Produto com codigo '%s' nao encontrado.\n", cod);
            }
        }
    } else if (strcmp(cmd, "LIST") == 0) {
        listar(*L);
    } else if (strcmp(cmd, "REL") == 0) {
        relatorio(*L);
    } else if (strcmp(cmd, "HELP") == 0) {
        exibir_ajuda();
    } else if (strcmp(cmd, "EXIT") == 0) {
        printf("Encerrando a aplicacao.\n");
        *L = limpar(*L);
        exit(0);
    } else {
        printf("Comando desconhecido. Digite 'HELP' para ver os comandos disponiveis.\n");
    }
}

int main() {
    Produto *estoque = NULL;
    char comando[MAX_CMD_LEN];

    printf("Bem-vindo ao sistema de controle de estoque.\n");
    exibir_ajuda();
    
    while (1) {
        printf("\n> ");
        ler_linha(comando, sizeof(comando));
        processar_comando(&estoque, comando);
    }

    return 0;
}