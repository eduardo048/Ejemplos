// fifocrea.c - Crea FIFO y lee datos

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "FIFO2"
#define BUFFER_SIZE 128

int main(void) {
    if(mkfifo(FIFO_NAME, 0666) == -1){
        perror("Error al crear el FIFO");
    }

    char buffer[BUFFER_SIZE];
    int fd;
    ssize_t bytes_leidos;

    while(1){
        printf("Esperando datos...\n");
        fd = open(FIFO_NAME, O_RDONLY);
        if(fd == -1){
            perror("Error al abrir FIFO para lectura");
            exit(EXIT_FAILURE);
        }
        while((bytes_leidos = read(fd, buffer, sizeof(buffer) - 1)) > 0){
            buffer[bytes_leidos] = '\0';
            printf("Leído: %s", buffer);
        }

        close(fd);
    }

    return 0;
}
