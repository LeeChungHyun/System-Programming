#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024 // max KB input length
#define PORT 30000 // server port #
#define HOSTADDR “xxx.xxx.xxx.xxx” // server IP

int main (int argc, char *argv[])
{
int sd, send_bytes, n, recv_bytes;
struct sockaddr_in servaddr;
char snddata[MAX], rcvdata[MAX];
bzero ((char*) &servaddr, sizeof(servaddr)); // prepare server address, port
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr (HOSTADDR);
servaddr.sin_port = htons (PORT);
if (( sd = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
fprintf( stderr, "can't open socket.\n");
exit(1);
}
if (connect (sd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
fprintf (stderr, "can’t connect to server.\n");
exit(1);
} // auto binding for this client and connect request

while (fgets (snddata, MAX, stdin) != NULL) { // get a string from KB
send_bytes = strlen (snddata);
if (send (sd, snddata, send_bytes, 0) != send_bytes) { // to server
fprintf( stderr, "can't send data.\n");
exit(1);
}
recv_bytes = 0;
while (recv_bytes < send_bytes) { // while loop for stream I/O !
if ((n = recv (sd, rcvdata + recv_bytes, MAX, 0)) < 0) { // from server
fprintf (stderr, "can't receive data.\n");
exit(1);
}
recv_bytes += n;
}
rcvdata[recv_bytes] = 0; // NULL char for string
fputs (rcvdata, stdout); // display
}
close (sd);
return 0;
}
