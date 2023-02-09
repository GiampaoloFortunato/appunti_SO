//Un processo padre crea due figli. Ogni figlio genera un numero che comunicherà al padre. Il padre stampa a schermo ogni numero.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>


int main(){
    int fd1, fd2, num1, num2, cons1, cons2;
    srand(time(NULL));
    //Creo file FIFO
    mknod("pipe1", S_IFIFO|0666, 0);
    mknod("pipe2", S_IFIFO|0666, 0);
    pid_t pid1, pid2;
    pid1 = fork();
    if(pid1 < 0){
        printf("errore\n");
        return 0;
    }
    //Figlio1
    if(pid1 == 0){
        fd1 = open("pipe1", O_WRONLY);
        while(1){
            num1 = (rand()*rand())%100+1;
            write(fd1, &num1, sizeof(int));
            sleep(1);
        }
    }else if(pid1 > 0){
        pid2 = fork();
        //Figlio2
        if(pid2 == 0){
            fd2 = open("pipe2", O_WRONLY);
            while(1){
                num2 = rand()%100+1;
                write(fd2, &num2, sizeof(int));
                sleep(1);
            }
        }
        //Padre
        if(pid2 > 0){
            fd1 = open("pipe1", O_RDONLY);
            fd2 = open("pipe2", O_RDONLY);
            while(1){
                read(fd1, &cons1, sizeof(int));
                read(fd2, &cons2, sizeof(int));
                printf("Messaggio da figlio 1: %d - Messaggio da figlio 2: %d\n", cons1, cons2);
                sleep(1);
            }
        }
    }
}
