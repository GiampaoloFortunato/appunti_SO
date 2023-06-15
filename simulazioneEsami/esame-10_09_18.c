/**
Realizzate un programma multi-thread in C, completo di commento, che svolga quanto segue:
Il thread main crea una matrice di numeri interi di dimensione NxM assegnando a ciascun elemento della matriceun valore casuale compreso tra 1 e 100. 
Dopo aver creato la matrice, il thread main crea 2 thread produttori,
 il primo dei quali ha il compito di eseguire la somma delle righe dispari della matrice e il secondo la somma delle righe pari. 
La somma di tutte le righe della matrice deve essere memorizzata in una variabile TOT che il thread main visualizzerà sullo schermo prima che l’applicazione termini.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10
#define M 11

int mat[N][M];
int TOT = 0;
pthread_mutex_t mutex;

void *codice_prod(void *arg){
    int somma = 0, i, j;
    
    for(i = (int) arg; i < N; i+=2){
        for(j=0; j<M; j++){
            somma += mat[i][j];
        }
    }
    pthread_mutex_lock(&mutex);
    TOT += somma;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

int main(){
    pthread_t th[2];
    srand(time(NULL));
    int i, j;
    
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            mat[i][j] = rand()%101;
        }
    }

    pthread_mutex_init(&mutex, NULL);

    for(i=0; i<2; i++){
        if(pthread_create(&th[i], NULL, codice_prod, (int *)i) < 0){
            printf("Errore nel creare thread: %d\n", i);
        }
    }
    for(i=0; i<2; i++){
        pthread_join(th[i],NULL);
    }

    printf("VALORE: %d\n", TOT);
}