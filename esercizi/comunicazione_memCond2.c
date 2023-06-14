#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

const char *NOME = "MEMCOND";
const int SIZE = 4096;

struct buffer_t{char txt[64];} *buffer;

int main(){
    pid_t pid;

    int shm_fd = shm_open(NOME, O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    buffer = mmap(0, SIZE,PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    pid = fork();

    if(pid == 0){
        //CONS
        sleep(1);
        printf("Ha scritto: %s\n", buffer->txt);
    }
    else if(pid > 0){
        //PROD
        char *stringa = "ciao";
        strcpy(buffer->txt, stringa);
    }
}