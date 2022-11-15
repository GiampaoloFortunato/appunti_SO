// Esempio che illustra il caso in cui due processi (padre e figlio) acchedono allo stesso file e ne condividono anche lìI/O pointer
// Programma preso dalle slide del professore

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define N 10

int main(){
    int i, fd1, fd2, pid;
    fd1 = open("file.txt", O_CREAT|O_WRONLY, 0777);
    pid = fork();
    if(pid == 0){
	fd2 = open("priv.txt", O_CREAT|O_WRONLY, 0777);
	for(i=0; i<N; i++){
	    write(fd1, "figlio\n", 6);
	    sleep(1);
	    write(fd2, "figlio\n", 6);
	}
	close(fd2);
    }else if(pid > 0){
	for(i=0;i<N;i++){
	    write(fd1, "padre\n", 5);
	    sleep(1);
	}
	close(fd1);
    }
}
