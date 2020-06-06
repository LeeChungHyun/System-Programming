#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define FIFO_FILE "MYFIFO"
#define SIZE 128
int main()
{
  FILE *fp;
  char a[40];
  char readbuf[SIZE];
start:
  if ((fp = fopen(FIFO_FILE, "r+")) == NULL)
  {
    perror("fopen");
    exit(1);
  }
  printf("Me : ");
  gets(a);
  if (a[strlen(a) - 1] == '.')
  {
    fputs(a, fp);
    fclose(fp);
    return 0;
  }
  fputs(a, fp);
  fclose(fp);
  sleep(1);
  fp = fopen(FIFO_FILE, "r");
  fgets(readbuf, SIZE, fp);
  printf("Him :%s\n", readbuf);
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
#include <pthread.h>
#include <string.h>

#define SIZE 128
#define FIFO_FILE "fifo"


int main() {
   int fd;
   char readbuf[SIZE];
   char quit[10];
   int to_quit;
   int read_bytes;
   printf("[SERVER]: \n");
   //Create the FIFO if it does not exist 
   mkfifo(FIFO_FILE, S_IFIFO|0666);
   strcpy(quit, "quit");
   fd = open(FIFO_FILE, O_RDWR);
   while(1) {
      read_bytes = read(fd, readbuf, sizeof(readbuf));
      readbuf[read_bytes] = '\0';
      printf("[SERVER]: %s", readbuf);
      to_quit = strcmp(readbuf, quit);
      
      if (to_quit == 0) {
         close(fd);
         break;
      }
      
      write(fd, readbuf, strlen(readbuf));
      sleep(2);
   }
   return 0;
}
*/