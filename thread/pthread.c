#include <stdio.h>
#include <malloc.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

#define MaxQueue 100//큐의 최댓값 지정한다.

//사용할 뮤텍스와 condition 선언하고 초기화한다.
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_has_space = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data = PTHREAD_COND_INITIALIZER;

int input;//파일을 오픈하고 반환받을 리턴 값
int n;//input.txt에서 한번에 읽어드린 문자의 길이
char buf[1];//input.txt에서 읽어드릴 문자

//연결리스트로 된 큐를 구현하기 위한 노드
struct NodeType{
	char value;
	struct NodeType* next;
};
//큐의 front/rear는 null을 가진다.
struct NodeType *front = NULL;
struct NodeType *rear = NULL;

int queLen = 0;//큐의 길이

int isFull(){
    struct NodeType *ptr;
    ptr = (struct NodeType*)malloc(sizeof(struct NodeType));
    if(ptr == NULL || queLen == MaxQueue){
        return 1;
    }
    else{
        free(ptr);
        return 0;
    }
}

int isEmpty()
{
    if(front == NULL)
        return 1;
    else return 0;
}

void Enqueue(char value){
    if(isFull()){
        printf("Que is full of malloc\n");
        return ;
    }
    else{
        struct NodeType *ptr;
        ptr = (struct NodeType *)malloc(sizeof(struct NodeType));

        ptr -> value = value;
        ptr ->next = NULL;

        if(rear == NULL)
            front = ptr;
        else
            rear -> next = ptr;
        rear = ptr;
        queLen++;
    }
}

void Dequeue(char *value)
{
    if (isEmpty())
    {
        printf("error : isEmpty");
        return;
    }
    else
    {
        struct NodeType *ptr;
        ptr = front;
        *value = front->value;
        front = front ->next;

        if (front == NULL)
            rear == NULL;
        free(ptr);
        queLen--;
    }
}

void destroyQueue(){
    struct NodeType *ptr;
    while(front != NULL){
        ptr = front;
        front = front -> next;
        free(ptr);
    }
    rear = NULL;
    queLen = 0;
}

int main(){
    int i;
    pthread_t threads[2];

    pthread_create(&threads[0], NULL, producer, NULL);
    pthread_create(&threads[1], NULL, consumer, NULL);

    for(i=0; i<2; i++)
        pthread_join(threads[i], NULL);
        
    destroyQueue();
    return 0;
}