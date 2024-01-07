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
void insertAtHead(LinkedList *,int);
void insertAtTail(LinkedList *, int);

void printListDetail(LinkedList *);
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
        insertAtHead(listptr,k);
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


void insertAtHead(LinkedList *listptr, int value){
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL){
        printf("Unable to allocate new node.\n");
        return;
    }
    node->data = value;
    node->next = NULL;
    if(listptr->nodeCount == 0) {
        listptr->head = node;
        listptr->tail = node;
    }
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


void printListDetail(LinkedList *listptr){
    if(listptr->nodeCount == 0){
        printf("\nLinked list is empty.\n");
        return;
    }
    printf("Printing linked list in details:\n");
    printf("HEAD: %p\n",listptr->head);
    Node *current = listptr->head;
    int count = 1;
    while(current != NULL){
        printf("%d. (%p)[%d|%p]\n",count, current, current->data, current->next);
        current = current->next;
        count++;
    }
    printf("TAIL: %p\n",listptr->tail);
}


Node *find(LinkedList *listptr,int target,  Node **prevptr){
    Node *temp = listptr->head;
    *prevptr = NULL;
    while(temp != NULL){
        if(temp->data == target){
            break;
        }
        *prevptr = temp;
        temp = temp->next;
    }
        return temp;
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
        listptr->head = temp->next;     //temp points to first node, assign next node to head
    }
    listptr->nodeCount--;
    result = temp->data;
    free(temp);                         //free temp, i.e., the first node
    return result;                      //return data value
}


int deleteLast(LinkedList *listptr){
    int result;                             //to store the data value of the deleted node
    if(listptr->nodeCount == 0){    
        return 0;
    }
    Node *temp = listptr->head;
    if(listptr->nodeCount == 1){
        listptr->head = NULL;
        listptr->tail = NULL;
    }
    else{
        while(temp->next->next != NULL){    //iterate till the temp points to the second last node
            temp = temp->next;  
        }
        listptr->tail = temp;               //assign second last node to tail
        temp = temp->next;                  //assign the last node to temp
        listptr->tail->next = NULL;         //assign next pointer of second last node as null
    }
    result = temp->data;                 
    free(temp);                             //free the last node
    listptr->nodeCount--;   
    return result;
}

//deleteTarget implementation 1
/*
int deleteTarget(LinkedList *listptr,int value){
    
    return 0 - empty linked list
    return -1 - element not found
    return 1 - element deleted
    
    if(listptr->nodeCount == 0){        //if linked list is empty
        return 0;
    }
    if(listptr->head->data == value){   //if value to be deleted is in first node
        deleteFirst(listptr);
        return 1;
    }
    if(listptr->tail->data == value){   //if value to be deleted is in last node
        deleteLast(listptr);
        return 1;
    }

    Node *temp = listptr->head, *prev;
    if(listptr->nodeCount == 1){            //if only one node in linked list
        if(listptr->head->data != value){   //node value not equal to target value
            return -1;
        }
        else{
            listptr->head = NULL;
            listptr->tail = NULL;
            return 1;
        }
    }
    else{                           //if multiple nodes in linked list
        while(temp->next->data != value && temp->next->next != NULL){
            temp = temp->next;
        }
        if(temp->next->next == NULL){       //if iterated to second last node and target node not found
            return -1;
        }
        prev = temp;
        temp = temp->next;
        prev->next = temp->next;
        free(temp);
        listptr->nodeCount--;
        return 1;
    }
}
*/


//deleteTarget implementation 2
int deleteTarget(LinkedList *listptr, int value){
    // return 0 - empty linked list
    // return -1 - element not found
    // return 1 - element deleted
    Node *temp = NULL, *prev = NULL;
    temp = find(listptr, value, &prev);

    if(listptr->nodeCount == 0){
        return 0;
    }
    if(temp == NULL){
        return -1;
    }
    int data = temp->data;
    if(temp == listptr->head){
        return deleteFirst(listptr);
    }
    else if(temp == listptr->tail){
        return deleteLast(listptr);
    }
    else{
        prev->next = temp->next;
        free(temp);
        listptr->nodeCount--;
        return 1;
    }
}


int reverse(LinkedList *listptr){
    if(listptr->nodeCount <= 1){
        return 0;
    }
    Node *p, *q, *r;
    q = NULL;
    p = listptr->head;
    r = p->next;
    while(1){
        p->next = q;
        if(p == listptr->tail){
            break;
        }
        q = p;
        p = r;
        r = r->next;
    }
    listptr->tail = listptr->head;
    listptr->head = p;
    return 1;
}


void menu(){
    printf("   Singly Linked List Operations\n");
    printf("---------------------------------------\n");
    printf("1.  Load from file\n");
    printf("2.  Create linked list from random numbers.\n");
    printf("3.  Insert at head\n");
    printf("4.  Insert at tail\n");
    printf("5.  Print list (detail)\n");
    printf("6.  Print list (data only)\n");
    printf("7.  Find\n");
    printf("8.  Delete from first\n");
    printf("9.  Delete from last\n");
    printf("10. Delete a target node\n");
    printf("11. Reverse\n");
    printf("12. Quit\n");
}


int main(){
    LinkedList list;
    int quit = 0, choice, data, result;
    Node * temp = NULL, *prev = NULL;
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
                printf("Input data to insert node at head (as first node): ");
                scanf("%d",&data);
                insertAtHead(&list, data);
                break;

            case 4:
                printf("Input data to insert node at tail (as last node): ");
                scanf("%d",&data);
                insertAtTail(&list, data);
                break;

            case 5:
                printListDetail(&list);
                break;
            
            case 6:
                printList(&list);
                break;
            
            case 7:
                printf("Enter data to find: ");
                scanf("%d",&data);
                temp = find(&list, data, &prev);
                if(temp == NULL){
                    printf("Target not found in linked list.\n");
                }
                else{
                    printf("Target found in linked list, address[data] of the target node: %p[%d], previous node[data]: %p[%d]\n",temp, temp->data, prev, prev->data);
                }
                break;

            case 8:
                result = deleteFirst(&list);
                if(result == 0)
                    printf("Empty linked list, no nodes to delete.\n");
                else
                    printf("%d has been deleted.\n",result);
                break;

            case 9:
                result = deleteLast(&list);
                if(result == 0)
                    printf("Empty linked list, no nodes to delete.\n");
                else
                    printf("%d has been deleted.\n",result);
                break;

            case 10:
                printf("Input data to delete: ");
                scanf("%d",&data);
                result = deleteTarget(&list,data);
                if(result == 0)
                    printf("Empty linked list, no nodes to delete.\n");
                else if(result == -1)
                    printf("%d not found in linked list.\n",data);
                else
                    printf("%d has been deleted.\n",data);
                break;

            case 11:
                result = reverse(&list);
                if(result){
                    printf("Linked list has been reversed.\n");
                }
                else{
                    printf("Linked list empty, nothing to reverse.\n");
                }
                break;

            case 12:
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
