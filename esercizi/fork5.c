/*Realizzate un programma in C, completo di commento, che svolga quanto segue:
un processo padre P scrive un messaggio su un file, quindi genera due processi figli P1 e P2 e attende che terminino. 
Il figlio P1 inizializza una variabile X al valore 100 e quindi si blocca. 
P2 esegue un ciclo infinito durante il quale genera ogni secondo un numero intero casuale compreso tra 1 e 200. 
Quando P2 estrae il numero X, definito da P1, invia un segnale a P1 per risvegliarlo e P2 termina.
P1, riattivato dal segnale che ha ricevuto da P2, legge il file scritto dal padre e lo visualizza sullo schermo e l’applicazione multi processo termina. (4 punti)*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int *x = 0;

int myRand(int min, int max){
    return rand()%(max-min+1)+min;
}

int main(){
    
    pid_t pid1, pid2;
    srand(time(NULL));
    pid1 = fork();
    if(pid1 == 0){
	
	x = 100;
	printf("P1: %d - %p\n", x, &x);
    }else if(pid1 > 0){
	pid2 = fork();
	if(pid2 == 0){
	    int y = 0;
	    while(y < 150){
		y = myRand(1, 200);
		printf("P2: %d - %p\n", x, &x);
		printf("P2: %d\n", y);
		
	    }
	}else if(pid2 > 0){
	    //padre
	}
	else{//errore
	     }
    }else{//errore
    }
}
