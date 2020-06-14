#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#define BUFFER_SIZE 128
#define FIFO1 "fifo-client"
#define FIFO2 "fifo-server"
void* fifo_server(void* FIFO){
	
	int fd;
	char buffer[BUFFER_SIZE];


        if((fd = open(FIFO, O_RDONLY)) == -1){
                perror("open failed");
                exit(1);
        }


        while(1){
                if(read(fd, buffer, BUFFER_SIZE) == -1){
                        perror("read failed");
                        exit(1);
                }

                printf("\n[SERVER] %s", buffer);
                
                if(!strcmp(buffer, "quit\n")){
			printf("[CLIENT] ");
			printf("Quit chatting\n");
                        exit(0);
		}
		printf("[CLIENT] ");
		fflush(stdout);
        }
	close(fd);
}

int main(){

        int fd2;
	char buffer2[BUFFER_SIZE]; 
	pthread_t p_thread;


        if((fd2 = open(FIFO2, O_WRONLY)) == -1){
                perror("open failed");
                exit(1);
	}


        pthread_create(&p_thread, NULL, fifo_server, (void*)FIFO1);

        while(1){
                printf("[CLIENT] ");
                fgets(buffer2, BUFFER_SIZE, stdin);

                if(write(fd2, buffer2, BUFFER_SIZE) == -1){
                        perror("write failed");
                        exit(1);
                }
                if(!strcmp(buffer2, "quit\n")){
			printf("Quit chatting\n");
                        exit(0);
		}
        }
	
        pthread_join(p_thread,NULL);
	close(fd2);
	return 0;
}