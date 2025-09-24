# Questão 3 — Pilha de Processos (alocação dinâmica)

Este projeto simula uma versão simplificada da stack de execução de um processo em um sistema operacional. A pilha gerencia a sequência de chamadas e retornos de funções.

## Estrutura do Projeto

- **`pilha.h`**: Contém as definições das estruturas `Frame` e `Pilha`, além dos protótipos das funções de manipulação da pilha.
- **`pilha.c`**: Implementação das funções da pilha (push, pop, etc.).
- **`main.c`**: Aplicação principal que simula o fluxo de execução com um menu de comandos interativo.

## Compilação e Execução

Para compilar o programa, você precisa compilar os arquivos `pilha.c` e `main.c` juntos. Use o seguinte comando com o compilador GCC:

```sh
gcc main.c pilha.c -o stack