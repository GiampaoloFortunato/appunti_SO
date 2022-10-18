//Creazione di un processo in POSIX
//Programma preso dalle slide del professore e commentato.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    //creazione di un processo con la funzione fork
    //la funzione fork restuisce -1 in caso di fallimento
    //altrimenti restituirà due valori:
    // - Il valore 0 al processo figlio
    // - un valore >0, ovvero il PID del processo figlio sarà ritornato al processo padre
    pid_t ret;
    ret = fork();

    //Per quanto detto sopra possiamo separare il codice del padre da quello del figlio
    //ovvero tramite il valore ritornato della funzione
    

    if(ret == -1){ //CONDIZIONE DI ERRORE NELLA CREAZIONE
	printf("Errore nella fork\n");
	exit(0);
	//con il metodo exit terminiamo il processo.
	//il parametro nel metodo (ovvero 0) indica lo stato
	//lo stato consente al processo figlio di comunicare al processo padre lo stato di uscita (tramite valore intero)
    }else if(ret == 0){ //GESTIAMO IL CODICE DEL FIGLIO
	//codice del figlio
	printf("ciao, sono il figlio con pid:%d \n", getpid());
    }else if(ret > 0){ //GESTIAMO IL CODICE DEL PADRE
	//codice del padre
	printf("we, sono il padre con pid:%d \n", getpid());
    }

    //CODICE ESEGUITO SIA DA FIGLIO CHE DA PADRE
    printf("Messaggio eseguito da pid:%d \n", getpid());


}
