#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int n;

void *f(void *arg){
    int i=0;
    for(i=0;i<n;i++){
	printf("Numero: %d da Thread:%s\n", i, (char*)arg);
    }
    pthread_exit(0);
}

void *f2(){
    int i=0;
    for(i=0;i<n;i++){
	printf("Numero: %d\n", i);
    }
}

void con_thread_main(){
    pthread_t th1, th2, th3, th4, th5, th6;
    if(pthread_create(&th1, NULL, f, "1") < 0){
	printf("Errore nella creazione del thread 1\n");
	exit(1);
    }
    if(pthread_create(&th2, NULL, f, "2") < 0){
	printf("Errore nella creazione del thread 2\n");
	exit(1);
    }
    if(pthread_create(&th3, NULL, f, "3") < 0){
	printf("Errore nella creazione del thread 3\n");
	exit(1);
    }
    if(pthread_create(&th4, NULL, f, "4") < 0){
	printf("Errore nella creazione del thread 4\n");
	exit(1);
    }
    if(pthread_create(&th5, NULL, f, "5") < 0){
	printf("Errore nella creazione del thread 4\n");
	exit(1);
    }
    if(pthread_create(&th6, NULL, f, "6") < 0){
	printf("Errore nella creazione del thread 4\n");
	exit(1);
    }
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);
    pthread_join(th5, NULL);
    pthread_join(th6, NULL);
}

void senza_thread_main(){
    f2();
    f2();
    f2();
    f2();
    f2();
    f2();
}

int main(int argc, char *argv[]){
    n = atoi(argv[1]);

    con_thread_main();
    //senza_thread_main();
}


