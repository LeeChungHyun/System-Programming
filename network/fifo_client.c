#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

#define K 1024

void cat() {
while (1) {
int r, w, t;
 char buf[K];
 int fd;
 char *tmp = "tmp";


 fd = open(tmp, O_WRONLY);

 while(( r = read(1, buf,K)) > 0) {
   t = 0;

   do {
    w = write(fd, buf, r);
    t += w;

   } while (t < r);

 }

 if (r < 0) perror("read");

 close(fd);
 unlink(tmp);
}
}

int main(int argc, char *argv[]) {

 if (access("tmp", F_OK) == -1) {
   printf("No one is listening\n");
   kill(0, SIGKILL);
 }else {
   printf("Start chatting:\n");
   cat();
 }

  return 0;
}
