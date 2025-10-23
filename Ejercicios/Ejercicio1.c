#include <stdlib.h>     
#include <unistd.h>     
#include <stdio.h>      
#include <sys/wait.h>   

void main() {
    // Variable compartida entre padre e hijo
    int variable = 6;   
    pid_t pid, Hijo_pid;

    printf("Valor inicial de la variable: %d\n", variable);

    /// Crear proceso hijo
    pid = fork();

    // Evaluar el valor retornado por fork()
    switch (pid) {
        case -1:
            // Error al crear el proceso hijo
            printf("No se ha podido crear el proceso hijo...\n");
            exit(-1);
            break;

        case 0:
            // === PROCESO HIJO ===
            printf("\tSoy el proceso HIJO (PID: %d)\n", getpid());
            printf("\tLa variable vale %d, la decremento en 5...\n", variable);

            // Decrementar la variable en 5
            variable -= 5;

            printf("\tAhora la variable en el HIJO vale: %d\n", variable);

            // Terminar el proceso hijo correctamente
            exit(0);
            break;

        default:
            // === PROCESO PADRE ===
            printf("Soy el proceso PADRE (PID: %d), espero a que termine mi hijo...\n", getpid());

            // Espera la finalización del hijo
            Hijo_pid = wait(NULL);

            printf("Mi hijo (PID: %d) ha terminado.\n", Hijo_pid);
            printf("La variable vale %d, la incremento en 5...\n", variable);

            // Incrementar la variable en 5
            variable += 5;

            printf("Ahora la variable en el PADRE vale: %d\n", variable);
    }
    exit(0);
}
