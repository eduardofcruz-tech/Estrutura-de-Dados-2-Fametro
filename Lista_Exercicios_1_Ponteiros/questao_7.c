#include <stdio.h>
#include <string.h>

// Função para inverte uma string usando ponteiros.
void inverterString(char *str) {
    char *inicio = str;
    char *fim = str + strlen(str) - 1;
    char temp;

    // Troca os caracteres das pontas para o centro.
    while (inicio < fim) {
        temp = *inicio;
        *inicio = *fim;
        *fim = temp;

        inicio++;
        fim--;
    }
}

int main() {
    char minhaString[] = "eduardo";

    printf("String original: %s\n", minhaString);

    inverterString(minhaString);

    printf("String invertida: %s\n", minhaString);

    return 0;
}