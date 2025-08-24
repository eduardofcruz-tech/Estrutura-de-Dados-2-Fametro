#include <stdio.h>

// Função para copiar uma string para outra usando ponteiros.
void copiarString(char *stringA, char *stringB)
{
    // Acessa e copia cada caractere até encontrar o terminador nulo '\0'.
    while (*stringA != '\0')
    {
        *stringB = *stringA;
        stringA++;
        stringB++;
    }
    // Adiciona o terminador nulo na string de stringB.
    *stringB = '\0';
}

int main()
{
    char stringInicial[] = "Eduardo França";
    char stringFinal[20]; // Garante que o stringB tenha espaço suficiente.

    printf("String de stringA: %s\n", stringInicial);

    copiarString(stringInicial, stringFinal);

    printf("String de stringB: %s\n", stringFinal);

    return 0;
}