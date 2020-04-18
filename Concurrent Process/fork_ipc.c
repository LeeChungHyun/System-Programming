#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <wait.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int pipe1[2],pipe2[2];//0 = read, 1 = write
	int fd,n;
	char buffer[10];

	if((fd = open("inputfile.txt",O_RDONLY)) < 0)
	{
		printf("file not exist or unable to access file\n");
		return 0;
	}
	pipe(pipe1);
	if(fork()==0)//child process
	{
		close(pipe1[1]);
		pipe(pipe2);
		if(fork()==0)//grand child process
		{
			close(pipe2[1]);
			while((n = read(pipe2[0],buffer,10))!= 0)
			{
				for(int i=0;i<n;i++)
					printf("%c",buffer[i]);
			}
			close(pipe2[0]);
			exit(0);
		}
		else//child process
		{
			close(pipe2[0]);
			while((n = read(pipe1[0],buffer,10))!= 0){
				for(int i=0; i<10; i++)
					if(buf[i] >='a' && buf[i] <='z')
						buf[i] = buf[i] -32;

				write(pipe2[1],buffer,n);
			}
			close(pipe2[1]);
			wait();
			exit(0);
		}
	}
	else//parent process
	{
		close(pipe1[0]);
		output = creat("outputfile.txt", 0666);
		while((n = read(fd,buffer,10))!= 0)
		{
			write(pipe1[1],buffer,n);
		}
		close(output);
		close(pipe1[1]);
		wait();
	}
	return 0;
}

