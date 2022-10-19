//Esempio banale di creazione di un processo figlio

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();

    if(pid == 0){
	printf("Sono il pid figlio: %d\n", getpid());
    }else if(pid > 0){
	printf("Sono il pid padre: %d\n", getpid());
    }else{
	printf("errore nella fork\n");
    }

}
