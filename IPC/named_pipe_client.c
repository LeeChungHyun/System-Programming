#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO_FILE "MYFIFO"
#define SIZE 128

int main(void)
{
  FILE *fp;
  char readbuf[SIZE], a[40];
  umask(0);
  mknod(FIFO_FILE, S_IFIFO | 0666, 1);
start:
  fp = fopen(FIFO_FILE, "r");
  fgets(readbuf, 80, fp);
  printf("Him :%s\n", readbuf);
  fclose(fp);
  sleep(1);
  printf("Me : ");
  gets(a);
  fp = fopen(FIFO_FILE, "r+");
  if (a[strlen(a) - 1] == '.')
  {
    fputs(a, fp);
    fclose(fp);
    return 0;
  }
  fputs(a, fp);
  fclose(fp);
  sleep(1);
  goto start;
  return 0;
}
/*
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 128
#define FIFO_FILE "fifo"

int main() {
   int fd;
   int end_process;
   int stringlen;
   int read_bytes;
   char readbuf[SIZE];
   char end_str[10];
   printf("[CLIENT]: Send messages, infinitely, to end enter \"end\"\n");
   fd = open(FIFO_FILE, O_CREAT|O_RDWR);
   strcpy(end_str, "quit");
   
   while (1) {
      printf("Enter string: ");
      fgets(readbuf, sizeof(readbuf), stdin);
      stringlen = strlen(readbuf);
      readbuf[stringlen - 1] = '\0';
      end_process = strcmp(readbuf, end_str);
      
      //printf("end_process is %d\n", end_process);
      if (end_process != 0) {
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         read_bytes = read(fd, readbuf, sizeof(readbuf));
         readbuf[read_bytes] = '\0';
         printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
      } else {
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
         close(fd);
         break;
      }
   }
   return 0;
}
*/