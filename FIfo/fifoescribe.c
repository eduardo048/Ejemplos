#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "FIFO2"

int main(void){
    const char *saludo = "Un saludo!!!\n";
    const char *edu = "Hola me llamo eduardo\n";
    int fd = open(FIFO_NAME, O_WRONLY);

    if(fd == -1){
        perror("Error al abrir FIFO para escritura");
        exit(EXIT_FAILURE);
    }
    printf("Escribiendo en el FIFO...\n");
    write(fd, saludo, strlen(saludo));
    write(fd, edu, strlen(edu));
    close(fd);

    return 0;
}
