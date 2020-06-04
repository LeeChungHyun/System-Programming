//client side
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX 1024
#define PORT 30000
#define HOSTADDR "127.0.0.1"
//SERVER IP(LOOPBACK)

int main(void)
{
	int sd, send_bytes, recv_bytes, n;
	struct sockaddr_in servaddr;
	char snddata[MAX], recvdata[MAX];

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(HOSTADDR);
	servaddr.sin_port = htons(PORT);

	if((sd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		fprintf(stderr,"can't open socket.\n");
		exit(1);
	}

	if(connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		fprintf(stderr,"can't connect to server.\n");
		exit(1);
	}

	while(fgets(snddata,MAX,stdin) != NULL)
	{
		send_bytes = strlen(snddata);
		if(send(sd, snddata, send_bytes, 0) != send_bytes)
		{
			fprintf(stderr,"can't send data.\n");
			exit(1);
		}

		recv_bytes = 0;
		while(recv_bytes<send_bytes)
		{
			if((n = recv(sd, recvdata, MAX, 0)) < 0)
			{
				fprintf(stderr,"can't receive data.\n");
				exit(1);
			}
			recv_bytes+=n;
		}
		recvdata[recv_bytes] = '\0';
		fputs(recvdata,stdout);
	}
	close(sd);
	return 0;
}
