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


int getSize(Stack *sp){
    return sp->size;
}

void push(Stack *sp, int value){
    if(sp->top == sp->size-1){
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
    if(sp->top == -1){
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


int main(){
    Stack s1;
    int choice, value, size;

    printf("Enter the size of the stack: ");
    scanf("%d",&size);
    init (&s1, size);

    printf("1. Push\n");
    printf("2. Pop\n");
    printf("3. Exit\n");

    while(1){
        printf("Enter choice: ");
        scanf("%d",&choice);
        printf("Size of stack: %d.\n",getSize(&s1));
        switch(choice){
            case 1: 
                    printf("Enter value to push: ");
                    scanf("%d", &value);
                    push(&s1, value);
                    break;
            case 2: 
                    value = pop(&s1);
                    if (value!= -9999){
                        printf("Popped data: %d.\n",value);
                    }
                    break;
            case 3:
                    deallocate(&s1);
                    exit(0);
            default:
                    printf("Invalid choice!\n");
                    break;
        }
    }
    return 0;
}