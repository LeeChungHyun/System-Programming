#include <semaphore.h>
int cnt=0;
static sem_t hsem;
int main(int argc, char *argv[])
{ pthread_t thread1;
pthread_t thread2;
if (sem_init(&hsem, 0, 1) < 0){
fprintf(stderr, "Semaphore Initilization Error\n");
return 1;
}
pthread_create(&thread1, NULL, Thread1, NULL);
pthread_create(&thread2, NULL, Thread2, NULL);
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);
printf("%d\n", cnt);
sem_destroy(&hsem);
return 0;
}

void *Thread1(void *arg)
{
int i, tmp;
for(i=0; i<1000; i++){
sem_wait(&hsem);
tmp=cnt;
usleep(1000);
cnt=tmp+1;
sem_post(&hsem);
}
printf("Thread1 End\n");
return NULL;
}

void *Thread2(void *arg)
{
int i, tmp;
for(i=0; i<1000; i++){
sem_wait(&hsem);
tmp=cnt;
usleep(1000);
cnt=tmp+1;
sem_post(&hsem);
}
printf("Thread2 End\n");
return NULL;
}