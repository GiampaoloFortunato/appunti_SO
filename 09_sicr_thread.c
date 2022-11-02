// SINCRONIZZAZIONI TRA THREAD
//Programma preso dalle slide del professore

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define FINE (-1)
#define MAX 20
#define DIM 10

typedef struct{
    pthread_mutex_t M;
    pthread_cond_t PIENO, VUOTO;
    int messaggio[DIM];
    int leggi, scrivi, cont;
} buffer_t;

buffer_t buf;

void init(buffer_t *buf);
void produci(buffer_t *buf, int mes);
int consuma(buffer_t *buf);

void init(buffer_t *buf){
    pthread_mutex_init(&buf->M, NULL);
    pthread_cond_init(&buf->PIENO, NULL);
    pthread_cond_init(&buf->VUOTO, NULL);
    buf->cont = 0;
    buf->leggi = 0;
    buf->scrivi = 0;
}

void produci(buffer_t *buf, int mes){
    pthread_mutex_lock(&buf->M);
    //il buffer è pieno?
    if(buf->cont == DIM)
	pthread_cond_wait(&buf->PIENO, &buf->M);
    //scrivi mes e aggiorna lo stato del messaggio
    buf->messaggio[buf->scrivi] = mes;
    buf->cont++;
    buf->scrivi++;
    //la gestione del buffer è circolare
    if(buf->scrivi == DIM)
	    buf->scrivi = 0;
    //risveglia un eventuale thread consumatore sospeso
    pthread_cond_signal(&buf->VUOTO);
    pthread_mutex_unlock(&buf->M);
}

int consuma(buffer_t *buf){
    int mes;
    pthread_mutex_lock(&buf->M);
    if(buf->cont == 0)
	    pthread_cond_wait(&buf->VUOTO, &buf->M);
    mes = buf->messaggio[buf->leggi];
    buf->cont--;
    buf->leggi++;
    if(buf->leggi >= DIM)
	buf->leggi = 0;
    pthread_cond_signal(&buf->PIENO);
    pthread_mutex_unlock(&buf->M);
    return mes;
}

void *produttore(void *arg){
    int n;
    for(n=0;n<MAX;n++){
	printf("Produttore %d -> %d\n", (int)arg, n);
	produci(&buf, n);
	sleep(1);
    }
    produci(&buf, FINE);
}

void *consumatore(void *arg){
    int d;
    while(1){
	d = consuma(&buf);
	if(d == FINE)
	    break;
	printf("%d <- consumatore %d\n", d, (int)arg);
	sleep(2);
    }
}

int main(){
    int i;
    int nprod = 1, ncons = 1;
    pthread_t prod[nprod], cons[ncons];
    init(&buf);
    for(i=0; i<nprod; i++)
	pthread_create(&prod[i], NULL, produttore, (void*)i);
    for(i=0; i<ncons; i++)
	pthread_create(&cons[i], NULL, consumatore, (void*)i);

    for(i=0;i<nprod;i++)
	pthread_join(prod[i], NULL);
    for(i=0;i<ncons;i++)
	pthread_join(cons[i], NULL);

    return 0;
}
