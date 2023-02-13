#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void stampa(){
    printf("ciao da: %d\n", getpid());
    exit(1);
}

int main(){
    signal(SIGUSR1, stampa);
    pid_t pid = fork();

    if(pid == 0){
        for(;;){
            
            printf("pid figlio:%d\n", getpid());
            pause();
        }
    }else if(pid > 0){
        for(int i=0; i<30; i++){
            printf("a\n");
            kill(pid, SIGUSR1);
        }
    }else{
        return 0;
    }
}
