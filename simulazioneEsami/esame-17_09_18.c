/**
Realizzate un programma multi thread in C, completo di commento, che simuli il comportamento di elettori che si recano ad un seggio elettorale per votare,
 in base alle seguenti specifiche:
- gli elettori arrivano al seggio in istanti di tempo casuale;
- nel seggio possono essere presenti al massimo 4 elettori allo stesso tempo;
- un elettore deve attendere sulla porta se nel seggio sono già presenti 4 elettori;
- quando entra nel seggio, un elettore impiega un tempo random, compreso tra TMIN e TMAX, per votare.
L'applicazione, durante l'esecuzione, deve visualizzare i seguenti messaggi, in accordo con gli stati in cui si può
trovare l'elettore:
- elettore j arriva al seggio
- elettore j attende sulla porta
- elettore j entra nel seggio e vota
- elettore j esce dal seggio
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


#define NUM_TH 15
#define MAX_ELETTORI 4
int elettori = 0;
pthread_mutex_t mutex;
pthread_cond_t condizione;

int myRandTime(int min, int max){
    return rand()%(max-min+1)+min;
}

void *codice_th(void *arg){
    printf("Arrivato al seggio il TH: %d\n", (int*)arg);
    pthread_mutex_lock(&mutex);
    if( elettori == MAX_ELETTORI ){
        pthread_cond_wait(&condizione, &mutex);
    }
    elettori ++;
    pthread_mutex_unlock(&mutex);
    printf("Il TH: %d e' entrato nel saggio\n", (int*) arg);
    int tempo = myRandTime(0, 2);
    sleep(tempo);
    pthread_cond_signal(&condizione);
    pthread_mutex_lock(&mutex);
    elettori--;
    pthread_mutex_unlock(&mutex);
    printf("Il TH: %d ha lasciato il saggio\n", (int*) arg);
    pthread_exit(0);
}

int main(){
    pthread_t th[NUM_TH];
    int i;

    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condizione, NULL);

    for(i=0; i < NUM_TH; i++){
        //creo i thread
        if( pthread_create(&th[i], NULL, codice_th, (int *)i) < 0){
            printf("Errore nella creazione del thread: %d\n", i);
        }
    }

    for(i=0; i < NUM_TH; i++){
        pthread_join(th[i], NULL);
    }
}