//Creazione di un processo figlio che esegue un nuovo programma (con execl
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t ret = fork();
    int stato;

    if(ret == 0){
	printf("processo figlio con pid:%d\n", getpid());
	execl("./consumatore", (char*)0);
	printf("execl fallita \n");
	exit(1);
    }else if(ret > 0){
	printf("Processo padre con pid:%d\n", getpid());
	execl("./produttore", (char*)0);
	ret = wait(&stato);
    }else{printf("errore nella fork\n");}
}
