#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_BSIZE 10
int cnt =0;
static sem_t hsem, num_buff, num_data;

void *producer(void *arg)
{
  int i,tmp;
  for(;;){
    sem_wait(&num_buff);
    sem_wait(&hsem);
    cnt++;
    printf("producer count : %d\n", cnt);
    sleep(1);
    sem_post(&hsem);
    sem_post(&num_data);
  }
  printf("producer end \n");
  return NULL;
}

void *consumer(void *arg)
{
  int i, tmp;
  for (;;)
  {
    sem_wait(&num_data);
    sem_wait(&hsem);
    cnt--;
    printf("consumer count : %d\n", cnt);
    sleep(1);
    sem_post(&hsem);
    sem_post(&num_buff);
  }
  printf("consumer end \n");
  return NULL;
}

int main(int argc, char *argv[]){
  pthread_t thread1;
  pthread_t thread2;

  if(sem_init(&hsem, 0, 1) <0){
    fprintf(stderr, "Semaphore initialization error\n");
    return 1;
  }
  if (sem_init(&num_buff, 0, MAX_BSIZE) < 0){
    fprintf(stderr, "Semaphore initialization error\n");
    return 1;
  }
  if (sem_init(&num_data, 0, 0) < 0){
    fprintf(stderr, "Semaphore initialization error\n");
    return 1;
  }
  pthread_create(&thread1, NULL, producer, NULL);
  pthread_create(&thread2, NULL, consumer, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("%d\n", cnt);
  sem_destory(&hsem);
  return 0;
}

