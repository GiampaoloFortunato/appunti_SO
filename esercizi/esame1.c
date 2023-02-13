#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

void gestore(){
    exit(1);
}

int main(){
    signal(SIGUSR1, gestore);
    mknod("pipe1", S_IFIFO|0666, 0);
    mknod("pipe2", S_IFIFO|0666, 0);
    int prod1, prod2, cons1, cons2, num1, num2, sum=0;
    pid_t pid1, pid2;

    pid1 = fork();
    if(pid1 == 0){
        srand(time(NULL));
        while(1){
            printf("sono vivo!: %d\n", getpid());
            prod1 = open("pipe1", O_WRONLY);
            num1 = rand() % 1024;
            if(num1%2 == 0){
                write(prod1, &num1, sizeof(int));
            }
        }
    }
    else if(pid1 > 0){
        pid2 = fork();
        if(pid2 == 0){
            srand(time(NULL));
            while(1){
                printf("sono vivo: %d\n", getpid());
                prod2 = open("pipe2", O_WRONLY);
                num2 = rand() %1024;
                if(num2%2 == 1){
                    write(prod2, &num2, sizeof(int));
                }
            }
        }
        else if(pid2 > 0){
            cons1 = open("pipe1", O_RDONLY);
            cons2 = open("pipe2", O_RDONLY);
            int ok=1;
            while(ok){
                int n1, n2;
                read(cons1, &n1, sizeof(int));
                read(cons2, &n2, sizeof(int));
                sum = sum + n1 + n2;
                if(sum > 1023){
                    kill(pid1, SIGUSR1);
                   kill(pid2, SIGUSR2);
                    ok = 0;
                }
                printf("%d\n", sum);
            }
        }
    }
}
