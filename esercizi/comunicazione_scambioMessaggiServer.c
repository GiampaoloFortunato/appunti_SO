#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>

#define SERVER_QUEUE_NAME "/mq_server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10

char msg[60];

int main(){
    mqd_t qd_server;

    struct mq_attr attr;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = sizeof(msg);
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    qd_server = mq_open(SERVER_QUEUE_NAME, O_CREAT|O_RDONLY, QUEUE_PERMISSIONS, &attr);
    printf("IN ATTESA ... \n");
    while(1){
        mq_receive(qd_server, (char *)&msg, sizeof(msg), NULL);
        printf("Ho ricevuto: %s\n", msg);
    }
}