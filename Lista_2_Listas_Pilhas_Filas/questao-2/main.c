#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Função auxiliar para o relatório REL
void exibirRelatorio(int total_vendido, int clientes_atendidos, int estoque_restante, int top3_qtd[], char top3_id[][24], Fila *nao_atendidos_fila)
{
    printf("\n--- Relatorio de Vendas ---\n");
    printf("Total de ingressos vendidos: %d\n", total_vendido);
    printf("Numero de clientes atendidos: %d\n", clientes_atendidos);
    printf("Quantidade restante em estoque: %d\n", estoque_restante);

    printf("\nTop 3 Maiores Compras:\n");
    for (int i = 0; i < 3; i++)
    {
        if (top3_qtd[i] > 0)
        {
            printf("%d. Cliente %s: %d ingressos\n", i + 1, top3_id[i], top3_qtd[i]);
        }
    }

    printf("\nClientes Nao Atendidos:\n");
    if (vazia(nao_atendidos_fila))
    {
        printf("Nenhum cliente nao atendido.\n");
    }
    else
    {
        Cliente *atual = nao_atendidos_fila->ini;
        while (atual != NULL)
        {
            printf("- Cliente %s: solicitou %d ingressos\n", atual->id, atual->qtd);
            atual = atual->prox;
        }
    }
    printf("---------------------------\n");
}

int main()
{
    Fila fila_clientes;
    Fila fila_nao_atendidos;
    inicializar(&fila_clientes);
    inicializar(&fila_nao_atendidos);

    int estoque_inicial;
    printf("Informe o estoque inicial de ingressos: ");
    scanf("%d", &estoque_inicial);

    int estoque_atual = estoque_inicial;
    int total_vendido = 0;
    int clientes_atendidos = 0;

    int top3_qtd[3] = {0, 0, 0};
    char top3_id[3][24] = {"", "", ""};

    char comando[10], id[24];
    int qtd;

    printf("\nComandos disponiveis:\nADD <id> <qtd>\nSTART\nRE\nEXIT\n");

    while (true)
    {
        printf("> ");
        scanf("%s", comando);

        if (strcmp(comando, "ADD") == 0)
        {
            scanf("%s %d", id, &qtd);
            Cliente novo_cliente;
            strcpy(novo_cliente.id, id);
            novo_cliente.qtd = qtd;
            enfileirar(&fila_clientes, novo_cliente);
            printf("Cliente %s adicionado a fila.\n", id);
        }
        else if (strcmp(comando, "START") == 0)
        {
            printf("\n--- Iniciando o processamento da fila ---\n");

            while (!vazia(&fila_clientes))
            {
                if (estoque_atual <= 0)
                {
                    printf("Estoque esgotado. Processamento finalizado.\n");
                    break;
                }

                Cliente cliente_atual;
                desenfileirar(&fila_clientes, &cliente_atual);

                if (cliente_atual.qtd <= estoque_atual)
                {
                    printf("Cliente %s: vendendo %d ingressos. Venda concluida.\n", cliente_atual.id, cliente_atual.qtd);
                    estoque_atual -= cliente_atual.qtd;
                    total_vendido += cliente_atual.qtd;
                    clientes_atendidos++;

                    if (cliente_atual.qtd > top3_qtd[0])
                    {
                        top3_qtd[2] = top3_qtd[1];
                        strcpy(top3_id[2], top3_id[1]);
                        top3_qtd[1] = top3_qtd[0];
                        strcpy(top3_id[1], top3_id[0]);
                        top3_qtd[0] = cliente_atual.qtd;
                        strcpy(top3_id[0], cliente_atual.id);
                    }
                    else if (cliente_atual.qtd > top3_qtd[1])
                    {
                        top3_qtd[2] = top3_qtd[1];
                        strcpy(top3_id[2], top3_id[1]);
                        top3_qtd[1] = cliente_atual.qtd;
                        strcpy(top3_id[1], cliente_atual.id);
                    }
                    else if (cliente_atual.qtd > top3_qtd[2])
                    {
                        top3_qtd[2] = cliente_atual.qtd;
                        strcpy(top3_id[2], cliente_atual.id);
                    }
                }
                else
                {
                    char confirmacao;
                    printf("Cliente %s: solicitou %d ingressos, mas so temos %d. Vender a quantidade disponivel? (S/N)\n", cliente_atual.id, cliente_atual.qtd, estoque_atual);
                    scanf(" %c", &confirmacao);

                    if (confirmacao == 'S' || confirmacao == 's')
                    {
                        printf("Cliente %s: vendendo os %d ingressos restantes. Venda concluida.\n", cliente_atual.id, estoque_atual);
                        total_vendido += estoque_atual;
                        clientes_atendidos++;
                        estoque_atual = 0;
                    }
                    else
                    {
                        printf("Venda para cliente %s cancelada. Cliente nao atendido.\n", cliente_atual.id);
                        enfileirar(&fila_nao_atendidos, cliente_atual);
                    }
                }
            }
            printf("--- Processamento da fila concluido. ---\n");
        }
        else if (strcmp(comando, "REL") == 0)
        {
            exibirRelatorio(total_vendido, clientes_atendidos, estoque_atual, top3_qtd, top3_id, &fila_nao_atendidos);
        }
        else if (strcmp(comando, "EXIT") == 0)
        {
            printf("Finalizando a aplicacao.\n");
            limpar(&fila_clientes);
            limpar(&fila_nao_atendidos);
            break;
        }
        else
        {
            printf("Comando invalido.\n");
        }
    }

    return 0;
}