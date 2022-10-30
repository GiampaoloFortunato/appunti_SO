#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int n;

void *f(){
    int i=0;
    for(i=0;i<n;i++){
	printf("Numero: %d \n", i);
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
    if(pthread_create(&th1, NULL, f(), "") < 0){
	printf("Errore nella creazione del thread 1\n");
	exit(1);
    }
    if(pthread_create(&th2, NULL, f(), "") < 0){
	printf("Errore nella creazione del thread 2\n");
	exit(1);
    }
    if(pthread_create(&th3, NULL, f(), "") < 0){
	printf("Errore nella creazione del thread 3\n");
	exit(1);
    }
    if(pthread_create(&th4, NULL, f(), "") < 0){
	printf("Errore nella creazione del thread 4\n");
	exit(1);
    }
    if(pthread_create(&th5, NULL, f(), "") < 0){
	printf("Errore nella creazione del thread 4\n");
	exit(1);
    }
    if(pthread_create(&th6, NULL, f(), "") < 0){
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

/*
./thread2 500000  0,36s user 0,68s system 97% cpu 1,071 total
./thread2 500000  1,01s user 2,32s system 97% cpu 3,416 total

./thread2 5000000  3,49s user 7,26s system 96% cpu 11,130 total
./thread2 5000000  10,07s user 21,04s system 95% cpu 32,692 total


./thread2 1000000  0,67s user 1,45s system 96% cpu 2,186 total
./thread2 1000000  2,75s user 5,86s system 97% cpu 8,806 total

./thread2 1000000  3,92s user 8,32s system 97% cpu 12,574 total
*/

