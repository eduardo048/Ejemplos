#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(){
    pid_t pid, Hijo_pid;
    int retorno = 0;
    pid = fork();
    
    if(pid == -1){
        printf("No se ha podido crear el proceso hijo...");
        retorno = -1;
    }else{
        if(pid == 0){
            printf("Soy el proceso hijo \n\t Mi PID es %d",
                "El PID de mi padre es: %d.\n",
                getpid(), getppid());
        }else{
            Hijo_pid = wait(NULL);
            printf("Soy el proceso padre:\n\t Mi PID es %d" ,
                "El PID de mi padre es: %d.\n\t",
                "I hijo: %d termino. ",
                getpid(), getppid(), pid,"\n"); 
        }
    }
    printf("Fin del programa");
    exit(retorno);
}