#include <direct.h>
//unix에는 #include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


int main(){
    int fd[2];
    int input, output;
    int n; 
    char buf[10];

    pipe(fd);
    if(fork() == 0){
        input = open("input.dat",0);
        close(fd[0]);
        while((n = read(input, buf, 10)) != 0)
            write(fd[1], buf, n);
        close(input);
        close(fd[1]);
        exit(0);
    }
    else{
        close(fd[1]);
        output = open("output.dat", 0666);
        while((n = read(fd[0], buf, 10)) != 0)
            write(output, buf, n);
        close(output);
        close(fd[0]);
        wait();
    }
}
