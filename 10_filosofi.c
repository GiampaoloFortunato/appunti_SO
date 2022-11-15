//Problema dei cinque filosofi
//Programma preso dalle slide del professore

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUMFILOSOFI 5
#define CICLI 100

typedef struct{
    int id;
    pthread_t thread_id;
    char nome[20];
} Filosofo;

//Bacchette sono risorse condivise, quindi ne gestiamo l'accesso in mutua esclusione (con mutex)
pthread_mutex_t bacchetta[NUMFILOSOFI];

void tempoRnd(int min, int max){
    sleep(rand()%(max-min+1) + min);
}

void *filosofo_th(void *id){
    Filosofo fil = *(Filosofo *)id;
    int i;
    for(i=0; i<CICLI; i++){
	printf("Filosofo %d: %s sta pensando \n", fil.id+1, fil.nome);
	tempoRnd(3,12);
	printf("Filosofo %d: %s ha fame\n", fil.id+1, fil.nome);
	//condizione che elimina attesa circolare
	if(fil.id % 2){
	    pthread_mutex_lock(&bacchetta[fil.id]);
	    printf("FIlosofo %d: %s prende la bacchetta destra (%d)\n", fil.id+1, fil.nome, fil.id+1);
	    tempoRnd(1,2);
	    printf("FIlosofo %d: %s prende la bacchetta sinistra (%d)\n", fil.id+1, fil.nome, (fil.id+1)%NUMFILOSOFI+1);
	}else{
	    pthread_mutex_lock(&bacchetta[(fil.id+1) % NUMFILOSOFI]);
	    printf("FIlosofo %d: %s prende la bacchetta sinistra (%d)\n", fil.id+1, fil.nome, (fil.id+1)%NUMFILOSOFI+1);
	    tempoRnd(1,2);
	    pthread_mutex_lock(&bacchetta[fil.id]);
	    printf("FIlosofo %d: %s prende la bacchetta destra (%d)\n", fil.id+1, fil.nome, fil.id+1);
	}
	printf("Filosofo %d: %s sta mangiando \n", fil.id+1, fil.nome);
	tempoRnd(3,10);
	printf("Filosofo %d: %s posa la bacchetta destra (%d)\n", fil.id+1, fil.nome, fil.id+1);
	pthread_mutex_unlock(&bacchetta[fil.id]);
	printf("Filosofo %d: %s posa la bacchetta sinistra (%d)\n", fil.id+1, fil.nome, (fil.id+1) % NUMFILOSOFI+1);
	pthread_mutex_unlock(&bacchetta[(fil.id+1) %NUMFILOSOFI]);
    }
}

int main(int argc, char *argv[]){
    int i;
    char nome[][20] = {"Socrate", "Platone", "Aristotele", "Talete", "Pitagora"};
    Filosofo filosofo[NUMFILOSOFI];
    srand(time(NULL));

    for(i=0; i<NUMFILOSOFI; i++)
	pthread_mutex_init(&bacchetta[i], NULL);

    for(i=0; i<NUMFILOSOFI; i++){
	filosofo[i].id = i;
	strcpy(filosofo[i].nome, nome[i]);
	if(pthread_create(&filosofo[i].thread_id, NULL, filosofo_th, &filosofo[i]))
	    perror("errore phtread_create");
    }

    for(i=0; i<NUMFILOSOFI; i++)
	if(pthread_join(filosofo[i].thread_id, NULL))
	    perror("errore pthread_join");
    return 0;
}
