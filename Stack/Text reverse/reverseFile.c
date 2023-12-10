#include<stdio.h>
#include<stdlib.h>

typedef struct {
    /*
    For the stack to be dynamically allocated we need to have a pointer to hold the base address of the arrray, also, since the size will be different for different instances of Stack so we need to keep the size inside the struct object.
    */
    char *item;
    int top;
    int size;
} Stack;

void init(Stack *, int);
void push(Stack *, char);
char pop(Stack*);
void deallocate(Stack *sp);
int getSize(Stack *sp);
int isUnderflow(Stack *);
int isOverflow(Stack *);
int reverseIt(char source[], char dest[]);

int getSize(Stack *sp){
    return sp->size;
}

void push(Stack *sp, char value){
    if(isOverflow(sp)){
        /*
        Instead of showing message stack overflow and returning to caller,
        we can grow the array to double its size by retaining the existing value
        */
        char *temp;
        temp = (char*) malloc(sizeof(char) * sp->size * 2);
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

char pop(Stack *sp){
    if(isUnderflow(sp)){
        printf("Stack underflow.\n");
        return 'x';
    }
    char value = sp->item[sp->top];
    sp->top--;
    return value;
}

void init(Stack *sp, int size){
    sp->top = -1;
    sp->item = (char* )malloc(sizeof(char) * size);
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

int reverseIt(char source[],char dest[]){
    FILE *fps, *fpd;
    const int SIZE= 50;
    fps = fopen(source, "r");
    if (fps == NULL){
        printf("Error opening file %s.\n",source);
        return 0;
    }

    fpd = fopen(dest, "w");
    if (fpd == NULL){
        printf("Error opening file %s.\n",dest);
        return 0;
    }

    Stack s;
    init(&s, SIZE);
    char buff;

    //fgetc reads a character from a text file.
    buff = fgetc(fps);
    while(!feof(fps)){
        push(&s,buff);
        buff = fgetc(fps);
    }
    //fputc writes a character to a text file
    while(!isUnderflow(&s)){
        fputc(pop(&s),fpd);
    }
    fclose(fps);
    fclose(fpd);
    deallocate(&s);
    return 1;
}


int main(){
    
    int f = reverseIt("textToReverse.txt", "reversedText.txt");
    if(f){
        printf("File reversed successfully.\n");
    }
    else{
        printf("Error - reversing failed.\n");
    }



    return 0;
}