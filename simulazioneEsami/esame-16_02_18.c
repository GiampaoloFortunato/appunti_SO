/**
Realizzate un programma multi-thread con modello master-worker in C, che svolga quanto segue:
Il thread main (master) crea 20 nuovi thread (worker) ad intervalli di tempo compresi tra 1 e 3 secondi e quindi si
sospende. I worker creati possono essere di due tipi: Tipo1 e Tipo2. La scelta del tipo è casuale. Un worker di Tipo1
aggiunge, ogni secondo, ad una variabile TOT condivisa, un valore casuale compreso tra 1 e 100. Un worker di
Tipo2, invece, sottrae, ogni secondo, al valore di TOT un valore casuale compreso tra 1 e 50. Se un worker estrae il
numero 17 si blocca e può essere riattivato solo da un altro thread del suo stesso tipo. L’applicazione termina
quando un thread estrae il valore 13. Prima di terminare il thread main stampa sullo schermo il valore di TOT. (5
punti)

*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define TH_MAX 20

int TOT = 0;
int VAR = 0;
pthread_mutex_t mutex;
pthread_cond_t condizione1, condizione2;

int getRand(int min, int max){
    return rand()%(max-min+1)+min;
}

void *tipo1(){
    while(1){
        int prod = getRand(1, 100);
        if(VAR == 1) {
            pthread_exit(0);
        }
        pthread_mutex_lock(&mutex);
        if(prod == 17){
            pthread_cond_wait(&condizione1, &mutex);
        }
        if (prod == 13){
            VAR = 1;
            printf("tot momentaneo: %d\n", TOT);
        }
        TOT += prod;
        pthread_cond_signal(&condizione1);
        pthread_mutex_unlock(&mutex);
    }
}

void *tipo2(){
    int prod2 = getRand(1, 50);
    if(VAR == 1) {
        pthread_exit(0);
    }
    while(1){
        pthread_mutex_lock(&mutex);
        if(prod2 == 17){
            pthread_cond_wait(&condizione2, &mutex);
        }
        if (prod2 == 13){
            VAR = 1;
            printf("tot momentaneo: %d\n", TOT);
        }
        TOT -= prod2;
        pthread_cond_signal(&condizione2);
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    srand(time(NULL));
    pthread_t th[TH_MAX];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condizione1,NULL);
    pthread_cond_init(&condizione2,NULL);
    for(int i=0; i< TH_MAX; i++){
        int time = rand()%4;
        //sleep(time);
        if(rand() > 0.5){
            pthread_create(&th[i], NULL, tipo1, NULL);
        }else{
            pthread_create(&th[i], NULL, tipo2, NULL);
        }
    }

    for (int i=0;i < TH_MAX; i++) {
        pthread_join(th[i], NULL);
    }
    printf("Il valore TOT: %d\n", TOT);
}