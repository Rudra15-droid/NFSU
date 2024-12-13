#include<stdio.h>
#include<stdlib.h>
#define MAX 100
typedef struct{
    char data[MAX];
    int top;
}Stack;
void init(Stack* a){
    a->top=-1;
}
void push(Stack* a,char c){
    a->data[++a->top]=c;
}
char pop(Stack* a){
    return a->data[a->top--];
}
char peep(Stack* a){
    return a->data[a->top];
}
int isEmpty(Stack* a){
    return a->top==-1;
}
int isOperand(char c){
    return (c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9');
}
int isOperator(char c){
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
}
int getPrecedance(char c){
    if(c=='+'||c=='-'){
        return 1;
    }else if(c=='*'||c=='/'){
        return 2;
    }else if(c=='^'){
        return 3;
    }else{
        return 0;
        }
}
int isParantheses(char c){
    return (c=='('||c==')');
}
void main(){
    char input[MAX],output[MAX];
    int i=0,outputIterator=0,recentIsOperator=1,validCharFound=0;
    Stack stack;
    init(&stack);
    printf("Enter the infix expression: ");
    fgets(input,sizeof(input),stdin);
    while(input[i]!='\n'&&input[i]!='\0'){
        char c=input[i];
        if(isOperand(c)){
            output[outputIterator++]=c;
            recentIsOperator=0;
            validCharFound=1;
        }else if(isOperator(c)){
            if(recentIsOperator){
                fprintf(stderr,"Illegal syntax: Two consecutive operators or operator at start of expression found at index %d \n",i);
                exit(-1);
            }
            recentIsOperator=1;
            validCharFound=1;
            if(!isEmpty(&stack)){
                while((!isEmpty(&stack))&&(getPrecedance(peep(&stack))>=getPrecedance(c))){
                    if(c=='^'&&peep(&stack)=='^'){
                        push(&stack,c);
                        goto postExp;
                    }
                    output[outputIterator++]=pop(&stack);
                }
            }
            push(&stack,c);
            {
            postExp:
                1;
            }
        }else if(isParantheses(c)){
            if(c=='('){
                push(&stack,c);
            }else{
                while(peep(&stack)!='('){
                    output[outputIterator++]=pop(&stack);
                }
                pop(&stack);
            }
            validCharFound=1;
        }else if(c!=' '){
            fprintf(stderr,"Unrecognized character %c at index %d",c,i);
            exit(-1);
        }
    i++;
    }
    while(!isEmpty(&stack)){
        output[outputIterator++]=pop(&stack);
    }
    output[outputIterator++]='\0';
    if(validCharFound){
        printf("Your result is: %s\n",output);
        if(i>=MAX-1){
        fprintf(stderr,"The output beyond the first %d character(s) might be limited. Please modify the value of MAX to get the full output",MAX);
    }
    }else
        printf("Empty string received. No output can be produced\n");

}

