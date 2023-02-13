#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t M;
pthread_cond_t cond_turno;
int turno = 0;

void *th_figlio(void *arg){
    int id= (int*) arg;
    while(1){
        //prologo
        //verifico con while se turno == id, wait
        //operazioni nella sezione critica
        //sleep(1)
        //signal
        //epilogo
    }
}

int main(){
    const num_th = 2;
    pthread_t th[num_th];

    pthread_mutex_init(&M, NULL);
    pthread_cond_init(&cond_turno);

    for(int i=0; i<num_th; i++){
        if(pthread_create(&th[i], NULL, th_figlio, (int*) i) != 0){
            printf("errore\n");
            exit(0);
       }
    }

    while(1){
        pthread_mutex_lock(&M);
        while(turno != 2){pthread_cond_wait(&cond_turno, &M)}
        //operazioni sezione critica
        turno = 0;
        pthread_cond_signal(&cond_turno);
        pthread_mutex_unlock(&M);
    }
}
