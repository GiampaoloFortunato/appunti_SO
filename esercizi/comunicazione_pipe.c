#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define NOME_PIPE "pipe"

int main(){
    int fd;
    char msg[60];
    pid_t pid;

    mknod(NOME_PIPE, S_IFIFO|0666, 0);

    pid = fork();

    if( pid == 0){
        //CONSUMATORE
        fd = open(NOME_PIPE, O_RDONLY);
        read(fd, &msg, sizeof(msg));
        printf("Messaggio letto: %s\n", msg);
    }else if( pid > 0){
        //PRODUTTORE
        fd = open(NOME_PIPE, O_WRONLY);
        write(fd,"CIAO", sizeof(msg));
    }

}