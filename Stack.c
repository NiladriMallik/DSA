#include<stdio.h>
#define SIZE 10


typedef struct {
    int item[SIZE];
    int top;
} Stack;


void push(Stack *, int);
void pop(Stack*);


void push(Stack *sp, int value){
    if(sp->top == SIZE-1){
        printf("Stack is overflow");
        return;
    }

    sp->top++;
    sp->item[sp->top] = value;
}


void pop(Stack *sp){

    if(sp->top == -1){
        printf("Stack underflow");
        return -9999;
    }
    int value = sp->item[sp->top];
    sp->top--;
    return value;
}


int main(){

    Stack s1, s2;

    return 0;
}