#include<stdio.h>
#include<stdlib.h>

#define SIZE 100

typedef struct{
    char item[SIZE];
    int top;
} Stack;

char precendence[6] = {'[' , '{' , '(' , ')' , '}' , ']'};
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

//check valid order of use of brackets
int correctBracketOrder(char, char);

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
        printf("Stack underflow, terminating program");
        exit(1);
    }
    return sp->item[sp->top];
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
    
    Stack stack;
    stack.top = -1;
    while(expr[i] != '\0'){
        //get the next character
        char c = expr[i];
        if (c == '(' || c == '[' || c == '{'){
            push(&stack,c);
        /*  printf("\nItems in stack: ");
                for(int j=0;j<=i;j++){
                    printf("%c ",stack.item[i]);
            }
        */ 
        }
        else if(c == ')' || c == '}' || c == ']'){
            if(isEmpty(&stack)){
                error = 1;
                break;
            }
            //check if the top of the stack matches with the character
            else if(isOpeningMatch(stackTop(&stack),c)){
                pop(&stack);
            /*  printf("\nItems in stack: ");
                for(int j=0;j<=i;j++){
                    printf("%c ",stack.item[i]);
                }
            */ 
            }
            else{
                error = 1;
                break;
            }
        }
        ++i;
    }
    //if we do not have any error but stack is still not empty
    if(!error && !isEmpty(&stack)){
        error = 1;
    }
    return error;
}

int correctBracketOrder(char stackTop, char right){

    //correct order of brackets {[( )]} 
    int warn = 0;

    

    return warn;
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