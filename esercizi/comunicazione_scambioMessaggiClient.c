#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>

#define SERVER_QUEUE_NAME "/mq_server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10

char msg[60] = "ciao mondo";

int main(){
    mqd_t qd_server;

    struct mq_attr attr;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = sizeof(msg);
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    qd_server = mq_open(SERVER_QUEUE_NAME, O_WRONLY);
    int i=0;
    while(i < 100){
        char msg1[64];
        sprintf(msg1, "%s - %d", msg, i);

        mq_send(qd_server, (char*)&msg1, sizeof(msg),0);
        i++;
    }
}