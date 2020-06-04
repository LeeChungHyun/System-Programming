//server side
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX 1024
#define PORT 30000
#define BACKLOG 5

void communication(void* ClientSocketDiscriptor)
{
	int client = *((int *)ClientSocketDiscriptor);
	int bytes;
	char buffer[MAX];
	while(1)
	{
		bytes = recv(client, buffer, MAX, 0);
		if(bytes == 0) break;
		else if (bytes < 0)
		{
			fprintf(stderr,"can't receive data.\n");
			exit(1);
		}
		if(send(client, buffer, bytes, 0) != bytes)
		{
			fprintf(stderr, "can't send data.\n");
			exit(1);
		}
	}
	pthread_exit(0);
}

int main(void)
{
	int sd, nsd, cliaddsize;
	struct sockaddr_in cliaddr, servaddr;
	pthread_t* pthread;

	if((sd = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		fprintf(stderr,"can't open socket.\n");
		exit(1);
	}

	memset(&cliaddr, 0, sizeof(cliaddr));
	memset(&servaddr, 0 ,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if(bind(sd, (struct socketaddr*)&servaddr, sizeof(servaddr))<0)
	{
		fprintf(stderr,"can't bind to socket.\n");
		exit(1);
	}

	listen(sd, BACKLOG);

	while(1)
	{
		cliaddsize = sizeof(cliaddr);
		if((nsd = accept(sd, (struct sockaddr*)&cliaddr, &cliaddsize))<0)
		{
			fprintf(stderr,"can't accept connection.\n");
			exit(1);
		}
		pthread = (pthread_t*)malloc(sizeof(pthread_t));
		pthread_create(pthread,NULL,communication,&nsd);
		if(pthread_detach(pthread) != 0)
			printf("Thread detach fail.\n");
	}
	return 0;
}
