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
int loadFromFil(LinkedList *, char *);
void createListFromRandomNumbers(LinkedList *, int);
void insertAtHead(LinkedList *, int);
void insertAtTail(LinkedList *, int);

void printList(LinkedList *);
Node *find(LinkedList *, int, Node **);

int deleteFirst(LinkedList *);
int deleteLast(LinkedList *);
int deleteTarget(LinkedList *,int);

int reverse(LinkedList *);
