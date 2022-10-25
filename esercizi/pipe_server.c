//Comunicazione tra processi tramite pipe. Uso del modello produttore-consumatore
//PRODUTTORE
//il produttore sarà il server che genererà numeri casuali

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#define NAME_PIPE "my_pipe"
#define NUM 10

struct message_t{
    int numero;
    char text[64];
} msg;

int main(){
    int fd;
    srand(time(NULL));
    //creo file FIFO
    mknod(NAME_PIPE, S_IFIFO|0666, 0);

    fd = open(NAME_PIPE, O_WRONLY);

    strcpy(msg.text, "Numero: ");
    for(int i=0; i < NUM; i++){
	msg.numero = rand()%100+1;
	
	printf("Produttore: %s%d\n", msg.text, msg.numero);

	write(fd, &msg, sizeof(msg));
	sleep(1);
    }
}
