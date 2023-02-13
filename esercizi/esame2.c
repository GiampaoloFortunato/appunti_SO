#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define MIN 0
#define MAX 1000
#define MASSIMO 18000

pthread_mutex_t M;
pthread_cond_t cond_turno;
int x[2] = {0,0};
int turno=0;

int genrand(int min, int max){
    return rand()%(max-min+1)+min;
}

void *th_figlio(void *arg){
    srand(time(NULL) + (int*)arg);
    int id = (int*) arg;
    while(1){
        //prologo sezione critica
        pthread_mutex_lock(&M);
        while(turno != id){pthread_cond_wait(&cond_turno, &M);}
        x[id] = genrand(MIN, MAX);
        turno++;
        printf("thread %d: x=%d\n", id, x[id]);
        sleep(1);
        pthread_cond_signal(&cond_turno);
        //epilogo
        pthread_mutex_unlock(&M);
    }
}

int main(){
    int somma = 0;
    pthread_t TH[2];

    pthread_mutex_init(&M, NULL);
    pthread_cond_init(&cond_turno, NULL);
    for(int i=0; i<2; i++){
        if(pthread_create(&TH[i], NULL, th_figlio, (int*) i) != 0){
            printf("Errore\n");
            exit(0);
        }
    }

    while(1){
        pthread_mutex_lock(&M);
        while(turno != 2){pthread_cond_wait(&cond_turno, &M);}
        somma = x[0] + x[1] + somma;
        printf("somma: %d\n", somma);
        if(somma > MASSIMO || x[0] == x[1]){exit(0);}
        turno = 0;
        pthread_cond_signal(&cond_turno);
        pthread_mutex_unlock(&M);
    }
}
