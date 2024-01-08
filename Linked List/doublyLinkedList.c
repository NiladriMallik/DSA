#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Node{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

/*
head will point to the first node
tail will point to the last node
nodeCount stores the number of nodes in the linked list
*/

typedef struct{
    struct Node *head;
    struct Node *tail;
    int nodeCount;
}LinkedList;

void initList(LinkedList *);
int loadFromFile(LinkedList *, char *);
void createListFromRandomNumbers(LinkedList *, int);
void insertAtHead(LinkedList *, int);
void insertAtTail(LinkedList *, int);

void printList(LinkedList *);
Node *find(LinkedList *, int, Node **);

int deleteFirst(LinkedList *);
int deleteLast(LinkedList *);
int deleteTarget(LinkedList *,int);

int reverse(LinkedList *);

void initList(LinkedList *listptr){
    listptr->head = NULL;
    listptr->tail = NULL;
    listptr->nodeCount = 0;
}


void insertAtHead(LinkedList *listptr, int value){
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL){
        printf("Unable to allocate new node.\n");
        return;
    }
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    if(listptr->nodeCount == 0){
        listptr->head = node;
        listptr->tail = node;
    }
    else{
        node->next = listptr->head;
        listptr->head = node;
    }
    listptr->nodeCount++;
}


void insertAtTail(LinkedList *listptr, int value){
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
        node->prev = listptr->tail;
        listptr->tail = node;
    }
    listptr->nodeCount++;
}


int deleteFirst(LinkedList *listptr){
    int result;
    if(listptr->nodeCount == 0){
        return 0;
    }
    Node *temp = listptr->head;
    if(listptr->nodeCount == 1){
        listptr->head = NULL;
        listptr->tail = NULL;
    }
    else{
        listptr->head = temp->next;
        listptr->head->prev = NULL;
    }
    listptr->nodeCount--;
    result = temp->data;
    free(temp);
    return result;
}


int deleteLast(LinkedList *listptr){
    int result;
    if(listptr->nodeCount == 0){
        return 0;
    }
    Node *temp = listptr->tail;
    if(listptr->nodeCount == 1){
        listptr->head = NULL;
        listptr->tail = NULL;
    }
    else{
        listptr->tail = temp->prev;
        listptr->tail->next = NULL;
        temp->prev = NULL;
    }
    result = temp->data;
    free(temp);
    listptr->nodeCount--;
    return result;

}