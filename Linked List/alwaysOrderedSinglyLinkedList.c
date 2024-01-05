#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;


/*
head will point to the first node
tail will point to the last node
to get the address of the last node, we don't have to iterate through the linked list
*/
typedef struct{
    struct Node *head;
    struct Node *tail;
    int nodeCount;
}LinkedList;


//function prototyps
void initList(LinkedList *);
void insertAtHead(LinkedList *,int);
void insertAtTail(LinkedList *, int);
void insertOrder(LinkedList *, int);
void printList(LinkedList *);


void menu(){
    printf("   Singly Linked List Operations\n");
    printf("---------------------------------------\n");
    printf("1. Insert at head\n");
    printf("2. Insert at tail\n");
    printf("3. Print list (data only)\n");
    printf("4.Insert in order\n");
    printf("5.Quit\n");
}


void initList(LinkedList *listptr){
    listptr->head = NULL;
    listptr->tail = NULL;
    listptr->nodeCount = 0;
}


void insertAtTail(LinkedList *listptr,int value){
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL){
        printf("Unable to allocate new node.\n");
        return;
    }
    node->data = value;
    node->next = NULL;
    if(listptr->nodeCount == 0){
        listptr->head = node;
        listptr->tail = node;
    }
    else{
        listptr->tail->next = node;
        listptr->tail = node;
    }
    listptr->nodeCount++;
}


void insertOrder(LinkedList *listptr, int value){
    Node *node = (Node*)malloc(sizeof(Node));


    node->data = value;
    node->next = NULL;

    if(node == NULL){
        printf("Unable to allocate new node.\n");
        return;
    }

    //in case of empty linked list
    if(listptr->nodeCount == 0){
        listptr->head = node;
        listptr->tail = node;
        return;
    }
  
    //when value of last node > input value
    //insert new node at last
    if(value > listptr->tail->data){
        listptr->tail->next = node;
        return;
    }

    //when value of first node < input node
    //insert new node at first
    if(value < listptr->head->data){
        node->next = listptr->head;
        listptr->head = node;
        return;
    }


    else{
        Node *temp = listptr->head;
        while(temp->next->data < value && temp->next){
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
        // temp->next->next = node->next;
        // free(temp);
    }
    listptr->nodeCount++;
}


void insertAtHead(LinkedList *listptr, int value){
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL){
        printf("Unable to allocate new node.\n");
        return;
    }
    node->data = value;
    node->next = NULL;

    //in case of empty linked list
    if(listptr->nodeCount == 0) {
        listptr->head = node;
        listptr->tail = node;
    }

    //case when linked list is not empty
    else{
        node->next = listptr->head;
        listptr->head = node;
    }
    listptr->nodeCount++;
}


void printList(LinkedList *listptr){
    if(listptr->nodeCount == 0){
        printf("Linked list is empty.\n");
        return;
    }
    Node *current = listptr->head;
    while(current != NULL){
        printf("%d\n",current->data);
        current = current->next;
    }
}


int main(){
    LinkedList list;
    initList(&list);
    menu();

    int quit = 0, choice, data;
    while(!quit){
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Input data to insert node at head (as first node): ");
                scanf("%d",&data);
                insertAtHead(&list, data);
                break;

            case 2:
                printf("Input data to insert node at tail (as last node): ");
                scanf("%d",&data);
                insertAtTail(&list, data);
                break;
            
            case 3:
                printList(&list);
                break;

            case 4:
                printf("Input data to insert in order: ");
                scanf("%d",&data);
                insertOrder(&list,data);
                break;

            case 5:
                quit = 1;
                break;

            default:
                printf("Invalid choice. Please enter correct option.\n");
                quit = 1;
                break;
        }
    }
    return 0;
}
