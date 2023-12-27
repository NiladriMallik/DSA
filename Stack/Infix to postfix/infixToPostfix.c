#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SIZE 100

typedef struct{
    char item[SIZE];
    int top;
}OperatorStack;

typedef struct{
    double item[SIZE];
    int top;
}OperandStack;


//for operator stack
void opr_push(OperatorStack *, char);
char opr_pop(OperatorStack *);
int isEmpty(OperatorStack *);

//for operand stack
int isEmptyOperandStack(OperandStack *);
double operand_pop(OperandStack *);
void operand_push(OperandStack *, double);

void convert(char[], char[]);
int prcd(char, char);

int isEmpty(OperatorStack *stack){
    return stack->top == -1;
}


int isEmptyOperandStack(OperandStack *stack){
    return stack->top == -1;
}


void opr_push(OperatorStack *stack, char v){
    if(stack->top == SIZE - 1){
        printf("Stack overflow, terminating program.\n");
        exit(1);
    }
    stack->item[++stack->top] =v;
}


char opr_pop(OperatorStack *stack){
    if(isEmpty(stack)){
        printf("Stack underflow, terminating program.\n");
        exit(1);
    }
    return stack->item[stack->top--];
}


int prcd(char left, char right){
    if(left == '(' || right == '(')
        return 0;
    if(right == ')')
        return 1;    
    if(left == '*' || left == '/'){
        if(right == '*' || right == '/' || right == '+' || right == '-')
            return 1;
        else
            return 0;
    }  
    if(left == '+' || left == '-'){
        if(right == '+' || right == '-')
            return 1;
        else
            return 0;
    }  
    if(left == '$'){
        return 1;
    }
    else
        return 0;
}


void convert(char infix[], char postfix[]){
    OperatorStack stack;
    stack.top = -1;
    int i = 0, j = 0;
    while(infix[i] != '\0'){
        char token = infix[i];
        //if token is an operand
        if(token >= '0' && token <='9'){
            postfix[j++] = token;
        }
        //if token is operator
        else if(token == '+' || token == '-' || token == '/' || token == '*' || token == '$' || token == '(' || token == ')'){
            while(stack.top != -1 && prcd(stack.item[stack.top], token)){
                char top_opr = opr_pop(&stack);
                postfix[j++] = top_opr;
            }
            if (token != ')'){
                opr_push(&stack, token);
            }
            else
                opr_pop(&stack);
        }

        else{
            printf("Invalid character %c, terminating character.\n",token);
            exit(1);
        }
        i++;
    }//end of the outer while loop
    while(stack.top != -1){
        char  top_opr = opr_pop(&stack);
        postfix[j++] = top_opr;
    }
    postfix[j] = '\0';
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
            operand_push(&stack, (double)v);
        }
        else if(token == '+' || token == '-' || token == '*' || token == '/' || token == '$'){
            double opnd1 = operand_pop(&stack);
            double opnd2 = operand_pop(&stack);
            double result = operate(opnd2, opnd1,  token);
            operand_push(&stack, result);
        }
        else{
            printf("Invalid symbol encountered.\n");
            exit(1);
        }
        ++i;
    }
    return operand_pop(&stack);
}


void operand_push(OperandStack *sp, double value){
    //checking for overflow
    if(sp->top == SIZE - 1){
        printf("Stack overflow, terminating program");
        exit(1);
    }

    //otherwise push
    // sp->top;
    sp->item[++sp->top] = value;
}

//pop operation
double operand_pop(OperandStack *osp){
    if(isEmptyOperandStack(osp)){
        printf("Stack underflow, terminating program");
        exit(1);
    }

    return osp->item[osp->top--];
}



int main(){
    char infix[SIZE];
    char postfix[SIZE];

    printf("Input infix: ");
    scanf("%s", infix);

    convert(infix, postfix);
    printf("The equivalent postfix expression is: %s.\n",postfix);

    double result = evalPostfix(postfix);
    printf("The value of the postfix expression is %lf.\n",result);

    return 0;
}