#include<stdio.h>
#include<stdlib.h>

#define SIZE 100

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
    queue->front = 0;
    queue->rear = 0;

}


void enqueue(Queue *queue, int value){
    if(queue->rear == SIZE){
        printf("Queue overflow.\n");
        return;
    }
    queue->item[queue->rear] = value;
    queue->rear++;
}


int dequeue(Queue *queue){
    if(queue->rear == queue->front){
        return -9999;
    }
    int value = queue->item[queue->front];
    queue->front++;
    return value;
}


void traverse(Queue *queue){
    printf("The queue is: ");
    for(int i = queue->front ; i < queue->rear ; i++){
        printf("%d\t",queue->item[i]);
    }
    printf("\n");
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
                traverse(&queue);
                break;
            case 4: 
                exit(0);
            default: 
                printf("Invalid choice.");
                break;
        }
    }
    return 0;
}