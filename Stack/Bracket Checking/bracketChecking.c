#include<stdio.h>
#include<stdlib.h>

#define SIZE 100

typedef struct{
    char item[SIZE];
    int top;
} Stack;

//function prototypes

//function for stack operations

void push(Stack *, char);
char pop(Stack *);
int isEmpty(Stack *);
char stackTop(Stack *);

//function required for this application
int isOpeningMatch(char,char);

//actual implementation of the algorithm
int checkExpr(char[]);

//push operation
void push(Stack *sp, char v){
    //checking overflow
    if (sp->top == SIZE - 1){
        printf("Stack overflow, terminating program\n");
        exit(1);
    }
    //otherwise push
    sp->item[++sp->top] = v;
}

//pop operation
char pop(Stack *sp){
    if (isEmpty(sp)){
        printf("Stack underflow, terminating program");
        exit(1);
    }
    return sp->item[sp->top--];
}

//returns 1 if stack is empty, 0 otherwise

int isEmpty(Stack *sp){
    return sp->top == -1;
}

char stackTop(Stack *sp){
    if(isEmpty(sp)){
        return ' ';
    }
    else return sp->item[sp->top];
}

int isOpeningMatch(char left, char right){
    int match = 0;
    switch(left){
        case '(' : if(right == ')')
                    match = 1;
                    break;

        case '{' : if(right == '}')
                    match = 1;
                    break;

        case '[' : if(right = ']')
                    match = 1;
                    break;

        default : printf("Invalid symbol encountered, terminating the program.\n");
                    exit(1);
    }
    return match;
}

int checkExpr(char expr[]){

    int i = 0,error = 0;
    char c;
    Stack *sp;
    sp->top = -1;
    while(expr[i] != '\0'){
        c = expr[i];
        if (c == '(' || c == '[' || c == '}'){
            push(&sp,c);
        }

        else if(c == ')' || c == '}' || c == ']'){
            if(isEmpty(&sp)){
                error = 1;
                break;
            }
            else if(isOpeningMatch(stackTop(&sp),c)){
                pop(&sp);
            }
            else{
                error = 1;
                break;
            }
        }
        else continue;
    }

    if(!error && !isEmpty(&sp)){
        error = 1;
    }

    return error;

}

int main(){
    char expr[SIZE];
    printf("Input expression: ");
    scanf("%s",expr);

    if(checkExpr(expr)){
        printf("Does not have well formed brackets.\n");
    }
    else{
        printf("Contains well formed brackets.\n");
    }
    
    return 0;
}