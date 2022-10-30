//Problema preso dalle slide del professore

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int ns = 1; //periodo iniziale di allarme (1 secondo)
int nmax = 10; //valore massimo dall'intervallo di allarme

void azione(){
    /* questa funzione viene eseguita ogni volta che il processo riceve il segnale SIGALRM */
    printf("Segnale di allarme ricevuto... eseguo date \n");
    system("date"); //esegue il comando date
    /* riassegnamento del periodo di allarme che cancella il precedente periodo assegnato*/
    alarm(ns); //ns viene incrementato
}

int main(){
    int i;
    signal(SIGALRM, azione);
    alarm(ns);
    while( ns <= nmax){
	printf("processo in pausa\n");
	pause();
	printf("fine pausa\n");
	ns = ns * 2; //incremento del periodo di allarme
    }
    exit(0);
}
