#include <stdio.h>
#include <ctype.h>

// Conta vogais e consoantes em uma string, retornando os valores por ponteiro.
void contarVogaisConsoantes(char *str, int *vogais, int *consoantes) {
    *vogais = 0;
    *consoantes = 0;

    // Percorre a string até o final.
    while (*str != '\0') {
        char letra = tolower(*str);

        // Verifica se é uma letra.
        if (letra >= 'a' && letra <= 'z') {
            // Se for vogal, incrementa vogais.
            if (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u') {
                (*vogais)++;
            } else {
                // Caso contrário, é consoante.
                (*consoantes)++;
            }
        }
        str++;
    }
}

int main() {
    char texto[] = "Eduardo Franca";
    int numVogais, numConsoantes;

    // Passa o texto e os endereços das variáveis para a função.
    contarVogaisConsoantes(texto, &numVogais, &numConsoantes);

    printf("string: %s\n", texto);
    printf("Vogais: %d\n", numVogais);
    printf("Consoantes: %d\n", numConsoantes);

    return 0;
}