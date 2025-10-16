#include <stdio.h>
#include <string.h>
int main(void) {
    char cadena[256];
    printf("Introduce una cadena: ");
    if (fgets(cadena, sizeof(cadena), stdin) == NULL) {
        fprintf(stderr, "Error al leer la cadena.\n");
        return 1;
    }
    cadena[strcspn(cadena, "\n")] = '\0';
    printf("Cadena introducida: %s\n", cadena);
    return 0;
}