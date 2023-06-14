/**
Realizzate un programma multi processo in C, che svolga quanto segue:
un processo P crea un processo figlio P1. 
I due processi, padre e figlio, comunicano mediante una coda di messaggi POSIX secondo il modello produttore-consumatore.
Il processo figlio (produttore) scrive continuamente, ogni 500 ms, un messaggio di tipo intero nella coda; 
il processo padre (consumatore) legge i messaggi dalla coda e li visualizza sullo schermo. 
Il programma termina quando il consumatore legge il messaggio di valore 10. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#define MAX_MSG 10
#define QUEUE_NAME "/mq_coda"
#define PERMISSION 0666

int main(){
    pid_t pid;
    srand(time(NULL));
    struct mq_attr attr;
    attr.mq_curmsgs = 0;
    attr.mq_msgsize = sizeof(int);
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MSG;

    mqd_t qd;
    pid = fork();

    if(pid == 0){
        //PRODUTTORE
        qd = mq_open(QUEUE_NAME, O_WRONLY);
        int x;
        while(1){
            x = rand()%100;
            mq_send(qd, &x, sizeof(int), 0);
            sleep(0.5);
        }
    }else if(pid > 0){
        //CONSUMATORE
        sleep(2);
        qd = mq_open(QUEUE_NAME, O_CREAT|O_RDONLY, PERMISSION, &attr);
        int y;
        while(1){
            mq_receive(qd, &y, sizeof(int), NULL);
            printf("Il padre ha letto: %d\n", y);
            if(y == 10){
                kill(pid, SIGKILL);
                mq_close(qd);
                mq_unlink(QUEUE_NAME);
                exit(0);
            }
        }
    }
}