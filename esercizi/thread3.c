#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *func(void *arg){
    printf("i: %d - Sono il thread: %d\n", i,(int*)arg);

    pthread_exit(0);
}

int main(){
    pthread_t th1, th2;
    if(pthread_create(&th1, NULL, func, (char*)1) < 0){
	printf("Errore nella creazione del thread 1");
	exit(1);
    }
    if(pthread_create(&th2, NULL, func, (char*)2) < 0){
	printf("Errore nella creazione del thread 2");
	exit(1);
    }
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
}
