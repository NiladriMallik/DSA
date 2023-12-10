#include<stdio.h>
#include<stdlib.h>

typedef struct {
    /*
    For the stack to be dynamically allocated we need to have a pointer to hold the base address of the arrray, also, since the size will be different for different instances of Stack so we need to keep the size inside the struct object.
    */
    int *item;
    int top;
    int size;
} Stack;

void init(Stack *, int);
void push(Stack *, int);
int pop(Stack*);
void deallocate(Stack *sp);
int getSize(Stack *sp);
int isUnderflow(Stack *);
int isOverflow(Stack *);

void printBinary(unsigned int);

int getSize(Stack *sp){
    return sp->size;
}

void push(Stack *sp, int value){
    if(isOverflow(sp)){
        /*
        Instead of showing message stack overflow and returning to caller,
        we can grow the array to double its size by retaining the existing value
        */
        int *temp;
        temp = (int*) malloc(sizeof(int) * sp->size * 2);
        if (temp == NULL){
            printf("Stack overflow!");
            return;
        }
        //Otherwise, double sized array has been allocated.
        //We can now copy the existing content to the temp array.
        int i;
        for(i=0;i<=sp->top;i++){
            temp[i] = sp->item[i];
        }
        free(sp->item);
        sp->item = temp;
        sp->size *= 2;
    }
    sp->top++;
    sp->item[sp->top] = value;
}


int pop(Stack *sp){
    if(isUnderflow(sp)){
        printf("Stack underflow.\n");
        return -9999;
    }
    int value = sp->item[sp->top];
    sp->top--;
    return value;
}


void init(Stack *sp, int size){
    sp->top = -1;
    sp->item = (int* )malloc(sizeof(int) * size);
    sp->size = size;

    if(sp->item == NULL){
        printf("Unable to allocate memory.\n");
        exit(1);
    }
}


void deallocate(Stack *sp){
    if(sp->item != NULL){
        free(sp->item);
    }
    sp->top = -1;
    sp->size = 0;
}


int isOverflow(Stack *sp){
    return sp->top == sp->size - 1;
}

int isUnderflow(Stack *sp){
    return sp->top == -1;
}

void printBinary(unsigned int n){
    Stack s;
    init(&s,10);
    const int BASE = 2;
    int n1 = n;
    
    while(n>0){
        int rem = n % BASE;
        push(&s, rem);
        n /= BASE;
    }
    printf("Binary equivalent of %d is ",n1);
    while(!isUnderflow(&s)){
        printf("%d",pop(&s));
    }
    deallocate(&s);
}


int main(){
    int n;
    
    printf("Enter the number to convert to binary: ");
    scanf("%d",&n);
    printBinary(n);
    return 0;
}