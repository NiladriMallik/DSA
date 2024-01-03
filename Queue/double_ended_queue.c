#include<stdio.h>
#include<stdlib.h>

#define SIZE  8

typedef struct {
    int item[SIZE];
    int rear,front;
}Queue;

void initQueue(Queue *);
void ins_at_rear(Queue *,int);
int del_from_rear(Queue *);
void ins_at_front(Queue *,int);
int del_from_front(Queue *);

void initQueue(Queue *queue){
    queue->front = 0;
    queue->rear = -1;
}

void ins_at_rear(Queue *queue,int value){
    if(queue->rear == SIZE - 1){
        printf("Unable to insert at the rear end.\n");
        return;
    }
    queue->rear++;
    queue->item[queue->rear] = value;
}


int del_from_rear(Queue *queue){
    if(queue->front > queue->rear){
        return -999;
    }
    int value = queue->item[queue->rear];
    queue->rear--;
    return value;
}


void ins_at_front(Queue *queue,int value){
    if(queue->front == 0){
        printf("Unable to insert at the front.\n");
        return;
    }
    queue->front--;
    queue->item[queue->front] = value;
}


int del_from_front(Queue *queue){
    if(queue->front > queue->rear){
        return -999;
    }
    return queue->item[queue->front++];

}


void menu(){
    printf("---------------FIFO Queue Operations---------------\n");
    printf("---------------------------------------------------\n");
    printf("1. Insert at rear\n");
    printf("2. Insert at front\n");
    printf("3. Delete from rear\n");
    printf("4. Delete from front\n");
    printf("5. Exit\n");
}


int main(){
    Queue queue;
    initQueue(&queue);
    int quit = 0;
    int value;
    menu();
    while(!quit){
        int choice;
        printf("Input your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("Input value to insert at rear: ");
                scanf("%d",&value);
                ins_at_rear(&queue,value);
                break;

            case 2:
                printf("Input value to insert at front: ");
                scanf("%d",&value);
                ins_at_front(&queue,value);
                break;

            case 3:
                value = del_from_rear(&queue);
                if(value == -999)
                    printf("Queue underflow.\n");
                else
                    printf("Delete from rear, value: %d.\n",value);
                break;

            case 4:
                value = del_from_front(&queue);
                if(value == -999)
                    printf("Queue underflow.\n");
                else
                    printf("Deleted from front, value: %d.\n",value);
                break;

            case 5:
                quit = 1;
                break;
            
            default:
                printf("Invalid choice, valid options are 1 - 5.\n");
        }
    }
}