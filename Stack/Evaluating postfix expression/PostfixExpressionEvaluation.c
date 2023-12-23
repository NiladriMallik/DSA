#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SIZE  100

typedef struct{
    double item[SIZE];
    int top;
}OperandStack;


//function prototypes
//function for stack operators
void push(OperandStack *, double);
double pop(OperandStack *);
double operate(double, double, char);
double evalPostfix(char[]);
int isEmpty(OperandStack *);


int isEmpty(OperandStack *stack){
    return stack->top == -1;
}
//push operation
void push(OperandStack *sp, double value){
    //checking for overflow
    if(sp->top == SIZE - 1){
        printf("Stack overflow, terminating program");
        exit(1);
    }

    //otherwise push
    sp->top++;
    sp->item[sp->top] = value;
}

//pop operation
double pop(OperandStack *osp){
    if(isEmpty(osp)){
        printf("Stack underflow, terminating program");
        exit(1);
    }

    return osp->item[osp->top--];
}

double operate(double LeftOpnd, double RightOpnd, char opr){
    double result = 0.0;

    switch (opr){
        case '+' : result = LeftOpnd + RightOpnd;
                   break;
        case '-' : result = LeftOpnd - RightOpnd;
                   break;
        case '/' : result = LeftOpnd / RightOpnd;
                   break;
        case '*' : result = LeftOpnd * RightOpnd;
                   break;
        case '$' : result = pow(LeftOpnd, RightOpnd);
                   break;
        default: printf("%c is not a valid operator.\n",opr);
                 exit(1);
    }
    return result;
}

double evalPostfix(char postfix[]){
    OperandStack stack;
    stack.top = -1;
    int i = 0;
    while(postfix[i] != '\0'){
        char token = postfix[i];
        if (token >= '0' && token <= '9'){
            int v = token -'0';
            push(&stack, (double)v);
        }
        else if(token == '+' || token == '-' || token == '*' || token == '/' || token == '$'){
            double opnd1 = pop(&stack);
            double opnd2 = pop(&stack);
            double result = operate(opnd1, opnd2,  token);
            push(&stack, result);
        }
        else{
            printf("Invalid symbol encountered.\n");
            exit(1);
        }
        ++i;
    }
    return pop(&stack);
}


int main(){
    char postfix[SIZE];
    printf("Input the postfix expression: ");
    scanf("%s",postfix);

    double result = evalPostfix(postfix);
    printf("Result: %lf\n",result);
    return 0;
}