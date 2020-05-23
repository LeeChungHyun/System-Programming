#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <stdlib.h>

void sig_catch(int sig_no){

}

int main(){
  int pid;
  int status;
  signal(SIGUSR1, sig_catch);
  if((pid = fork()) ==0){
    pause();
    printf("child wake up\n");
    exit(0);
  }else{
    sleep(1);
    kill(pid, SIGUSR1);
    wait(&status);
  }
}