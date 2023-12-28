#include<stdio.h>
#include<stdlib.h>

#define SIZE 5

typedef struct{
    int item[SIZE];
    int rear, front;
}Queue;

//function prototypes
void initQueue(Queue *);
void enqueue(Queue *, int);
int dequeue(Queue *);
void traverse(Queue *);

void initQueue(Queue *queue){
    queue->front = SIZE - 1;
    queue->rear = SIZE - 1;

}


void enqueue(Queue *queue, int value){
    if((queue->rear + 1)%SIZE == queue->front){
        printf("Queue overflow.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % SIZE;
    queue->item[queue->rear] = value;
}


int dequeue(Queue *queue){
    if(queue->rear == queue->front){
        return -9999;
    }
    queue->front = (queue->front + 1) % SIZE;
    int value = queue->item[queue->front];
    return value;
}


int main(){
    Queue queue;
    initQueue(&queue);
    int choice, value;

    while(1){
        printf("\n1. To insert into queue.\n2. To remove from queue.\n3. Exit.\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: 
                printf("Enter value to enter: ");
                scanf("%d",&value);
                enqueue(&queue,value);
                break;
            case 2: 
                value = dequeue(&queue);
                if(value != -9999)
                    printf("Value dequeued is %d.\n",value);
                else
                    printf("Queue underflow.\n");
                break;
            case 3: 
                exit(0);
            default: 
                printf("Invalid choice.");
                break;
        }
    }
    return 0;
}