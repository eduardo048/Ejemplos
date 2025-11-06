#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
// Ejercicio 1.2: Comunicación entre procesos usando pipe.
int main(void){
    // Declaración de variables
    int fd[2];
    pid_t pid;
    char saludoHijo[] = "Buenos días padre.\0";
    char buffer[80];
    // Creación del pipe y del proceso hijo
    pipe(fd); 
    pid = fork(); 
    // Comunicación entre procesos
    switch(pid) {
        // Gestión de errores y casos de padre e hijo
        case -1 : 
            printf("NO SE HA PODIDO CREAR HIJO...");
            exit(-1);
        // Proceso hijo
        case 0 : 
            close(fd[0]);
            // Cierra el extremo de lectura del pipe
            write(fd[1], saludoHijo, strlen(saludoHijo));
            printf("El HIJO envía algo al pipe.\n");
            close(fd[1]);
            break;
        // Proceso padre
        default : 
            close(fd[1]);
            wait(NULL); 
            // Espera a que el hijo termine
            read(fd[0], buffer, sizeof(buffer)); 
            printf("El PADRE recibe algo del pipe: %s\n", buffer);
            close(fd[0]);
            break;
    }
    // Finalización del programa
    return 0;
}