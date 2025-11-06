#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
// Programa Abuelo-Hijo-Nieto: Comunicación entre procesos usando pipes.
int main() {
    // Declaración de variables
    pid_t pid, Hijo_pid, pid2, Hijo2_pid;
    int fd1[2]; 
    int fd2[2]; 
    char buffer[80] = "";

    // Mensajes
    char saludoAbuelo[] = "Saludos del Abuelo.";
    char saludoPadre[]  = "Saludos del Padre..";
    char saludoHijo[]   = "Saludos del Hijo...";
    char saludoNieto[]  = "Saludos del Nieto..";

    // Creación de los pipes
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("Error al crear pipes");
        exit(EXIT_FAILURE);
    }
    // Creación del proceso hijo
    pid = fork(); 
    // Crear proceso hijo
    if (pid < 0) {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    }
    // Proceso hijo
    if (pid == 0) {
        // Creación del proceso nieto
        pid2 = fork(); 
        // Crear proceso nieto
        switch (pid2) {
            // Gestión de errores y casos de padre e hijo
            case -1:
                perror("Error al crear el proceso nieto");
                exit(EXIT_FAILURE);
            // Proceso nieto
            case 0:
                // Leer mensaje del padre (Hijo)
                close(fd2[1]); 
                read(fd2[0], buffer, sizeof(buffer));
                printf("\t\tNIETO RECIBE mensaje de su padre: %s\n", buffer);
                close(fd2[0]);

                // Enviar mensaje al padre (Hijo)
                printf("\t\tNIETO ENVÍA mensaje a su padre...\n");
                close(fd1[0]); 
                write(fd1[1], saludoNieto, strlen(saludoNieto) + 1); 
                close(fd1[1]);
                break;
            // Proceso padre (Hijo)
            default:
                // Leer mensaje del abuelo
                close(fd1[1]); 
                read(fd1[0], buffer, sizeof(buffer));
                printf("\tHIJO RECIBE mensaje del ABUELO: %s\n", buffer);
                close(fd1[0]);

                // Enviar mensaje al nieto
                close(fd2[0]); 
                write(fd2[1], saludoPadre, strlen(saludoPadre) + 1);
                close(fd2[1]);
                // Esperar a que el nieto termine
                Hijo2_pid = wait(NULL); 

                // Leer mensaje del nieto
                close(fd1[1]); 
                read(fd1[0], buffer, sizeof(buffer));
                printf("\tHIJO RECIBE mensaje de su hijo: %s\n", buffer);
                close(fd1[0]);
                // Enviar mensaje al abuelo
                printf("\tHIJO ENVÍA mensaje al ABUELO...\n");
                close(fd2[0]); 
                write(fd2[1], saludoHijo, strlen(saludoHijo) + 1);
                close(fd2[1]);
                break;
        }
    // Proceso abuelo
    } else {
        // Enviar mensaje al hijo
        printf("ABUELO ENVÍA mensaje al HIJO...\n");
        close(fd1[0]); 
        write(fd1[1], saludoAbuelo, strlen(saludoAbuelo) + 1);
        close(fd1[1]);
        // Esperar a que el hijo termine
        Hijo_pid = wait(NULL); 

        // Leer mensaje del hijo
        close(fd2[1]); 
        read(fd2[0], buffer, sizeof(buffer));
        printf("EL ABUELO RECIBE mensaje del HIJO: %s\n", buffer);
        close(fd2[0]);
    }
    // Finalización del programa
    return 0;
}
