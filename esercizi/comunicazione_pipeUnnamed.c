#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define LEGGI 0
#define SCRIVI 1
#define DIM 256

int main(){
    int n, fd[2];
    char msg[DIM];
    pid_t pid;
    
    if(pipe(fd) < 0){
        printf("Errore pipe\n");
        exit(1);
    }

    pid = fork();

    if( pid == 0 ){
        //CONSUMATORE
        close(fd[SCRIVI]);
        n = read(fd[LEGGI], msg, DIM);
        printf("Messaggio letto: %s\n", msg);
    }else if ( pid > 0 ) {
        //PRODUTTORE
        close(fd[LEGGI]);
        write(fd[SCRIVI], "messaggio 1", DIM);
    }
}