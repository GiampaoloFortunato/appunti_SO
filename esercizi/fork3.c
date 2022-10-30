#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int n = 10;

void f(){
    int i=0;
    for(i=0;i<n;i++){
	printf("Numero: %d Da: %d\n", i, getpid());
    }
}

void main_fork(){
    pid_t ret = fork();
    if(ret == -1)
	return;
    if(ret == 0){
	f();
    }
    else{
	f();
    }
}

void main_senza_fork(){
    f();
    f();
}

int main(int argc, char *argv[]){
    if(argc > 0)
	n = atoi(argv[1]);

    main_fork();
    //main_senza_fork();
}
