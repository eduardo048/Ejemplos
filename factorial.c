#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    char buffer[64];
    char *endptr = NULL;
    long numero = 0;
    unsigned long long factorial = 1;

    printf("Introduce un numero entero no negativo: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error al leer el numero.\n");
        return 1;
    }

    errno = 0;
    numero = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Entrada invalida.\n");
        return 1;
    }

    if (numero < 0) {
        fprintf(stderr, "El numero debe ser no negativo.\n");
        return 1;
    }

    for (long i = 2; i <= numero; ++i) {
        factorial *= (unsigned long long)i;
    }

    printf("Factorial de %ld es %llu\n", numero, factorial);
    return 0;
}
