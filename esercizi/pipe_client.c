#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define NAME_PIPE "my_pipe"
#define NUM 10

struct message_t{
    int numero;
    char text[64];
} msg;

int main(){
    int fd;

    mknod(NAME_PIPE, S_IFIFO|0666, 0);

    fd = open(NAME_PIPE, O_RDONLY);
    for(int i=0; i < NUM; i++){
	read(fd, &msg, sizeof(msg));
	printf("consumatore: %s%d\n", msg.text, msg.numero);
	sleep(1);
    }
}
