#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#define K 1024


void handler(int sig) {
    unlink("tmp");
    printf("\n");
    kill(0, SIGKILL);
}


void parent(int p[2], pid_t pid) {

 int r, t, w, status;
 char buf[K];


 while(waitpid(pid, &status, 0) < 0) perror("wait");
 printf("Start chatting:\n");

while(1) {
char *tmp = "tmp";
 mkfifo(tmp, 0666);

 int fd = open(tmp, O_RDONLY);
 chmod(tmp, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP);


 while ((r = read(fd, buf, K)) > 0) {

  for (int i = 0; i < r; i++) 
          printf("%c", buf[i]);
 }

 close(fd);
 unlink(tmp);
 fflush(stdout);
}
}

int main(int argc, char *argv[]) {


  if (access("tmp", F_OK) != -1) {
    printf("Listen is already running, exiting.\n");
    kill(0, SIGKILL);
  }
  int pfd[2];
  signal(SIGINT, &handler);

  if (pipe(pfd) < 0) {
    perror("pipe");
    return -1;
  }

  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    return -1;
  }

  if (pid > 0) parent(pfd, pid);
  return 0;
}
