//Comunicazione tra processi - memoria condivisa con modello produttore-consumatore
//Programma preso da slide professore

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h> // costanti mode
#include <fcntl.h> // costanti O_
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(){
    const int SIZE = 4096; //dimensione del segmento condiviso
    const char *nome = "MEMCOND"; //nome del segmento
    void *shm_ptr; //puntatore al segmento condiviso
    
    //DATI SCRITTI IN MEMORIA CONDIVISA
    const char *string_0 = "Saluti";
    const char *string_1 = "a tutti!";
    int shm_fd; //file descripto del segmento
    
    //CREA IL SEGMENTO DI MEMORIA CONDIVISA
    shm_fd = shm_open(nome, O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, SIZE); //imposto dimensione segmento
    
    //MEMORY MAP DEL SEGMENTO
    shm_ptr=mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sprintf(shm_ptr, "%s", string_0); //scrive nel segmento
    shm_ptr += strlen(string_0);
    sprintf(shm_ptr, "%s", string_1);
    shm_ptr += strlen(string_1);
    return 0;
}
