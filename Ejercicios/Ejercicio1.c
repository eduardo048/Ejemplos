#include <stdio.h>    
#include <stdlib.h>     
#include <unistd.h>     
#include <sys/wait.h>   

int main(void) {
    // Declaración e inicialización de la variable
    int variable = 6;
    pid_t pid;  

    // Mostramos el valor inicial de la variable
    printf("Valor inicial de la variable: %d\n", variable);

    // Creamos un nuevo proceso
    pid = fork();

    if (pid < 0) {
        // Manejo de error en la creación del proceso hijo
        perror("Error al crear el proceso hijo");
        return 1; 
    } 
    else if (pid == 0) {
        // Este bloque lo ejecuta solo el proceso hijo

        // El proceso hijo resta 5 a la variable
        variable -= 5;

        // Muestra el nuevo valor de la variable en el proceso hijo
        printf("Variable en Proceso Hijo: %d\n", variable);

        // El proceso hijo termina su ejecución
        exit(0);
    } 
    else {
        // Este bloque lo ejecuta solo el proceso padre

        // El proceso padre espera a que el hijo termine
        wait(NULL);

        // El proceso padre suma 5 a la variable
        variable += 5;

        // Muestra el nuevo valor de la variable en el proceso padre
        printf("Variable en Proceso Padre: %d\n", variable);
    }

    // Fin del programa
    return 0;
}
