//Comunicazione tra processi - scambio di messaggi
//Programma preso dalle slide del professore
//SERVER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>
#define SERVER_QUEUE_NAME "/mq_server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10

struct message{
    int pid;
    char text[64];
} msg_send, msg_rcv;

int main(int argc, char *argv[]){
    mqd_t qd_server, qd_client; //descrittori code
    long serial_number = 1; //numero seriale da inviale al client
    char client_queue_name[16]; //nome coda del client
    struct mq_attr attr; //attributi della coda
    attr.mq_flags = 0; //bloccante
    attr.mq_maxmsg = MAX_MESSAGES; //numero massimo di messaggi della coda
    attr.mq_msgsize = sizeof(msg_rcv);
    attr.mq_curmsgs = 0;

    printf("Server: Benvenuto!\n");
    
    qd_server = mq_open(SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr);
    
    while(1){
		//preleva dalla coda il messaggio più vecchio con più alta priorità
		mq_receive(qd_server, (char*)&msg_rcv, sizeof(msg_rcv), NULL);
		printf("Server: messaggio ricevuto dal client:%d, %s \n", msg_rcv.pid, msg_rcv.text);
		sprintf(client_queue_name, "/mq_%d", msg_rcv.pid);
		//Invia il messaggio di risposra al client
		qd_client = mq_open(client_queue_name, O_WRONLY);
		sprintf(msg_send.text, "Benvenuto client %d, il tuo numero e' %ld", msg_rcv.pid, serial_number);
		
		mq_send(qd_client, (const char *)&msg_send, sizeof(msg_send), 0);
		printf("Server: risposta inviata al client. \n");
		serial_number++; //incrementa il serial numb
	}
}
