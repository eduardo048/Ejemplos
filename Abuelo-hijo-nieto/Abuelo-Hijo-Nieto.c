#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

// Programa Abuelo-Hijo-Nieto: Comunicación entre procesos usando pipes y switch.
// Ahora con impresión de PIDs y control de procesos mediante estructuras switch.

int main(){
    // Declaración de variables
    pid_t pid, Hijo_pid, pid2, Hijo2_pid;
    int fd1[2]; // Pipe para comunicación ABUELO <-> HIJO / NIETO -> HIJO
    int fd2[2]; // Pipe para comunicación HIJO <-> NIETO / HIJO -> ABUELO
    char buffer[80] = "";

    // Mensajes
    char saludoAbuelo[] = "Saludos del Abuelo.";
    char saludoPadre[]  = "Saludos del Padre..";
    char saludoHijo[]   = "Saludos del Hijo...";
    char saludoNieto[]  = "Saludos del Nieto..";

    // Creación de los pipes
    if(pipe(fd1) == -1 || pipe(fd2) == -1){
        perror("Error al crear pipes");
        exit(EXIT_FAILURE);
    }
    // Creación del proceso hijo (desde el ABUELO)
    pid = fork();

    switch(pid){
        // Gestión de errores
        case -1:
            perror("Error al crear el proceso hijo");
            exit(EXIT_FAILURE);

        // Proceso HIJO
        case 0:
            printf("\t[HIJO] PID = %d, PPID = %d\n", getpid(), getppid());

            // Creación del proceso nieto (desde el HIJO)
            pid2 = fork();

            switch(pid2){
                // Gestión de errores
                case -1:
                    perror("Error al crear el proceso nieto");
                    exit(EXIT_FAILURE);

                // Proceso NIETO
                case 0:
                    printf("\t\t[NIETO] PID = %d, PPID = %d\n", getpid(), getppid());

                    // Leer mensaje del padre (HIJO)
                    close(fd2[1]); // Cierra escritura del pipe 2
                    read(fd2[0], buffer, sizeof(buffer)); // Lee del pipe 2
                    printf("\t\tNIETO RECIBE mensaje de su padre: %s\n", buffer);
                    close(fd2[0]); // Cierra lectura

                    // Enviar mensaje al padre (HIJO)
                    printf("\t\tNIETO ENVÍA mensaje a su padre...\n");
                    close(fd1[0]); // Cierra lectura del pipe 1
                    write(fd1[1], saludoNieto, strlen(saludoNieto) + 1); // Escribe al pipe 1
                    close(fd1[1]); // Cierra escritura
                    break;

                // Proceso padre del NIETO (es decir, el HIJO)
                default:
                    // Leer mensaje del ABUELO
                    close(fd1[1]); // Cierra escritura del pipe 1
                    read(fd1[0], buffer, sizeof(buffer)); // Lee del pipe 1
                    printf("\tHIJO RECIBE mensaje del ABUELO: %s\n", buffer);
                    close(fd1[0]); // Cierra lectura

                    // Enviar mensaje al NIETO
                    close(fd2[0]); // Cierra lectura del pipe 2
                    write(fd2[1], saludoPadre, strlen(saludoPadre) + 1); // Escribe al pipe 2
                    close(fd2[1]); // Cierra escritura

                    // Esperar a que el NIETO termine
                    Hijo2_pid = wait(NULL);

                    // Leer mensaje del NIETO
                    close(fd1[1]); // Cierra escritura del pipe 1
                    read(fd1[0], buffer, sizeof(buffer)); // Lee del pipe 1
                    printf("\tHIJO RECIBE mensaje de su hijo: %s\n", buffer);
                    close(fd1[0]);

                    // Enviar mensaje al ABUELO
                    printf("\tHIJO ENVÍA mensaje al ABUELO...\n");
                    close(fd2[0]); // Cierra lectura del pipe 2
                    write(fd2[1], saludoHijo, strlen(saludoHijo) + 1); // Escribe al pipe 2
                    close(fd2[1]); // Cierra escritura
                    break;
            }
            break;
        // Proceso ABUELO
        default:
            printf("[ABUELO] PID = %d\n", getpid());

            // Enviar mensaje al HIJO
            printf("ABUELO ENVÍA mensaje al HIJO...\n");
            close(fd1[0]); // Cierra lectura del pipe 1
            write(fd1[1], saludoAbuelo, strlen(saludoAbuelo) + 1); // Escribe al pipe 1
            close(fd1[1]); // Cierra escritura

            // Esperar a que el HIJO termine
            Hijo_pid = wait(NULL);

            // Leer mensaje del HIJO
            close(fd2[1]); // Cierra escritura del pipe 2
            read(fd2[0], buffer, sizeof(buffer)); // Lee del pipe 2
            printf("EL ABUELO RECIBE mensaje del HIJO: %s\n", buffer);
            close(fd2[0]); // Cierra lectura
            break;
    }
    return 0;
}
