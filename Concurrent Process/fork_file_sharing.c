#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]{
    int fd;
    int fdout;
    int i;
    int readbyte;
    char buf[10];

    fd = open(argv[1], 0);

    if(fd<0)
        printf("open error, %d\n", fd);

    if(fork() == 0){
        int pid = getpid();
        char i = '1';

        while((readbyte = read(fd, buf, 10)) !=0){
            printf("%d, %s\n", pid, buf);
            write(fdout, buf, readbyte);
            write(fdout, "\n", sizeof(char));
            sleep(1);
            exit(0);
        }
    }
    else{
        if (fork() == 0)
        {
            int pid = getpid();
            char i = '2';

            while ((readbyte = read(fd, buf, 10)) != 0)
            {
                printf("%d, %s\n", pid, buf);
                write(fdout, buf, readbyte);
                write(fdout, "\n", sizeof(char));
                sleep(1);
                exit(0);
            }
        }
        else{
            int pid = getpid();
            char i = '3';

            while ((readbyte = read(fd, buf, 10)) != 0)
            {
                printf("%d, %s\n", pid, buf);
                write(fdout, buf, readbyte);
                write(fdout, "\n", sizeof(char));
                sleep(1);
                exit(0);
            }
        }
    }
close(fdout);
}
