#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>  

// Programa que crea un pipe entre un proceso padre y un proceso hijo.
// El proceso hijo envía un mensaje al proceso padre a través del pipe.

int main(void){
    // Descriptores del pipe: fd[0] para lectura, fd[1] para escritura 
    int fd[2];  
    // Buffer para almacenar el mensaje leído             
    char buffer[30];
    // Identificador del proceso
    pid_t pid;

    // Crear el pipe
    if(pipe(fd) == -1){
        perror("pipe");
        return 1;
    }

    // Crear proceso hijo
    pid = fork();
    if(pid == -1){
        perror("fork");
        return 1;
    }

    if(pid == 0){
        // === HIJO ===
        const char *msg = "Hola papa!\n";

        close(fd[0]);

        // escribir en el pipe
        ssize_t n = write(fd[1], msg, strlen(msg) + 1);
        // manejar error de escritura
        if(n == -1){
            perror("write");
            // cerramos antes de salir
            close(fd[1]);
            exit(1);
        }

        close(fd[1]);
        exit(0);
    } else {
        // === PADRE ===
        close(fd[1]);

        // esperar a que el hijo termine
        wait(NULL);

        // leer del pipe
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        // manejar error de lectura
        if(n == -1){
            perror("read");
            close(fd[0]);
            return 1;
        }
        // asegurar que el buffer esté null-terminated
        if(n >= 0){
            buffer[n] = '\0';
        }
        // mostrar el mensaje leído
        printf("El PADRE leyó del pipe:\n\tMensaje leído: %s\n", buffer);

        close(fd[0]); 
    }
    return 0;
}
