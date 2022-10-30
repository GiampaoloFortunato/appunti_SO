//DIFFERENZA TRA USO DI THREAD E MONO-THREAD
//Per eseguire correttamente il programma:
//  bisogna specificare il numero n (num max che esegue il ciclo) come parametro durante l'esecuzione 
//  ./thread NUMERO
//  per controllare il tempo scrivere: 
//	time ./thread NUMERO

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

int n;

void *f(){
    int i = 0;
    for(i=0;i<n;i++){
	printf("numero: %d da: %d\n", i, getpid());
    }
    pthread_exit(0);
}

void f2(){
    int i = 0;
    for(i=0;i<n;i++){
	printf("numero: %d da: %d\n", i, getpid());
    }
}

void secondo_main(){
    pid_t ret = fork();
    pthread_t primo_thread, secondo_thread;
    int res;
    if(ret == -1)
	return;
    
    if(ret == 0){
	printf("Processo figlio: %d\n", getpid());

	if(pthread_create(&secondo_thread, NULL, f, "") < 0){
	    printf("Thread processo figlio fallito\n");
	    exit(1);
	}
	res = pthread_join(secondo_thread, NULL);
    }else{
	printf("Processo padre: %d\n", getpid());
	if(pthread_create(&primo_thread, NULL, f, "") < 0){
	    printf("Thread processo padre fallito\n");
	    exit(1);
	}
	res = pthread_join(primo_thread, NULL);
	
    }
}

void terzo_main(){
    f2();
    f2();
}

int main(int argc, char *argv[]){
    n = atoi(argv[1]);
    
    //secondo_main();
    terzo_main();
}

/*

./thread 1000000  1,48s user 2,77s system 82% cpu 5,135 total
./thread 1000000  2,75s user 4,08s system 98% cpu 6,907 total

./thread 5000000  7,35s user 14,24s system 84% cpu 25,553 total
./thread 5000000  13,85s user 20,46s system 97% cpu 35,146 total

 * */
