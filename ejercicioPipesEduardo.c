#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <sys/wait.h>   

// Comunicación entre procesos usando pipes
// El proceso hijo envía un mensaje al proceso padre a través del pipe
// El padre lee el mensaje y lo muestra por pantalla
// Autor: Eduardo 
int main(void){
    // Descriptores del pipe
    int fd[2];               
    char buffer[30];
    pid_t pid;
    // Crear el pipe
    if(pipe(fd) == -1){
        perror("No se pudo crear el pipe");
        exit(-1);
    }
    // Crear proceso hijo
    pid = fork();
    // Evaluar el valor retornado por fork()
    switch(pid) {

        case -1:
            // ERROR
            perror("NO SE HA PODIDO CREAR EL HIJO");
            exit(-1);
            break;

        case 0:
            // === HIJO ===
            printf("HIJO: Escribo en el pipe...\n");
            // El hijo NO lee del pipe
            close(fd[0]); 
            // Escribir mensaje en el pipe
            write(fd[1], "Hola papi", strlen("Hola papi") + 1);
            // Cerrar el extremo de escritura del pipe
            close(fd[1]); 
            exit(0);
            break;

        default:
            // === PADRE ===
            // Esperar a que el hijo termine
            wait(NULL); 
            // El padre NO escribe en el pipe 
            printf("PADRE: Leo del pipe...\n");
            close(fd[1]); 
            // Leer mensaje del pipe
            read(fd[0], buffer, sizeof(buffer));
            // Mostrar el mensaje leído
            printf("\tMensaje leído: %s\n", buffer);
            // Cerrar el extremo de lectura del pipe
            close(fd[0]); 
            break;
    }
    return 0;
}
