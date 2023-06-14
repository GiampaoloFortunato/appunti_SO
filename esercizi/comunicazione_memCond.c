#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>

const char *NOME = "MEMCOND";
const int SIZE = 4096; 
struct buffer_t{char txt[64];} *buffer;
int main(){
    pid_t pid;

    //Creo il segmento di memoria condivisa
    int shm_fd = shm_open(NOME, O_CREAT|O_RDWR, 0666);
    //Dimensiono il segmento (in byte)
    ftruncate(shm_fd, SIZE);
    //Creo il file mappato corrispondente al segmento creato
    buffer = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    pid = fork();

    if( pid < 0 ){  printf("Errore\n"); }

    if( pid == 0 ){
        //CONSUMATORE
        sleep(1);
        printf("Ha scritto: %s\n", buffer->txt);
        shm_unlink(NOME);exit(0);
    }else if ( pid > 0) {
        //PRODUTTORE
        char *stringa = "ciao";
        strcpy(buffer->txt, stringa);
        shm_unlink(NOME);
        int stato;
        wait(&stato);
    }

}