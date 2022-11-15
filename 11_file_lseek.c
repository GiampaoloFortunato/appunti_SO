//Esempio che mostra come realizza l'accesso diretto mediante la lseek
//Programma preso dalle slide del professore

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

struct Persona{
    int id;
    char cognome[40], nome[20], tel[16];
} persona;

int main(){
    int fd, size, n, i=0;
    size = sizeof(persona);
    fd = open("./persone.db", O_CREAT|O_RDWR);
    persona.id = 10;
    strcpy(persona.cognome, "Fortunato");
    strcpy(persona.nome, "Giampaolo");
    strcpy(persona.tel, "3922557322");
    lseek(fd, size*i, SEEK_SET);
    write(fd, &persona, size);
    i++;
    persona.id = 11;
    strcpy(persona.cognome, "D'Amico");
    strcpy(persona.nome, "Giulia");
    strcpy(persona.tel, "3492107193");
    lseek(fd, size*i, SEEK_SET);
    write(fd, &persona, size);
    i++;
    persona.id = 12;
    strcpy(persona.cognome, "Rossi");
    strcpy(persona.nome, "Mario");
    strcpy(persona.tel, "3394515477");
    lseek(fd, size*i, SEEK_SET);
    write(fd, &persona, size);
    close(fd);
    fd = open("./persone.db", O_RDONLY);
    i = 1; //posiziona la lettura al primo record
    lseek(fd, size*i, SEEK_SET);
    read(fd, &persona, size);
    printf("cognome %s\n", persona.cognome);
    close(fd);

}
