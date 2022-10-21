//Comunicazione tra processo con modello produttore/consumatore, tramite pipe
//Programma preso dalle slide del professore

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

struct message_t{
    int numero;
    char text[64];
} msg;

int main(int argc, char *argv[]){
    int fd, i=0, n=10;
    int size = sizeof(msg);
    srand(time(NULL)); //seme per random
    mknod("mia_pipe", S_IFIFO|0666,0); //crea file FIFO
    
    //A seconda del numero di parametri in input eseguo come produttore o consumatore
    if(argc == 2)
	fd = open("mia_pipe", O_WRONLY); //PRODUTTORE
    else
	fd = open("mia_pipe", O_RDONLY); //CONSUMATORE
    
    strcpy(msg.text, "Auguri");
    for(i=0;i<n;i++){
	if( argc == 2){
	    //produttore
	    msg.numero = rand()%100+1; //numero casuale
	    printf("produttore: %s %d \n", msg.text, msg.numero);
	    write(fd, &msg, size); //scrive messaggio in pipe
	    sleep(1); //sospensione per 1 secondo
	}else{
	    //consumatore
	    read(fd, &msg, size); //legge messaggio dalla pipe
	    printf("consumatore: %s %d\n", msg.text, msg.numero);
	    sleep(1);
	}
    }

}
