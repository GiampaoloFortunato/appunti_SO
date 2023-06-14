/**
Realizzate un programma multi processo in C, che svolga quanto segue:
un processo P crea un processo figlio P1. 
I due processi padre e figlio comunicano mediante un segmento di memoriacondiviso secondo il modello produttore-consumatore. 
Il processo padre (produttore) scrive un messaggio nel segmento di memoria condiviso e si sospende; 
il processo figlio (consumatore) legge il messaggio dal segmento condiviso, lo visualizza sullo schermo,
 risveglia il processo padre e entrambi i processi terminano.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define NAME "MEM_COND"
#define SIZE 4096

char *msg;

void f(){

}

int main(){
    pid_t pid;
    
    int shm_fd = shm_open(NAME, O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    msg = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);

    pid = fork();

    if(pid == 0){
        //CONSUMATORE
        printf("Padre ha scritto: %s\n", msg);
        kill(getppid(), SIGUSR1);
        exit(0);
    }else if( pid > 0 ){
        //PRODUTTORE
        strcpy(msg, "ciao da padre");
        signal(SIGUSR1, f);
        pause();

        return(0);
    }
}