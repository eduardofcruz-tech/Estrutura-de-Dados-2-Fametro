#include <stdio.h>

// Função para dobrar o valor de um número usando um ponteiro.
void dobrar(int *ptr) {
    // Acessa e dobra o valor da variável original.
    *ptr = (*ptr) * 2;
}

int main() {
    int numero = 5;

    printf("Valor original: %d\n", numero);

    // Passa o endereço de 'numero' para a função.
    dobrar(&numero);

    printf("Valor após a função dobrar: %d\n", numero);

    return 0;
}