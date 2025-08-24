#include <stdio.h>

// Calcula as quatro operações e armazena os resultados usando ponteiros.
void calcular(float a, float b, float *soma, float *sub, float *mult, float *div) {
    // Realiza os cálculos.
    *soma = a + b;
    *sub = a - b;
    *mult = a * b;

    // Evita divisão por zero.
    if (b != 0) {
        *div = a / b;
    } else {
        *div = 0;
    }
}

int main() {
    float num1 = 10.0;
    float num2 = 2.0;
    
    // Declara as variáveis para guardar os resultados.
    float resSoma, resSub, resMult, resDiv;

    // Chama a função, passando os números e os endereços das variáveis.
    calcular(num1, num2, &resSoma, &resSub, &resMult, &resDiv);

    // Imprime os resultados.
    printf("Resultados:\n");
    printf("Soma: %.2f\n", resSoma);
    printf("Subtracao: %.2f\n", resSub);
    printf("Multiplicacao: %.2f\n", resMult);
    printf("Divisao: %.2f\n", resDiv);

    return 0;
}