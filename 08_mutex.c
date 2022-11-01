//Programma preso dalle slide del professore
/* ESEMPIO - MUTEX
 * Il thread main iniziale crea due thread di nome Th1 e Th2.
 * I due thread condividono la variabile intera A alla quale inizialmente è assegnato il valore 10.
 * Il thread Th1 incrementa di 1 il valore di A e attende 1 secondo,
 * mentre Th2 decrementa di 1 il valore di A e attende 1 secondo.
 * Entrambi i thread eseguono le operazioni suddette per 10 volte, quindi teminano
 * */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int A = 10; //variabile condivisa
pthread_mutex_t M; //mutex per mutua esclusione

void *codice_Th1(void *arg){
    int i;
    for(i=0; i<10; i++){
	printf("Thread %s: ", (char *)arg);
	pthread_mutex_lock(&M); //prologo sezione critica
	A++;
	printf("A=%d\n",A);
	pthread_mutex_unlock(&M); //epilogo sezione critica
	sleep(1);
    }
    pthread_exit(0);
}
void *codice_Th2(void *arg){
    int i;
    for(i=0; i<10; i++){
	printf("Thread %s: ", (char *)arg);
	pthread_mutex_lock(&M); //prologo sezione critica
	A--;
	printf("A=%d\n",A);
	pthread_mutex_unlock(&M); //epilogo sezione critica
	sleep(1);
    }
    pthread_exit(0);
}
int main(){
    pthread_t th1, th2;

    //creazione e attiviazione del primo thread
    if(pthread_create(&th1, NULL, codice_Th1, "th1") != 0){
	fprintf(stderr, "Errore di creazione thread 1\n");
	exit(1);
    }
    //creazione e attivazione del secondo thread
    if(pthread_create(&th2, NULL, codice_Th2, "th2") != 0){
	fprintf(stderr, "Errore di creazione thread 1\n");
	exit(1);
    }

    //attesa della terminazione del primo thread
    if(pthread_join(th1, NULL) != 0)
	fprintf(stderr, "join fallito \n");
    else
	printf("terminato il thread 1\n");
    //attesa della terminazione del secondo thread
    if(pthread_join(th2, NULL) != 0)
	fprintf(stderr, "join fallito \n");
    else
	printf("terminato il thread 2\n");
    return 0;
}
