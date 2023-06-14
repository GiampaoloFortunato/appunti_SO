/*
Realizzate un programma multi processo in C, che svolga quanto segue:
un processo P crea un processo figlio P1. I due processi padre e figlio comunicano mediante un segmento di memoria
condiviso secondo il modello produttore-consumatore. Il processo padre (produttore) scrive un messaggio nel segmento di
memoria condiviso e si sospende; il processo figlio (consumatore) legge il messaggio dal segmento condiviso, lo visualizza
sullo schermo, risveglia il processo padre e entrambi i processi terminano. (6 punti)
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>

const char *NOME = "MEMCOND";
const int SIZE = 4096;

int main(){
    pid_t pid;

    int shm_fd;
    char *buffer;

    shm_fd = shm_open(NOME, O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    buffer = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);

    pid = fork();

    if(pid==0){
        //CONS
        printf("Padre ha scritto: %s\n", buffer);
        shm_unlink(NOME);
        exit(0);
    }else if(pid>0){
        //PROD
        int stato;
        strcpy(buffer, "ciao da padre");
        waitpid(pid, &stato, 0);
    }

}