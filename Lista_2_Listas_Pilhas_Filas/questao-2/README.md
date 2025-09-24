# Questão 2 — Fila para Venda Digital de Ingressos

Este projeto implementa uma fila de clientes para simular a venda de ingressos online, processando os pedidos em ordem FIFO (First-In, First-Out).

## Estrutura do Projeto

- **`fila.h`**: Contém as definições das estruturas `Cliente` e `Fila` e os protótipos das funções de manipulação da fila.
- **`fila.c`**: Implementação das funções de fila (enfileirar, desenfileirar, etc.).
- **`main.c`**: Aplicação principal com a lógica de vendas e o menu de interação via terminal.

## Compilação e Execução

Para compilar o programa, você precisa compilar os arquivos `fila.c` e `main.c` juntos. Use o seguinte comando com o compilador GCC:

```sh
gcc main.c fila.c -o vendas