// Esempio che mostra la realizzazione di un comando cp (copia di file)
//Programma preso dalle slide del professore

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define DIMBUF 1024
#define PERMESSI 0755

int main(int argc, char **argv){
    int stato, fin, fout, n;
    char buffer[DIMBUF];
    if(argc != 3){
	printf("Errore nel comando\n");
	exit(1);
    }
    if((fin = open(argv[1], O_RDONLY)) < 0){
	printf("Errore lettura file\n");
	exit(1);
    }
    if((fout = open(argv[2], O_CREAT|O_WRONLY, PERMESSI)) < 0){
	printf("Errore scrittura file\n");
	exit(1);
    }
    while((n=read(fin,buffer,DIMBUF)) > 0)
	if(write(fout, buffer,n) < n){
	    close(fin);
	    close(fout);
	    exit(1);
	}
    close(fin);
    close(fout);
    exit(0);
}
