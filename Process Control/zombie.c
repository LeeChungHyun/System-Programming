#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
pid_t pid;
int i = 10000;

if((pid = fork())<0){
perror("fork error");
}else if(pid == 0){
printf("Child: pid=%d\n", getpid());

while(1){
printf("c(%d)\n", i);
i++;
sleep(1);
}
}else{
    printf("parent: pid=%d\n", getpid());
    printf("parent: Child pid=%d\n",pid);
    sleep(1);
                
    printf("Parent: exit\n");
                
    exit(0);
    }
}
