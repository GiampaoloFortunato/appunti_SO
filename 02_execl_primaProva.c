//Esempio execl
//Programma preso dalle slide del professore

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
//OSS: la libreria <unistd.h> è indispensabile per la creazione di processi

int main(){
    pid_t ret;
    int stato;

    ret = fork();

    printf("pid:%d \n", getpid());

    if(ret == 0){
	//Codice figlio
	//OSS: ./nuovo è il file presente nella stessa cartella che verrà eseguito
	//OSS2: nota che il file non è il file.c ma il file una volta compilato, quindi quando si compila tale programma bisogna dargli il giusto nome
	execl("./02_execl_nuovoFile", "Ciao", "dal processo", "padre", (char*)0);
	printf("exec fallita\n");
	exit(1);
    } else if(ret > 0){
	//Codice padre
	printf("Sono il padre con pid:%d \n", getpid());
	ret = wait(&stato);
	printf("stato: %d\n", stato);
    }else{ printf("Errore fork");  }

    printf("OK dal pid:%d\n", getpid());
}
