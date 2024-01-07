#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;


/*
head will point to the first node
tail will point to the last node
to get the address of the last node, we don't have to iterate through the linked list
//nodeCount contains number of nodes in linked list
*/
typedef struct{
    struct Node *head;
    struct Node *tail;
    int nodeCount;
}LinkedList;


//function prototypes
void initList(LinkedList *);
int loadFromFile(LinkedList *, char *);
void createListFromRandomNumbers(LinkedList *, int);
void insertAtTail(LinkedList *, int);

//printing of linked list
void printListForward(LinkedList *);
void printListBackward(LinkedList *);

//helper recursive functions for implementing the traversal
void printRecForward(Node *);
void printRecReverse(Node *);


void initList(LinkedList *listptr){
    listptr->head = NULL;
    listptr->tail = NULL;
    listptr->nodeCount = 0;
}


int loadFromFile(LinkedList *listptr, char *fileName){
    //mode to read a file - r
    //mode to read a binary file - rb
    FILE *inputFile = fopen(fileName,"r");
    if(inputFile == NULL){
        return 0;
    }

    int data;
    /*parameters of fscanf function
    file pointer
    format specifier
    address of the variable where we will keep the data  */
    fscanf(inputFile, "%d", &data);
    while(!feof(inputFile)){
        insertAtTail(listptr,data);
        fscanf(inputFile,"%d",&data);
    }
    fclose(inputFile);
    return 1;
}


void createListFromRandomNumbers(LinkedList *listptr, int n){
    int i;
    /*
    time() will return the time of the system, 
    that will initialize the seed of the random number with the current system time
    Since seed is different everytime function is called,
    series of random numbers are going to be different every time.
    */
    srand(time(NULL));
    for(int i = 1; i <= n; i++){
        int  k = rand() % 1000;
        insertAtTail(listptr,k);
    }
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


void printRecForward(Node *node){
    if(node == NULL){
        return;
    }
    printf("%4d ",node->data);
    printRecForward(node->next);
}


void printRecReverse(Node *node){
    if(node == NULL){
        return;
    }
    printRecReverse(node->next);
    printf("%4d ",node->data);
}


void printListForward(LinkedList *listptr){
    printRecForward(listptr->head);
}


void printListBackward(LinkedList *listptr){
    printRecReverse(listptr->head);
}




void menu(){
    printf("   Singly Linked List Recursive Operations\n");
    printf("---------------------------------------\n");
    printf("1. Load from file\n");
    printf("2. Create linked list from random numbers\n");
    printf("3. Insert at tail\n");
    printf("4. Print linked list in forward order\n");
    printf("5. Print linked list in reverse ordert\n");
    printf("6. Quit\n");
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
                result = loadFromFile(&list, "data.txt");
                if(result == 1)
                    printf("File has been loaded.\n");
                else
                    printf("File loading failed due to some error.\n");
                break;

            case 2:
                printf("Enter the number of random numbers: ");
                scanf("%d",&data);
                createListFromRandomNumbers(&list,data);
                break;

            case 3:
                printf("Input data to insert node at tail (as last node): ");
                scanf("%d",&data);
                insertAtTail(&list, data);
                break;

            case 4:
                printListForward(&list);
                break;

            case 5:
                printListBackward(&list);
                break;

            case 6:
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