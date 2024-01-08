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

void printList(LinkedList *, int);

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
        node->prev = NULL;
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


void printList(LinkedList *listptr, int direct){
    //direction 0 = backward
    //direction 1 = forward
    if(listptr->nodeCount == 0){
        printf("Empty linked list.\n");
        return;
    }
    else{
        Node *temp;
        if(direct == 1){
            printf("Linked list in forward direction: \n");
            temp = listptr->head;
            while(temp != NULL){
                printf("%d\n",temp->data);
                temp = temp->next;
            }
        }
        else{
            printf("Linked list in backward direction: \n");
            temp = listptr->tail;
            while(temp != NULL){
                printf("%d\n",temp->data);
                temp = temp->prev;
            }
        }
    }
}


void menu(){
    printf("   Singly Linked List Operations\n");
    printf("---------------------------------------\n");
    printf("1.  Load from file\n");
    printf("2.  Create linked list from random numbers.\n");
    printf("3.  Insert at head\n");
    printf("4.  Insert at tail\n");
    printf("5.  Print list (data only)\n");
    printf("6.  Find\n");
    printf("7.  Delete from first\n");
    printf("8.  Delete from last\n");
    printf("9. Delete a target node\n");
    printf("10. Quit\n");
}


int main(){
    LinkedList list;
    int quit = 0, choice, data, result;
    initList(&list);
    menu();

    while(!quit){
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Not implmented yet.\n");
                break;

            case 2:
                printf("Not implemented yet.\n");
                break;

            case 3:
                printf("Input data to insert at head: ");
                scanf("%d",&data);
                insertAtHead(&list, data);
                break;

            case 4:
                printf("Input data to insert at tail: ");
                scanf("%d",&data);
                insertAtTail(&list, data);
                break;

            case 5:
                printf("Printing list, backward (0) or forward (1): ");
                scanf("%d",&data);
                printList(&list, data);
                break;

            case 6:
                printf("Not implemented yet.\n");
                break;

            case 7:
                result = deleteFirst(&list);
                if(result == 0)
                    printf("Empty linked list, no nodes to delete.\n");
                else
                    printf("%d has been deleted.\n",result);
                break;

            case 8:
                result = deleteLast(&list);
                if(result == 0)
                    printf("Empty linked list, no nodes to delete.\n");
                else
                    printf("%d has been deleted.\n",result);
                break;

            case 9:
                printf("Not implemented yet.\n");
                break;

            case 10:
                quit = 1;
                break;

            default:
                printf("Invalid choice. Please enter correct option.\n");
                break;
        }
        printf("\n");
    }
    return 0;
}