/*Realizzare un programma in C, completo di commento, che svolga quanto segue:
Un processo genera due processi figli P1 e P2. Il figlio P1 esegue un ciclo indeterminato durante il quale genera casualmente numeri interi compresi tra 0 e 1023. 
P1 comunica, ad ogni iterazione, il numero al padre solo se esso è dispari. 
P2 fa la stessa cosa ma comunica al padre solo i numeri pari. 
Il padre, per ogni coppia di numeri che riceve dai figli ne fa la somma e la visualizza. 
Il programma deve terminare quando la somma dei due numeri ricevuti supera il valore 1024: il padre, allora, invia un segnale di terminazione a ciascuno dei figli. (4 punti)*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int getRand(int min, int max){
    return rand()%(max-min+1)+min;
}

void f(){
}

int main(){
    pid_t pid1, pid2;
    mknod("pipe1", S_IFIFO|0666, 0);
    mknod("pipe2", S_IFIFO|0666, 0);

    pid1 = fork();

    if(pid1 == 0){
	int fd1 = open("pipe1", O_WRONLY);
	srand(time(NULL));
    	signal(SIGUSR1, f);
	while(1){
	    int x = getRand(1, 1024);
	    if( x%2 != 0){
		write(fd1, &x, sizeof(int));
		printf("P1: x=%d\n", x);
		pause();
	    }
	}
    }
    else if(pid1 > 0){
	pid2 = fork();
	if(pid2 == 0){
	    int fd2 = open("pipe2", O_WRONLY);
	    srand(time(NULL));
	    signal(SIGUSR1, f);
	    while(1){
		int y = getRand(1, 1024);
		if( y%2 == 0){
		    write(fd2, &y, sizeof(int));
		    printf("P2: y=%d\n", y);
		    pause();
		}
	    }
	}
	else if(pid2 > 0){
	    int fd1 = open("pipe1", O_RDONLY);
            int fd2 = open("pipe2", O_RDONLY);
	    while(1){
		int x, y;
		read(fd1, &x, sizeof(int));
                read(fd2, &y, sizeof(int));
                printf("Messaggio da figlio 1: %d - Messaggio da figlio 2: %d\n", x, y);
		if( x + y > 1724){
		    printf("M: Somma=%d\n", x+y);
		    kill(pid1, SIGKILL);
		    kill(pid2, SIGKILL);
		    exit(0);
		}
		kill(pid1, SIGUSR1);
		kill(pid2, SIGUSR1);
		
	    }
	}
	else{	printf("errore nella fork2\n");    }
    }
    else{   printf("errore nella fork1\n");    }
}
