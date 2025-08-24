#include <stdio.h>

int main()
{

    int numero = 42;     // Declara uma variável inteira e a inicializa com um valor
    int *ptrNumero;      // 2. Declara um ponteiro para inteiro.
    ptrNumero = &numero; // 3. Atribui o endereço da variável 'numero' ao ponteiro.

    printf("Valor da variável 'numero': %d\n", numero);
    printf("Endereço da variável 'numero': %p\n", &numero);
    printf("Valor do ponteiro 'ptrNumero': %p\n", ptrNumero);
    printf("Valor apontado por 'ptrNumero': %d\n", *ptrNumero);

    return 0;
}