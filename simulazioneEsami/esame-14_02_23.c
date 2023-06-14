/**
* Un processo server di nome MusicServer fornisce a processi client un servizio di testi di canzoni. 
* Più precisamente, un client invia al server un messaggio di richiesta, 
* contenente il titolo della canzone e il nome dell’artista e il server risponde al client con un messaggio di risposta contenente 
* il testo della canzone. 
* Dopo aver ottenuto il testo, il client lo visualizza sullo schermo.
* Considerando di avere a disposizione il codice del server, realizzate un’applicazione in C che implementi il comportamento del client, 
* in modo che i processi client e server comunichino mediante code di messaggi POSIX. (6 punti)
*/
#include <stdlib.h>
#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SERVER_NAME "/mq_server"
#define QUEUE_PERMISSIONS 0666

struct msg_t{char artista[64]; char titolo[100]; int pid;} msg;
int main(){
    mqd_t qd_server, qd_client;
    char client_name[16];
    sprintf(client_name, "/mq_%d", getpid());

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;
    attr.mq_msgsize = sizeof(msg);
    attr.mq_maxmsg = 1;
    
    qd_server = mq_open(SERVER_NAME, O_WRONLY);
    qd_client = mq_open(client_name,O_CREAT|O_RDONLY, QUEUE_PERMISSIONS, &attr);
    
    msg.pid = getpid();
    strcpy(msg.titolo, "titoletto");
    strcpy(msg.artista,"artista");
    
    mq_send(qd_server, (char *)&msg, sizeof(msg),0);
    
    char msg_ptr[100];
    mq_receive(qd_client, (char *)&msg_ptr, sizeof(msg_ptr),NULL);

    printf("Ecco il testo: %s\n", msg_ptr);
}

/** SERVER

#include <stdlib.h>
#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>

#define SERVER_NAME "/mq_server"
#define QUEUE_PERMISSIONS 0666

char canzone[100] = "canzone canzone ble vla bla";

struct msg_t{char artista[64]; char titolo[100];int pid;} msg;
int main(){
    mqd_t qd_server, qd_client;
    char client_name[16];

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;
    attr.mq_msgsize = sizeof(msg);
    attr.mq_maxmsg = 1;

    qd_server = mq_open(SERVER_NAME, O_CREAT|O_RDONLY, QUEUE_PERMISSIONS, &attr);

    mq_receive(qd_server, (char *)&msg, sizeof(msg),NULL);
    
    printf("PID: %d\n", msg.pid);
    
    sprintf(client_name,"/mq_%d",msg.pid);
    qd_client = mq_open(client_name,O_WRONLY);
    mq_send(qd_client, (char *)&canzone, sizeof(canzone),0);
    
}
*/