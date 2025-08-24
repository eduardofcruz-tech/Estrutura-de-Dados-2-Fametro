#include <stdio.h>

// A função 'troca' recebe dois ponteiros para inteiros como parâmetros e realiza a troca dos valores das variaveis.
void troca(int *a, int *b) {
    int temp = *a; 
    *a = *b;
    *b = temp;
}

int main() {
    int num1, num2;

    // Solicita e lê o valor da primeira variável
    printf("Digite o valor da primeira variavel: ");
    scanf("%d", &num1);

    // Solicita e lê o valor da segunda variável
    printf("Digite o valor da segunda variavel: ");
    scanf("%d", &num2);

    printf("\n--- Antes da troca ---\n");
    printf("Primeira variavel: %d\n", num1);
    printf("Segunda variavel: %d\n", num2);

    // Chama a função 'troca', passando os endereços de memória das variáveis
    troca(&num1, &num2);

    printf("\n--- Depois da troca ---\n");
    printf("Primeira variavel: %d\n", num1);
    printf("Segunda variavel: %d\n", num2);

    return 0;
}