//Nuovo file da eseguire

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int i;
    printf("Processo chiamato da execl con PID:%d e PPID:%d \n", getpid(), getppid());
    for(i=0; i<argc; i++){
	//visualizzo i parametri d'ingresso
	printf("%s \n", argv[i]);
    }
}
