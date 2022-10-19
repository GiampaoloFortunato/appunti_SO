//CONDIVISIONE DI MEMORIA CON MODELLO PRODUTTORE-CONSUMATORE
//Programma preso dalle slide del professore

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int N=5;
char nome[][20] = {"Pietro", "Antonio", "Laura", "Luisa", "Lino"};

struct buffer_t{
    int id;
    char text[64];
} *buffer;

//Processo produttore
void produttore(){
    int i;
    for(i=0; i<N; i++){
	buffer->id=1;
	strcpy(buffer->text, nome[i]);
	printf("messaggio scritto: %d %s\n", buffer->id, buffer->text);
	usleep(200);
    }
}

//processo consumatore
void consumatore(){
    int i;
    for(i=0;i<N;i++){
	printf("messaggio letto: %d %s\n", buffer->id, buffer->text);
	usleep(200);
    }
}

int main(){
    pid_t pid;
    int shm_id, SIZE;
    shm_id = shm_open("MEMCOND", O_CREAT|O_RDWR, 0666);
    SIZE = sizeof(struct buffer_t);
    ftruncate(shm_id, SIZE);
    buffer = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_id, 0);
    pid = fork();
    if(pid == 0){
	produttore();
    }else{
	consumatore();
	shm_unlink("MEMCOND");
	wait(NULL);
    }

}
