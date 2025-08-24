#include <stdio.h>

// A função que encontra o maior e o menor
void encontrarMaiorMenor(int *array, int tamanho, int *maior, int *menor) {
    // 1. Assume que o primeiro número é o maior e o menor
    *maior = array[0];
    *menor = array[0];

    // 2. Percorre o resto do array
    for (int i = 1; i < tamanho; i++) {

        // Se achar um número maior, atualiza o 'maior'
        if (array[i] > *maior) {
            *maior = array[i];
        }
        
        // Se achar um número menor, atualiza o 'menor'
        if (array[i] < *menor) {
            *menor = array[i];
        }
    }
}

int main() {
    int numeros[] = {5, 55, -30, 89, 90, -10};
    int tamanho = 6;

    int maior_encontrado;
    int menor_encontrado;

    // Chama a função, passando os endereços das variáveis de resultado
    encontrarMaiorMenor(numeros, tamanho, &maior_encontrado, &menor_encontrado);

    printf("Maior valor: %d\n", maior_encontrado);
    printf("Menor valor: %d\n", menor_encontrado);

    return 0;
}