#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>     // open()
#include <unistd.h>    // read(), write(), close()

int main(void)
{
    char saludo[] = "Un saludo!!!\n";
    char buffer[10];
    int fd, bytesleidos;

    // Abrir fichero para escritura (1 = solo escritura)
    fd = open("texto.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        printf("ERROR AL ABRIR EL FICHERO PARA ESCRITURA...\n");
        exit(-1);
    }

    printf("Escribo el saludo...\n");
    write(fd, saludo, strlen(saludo)); // escribo en el archivo
    close(fd); // cierro el fichero

    // Abrir fichero para lectura (0 = solo lectura)
    fd = open("texto.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("ERROR AL ABRIR EL FICHERO PARA LECTURA...\n");
        exit(-1);
    }

    printf("Contenido del fichero:\n");

    // Leo byte a byte y lo guardo en buffer
    bytesleidos = read(fd, buffer, 1);
    while (bytesleidos != 0)
    {
        printf("%c", buffer[0]); // imprimo el byte leído
        bytesleidos = read(fd, buffer, 1); // leo el siguiente byte
    }

    close(fd); // cierro el fichero

    return 0;
}
