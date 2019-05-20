#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#define MAX_SIZE 101

typedef union
{
    float fData;
    char* cpData;
} Item;

typedef struct
{
    int top;
    Item data[MAX_SIZE];

} Stack;

void init(Stack *s)
{
    // int	top=0;
    s->top=0;
}

int isEmpty(Stack *s)
{
    if(s->top==0)
        return 1;
    else
        return 0;
}

Item top(Stack *s)
{
    //Item first;


    return s->data[s->top-1];
}

Item pop(Stack *s)
{
    s->top--;
    Item temp= s->data[s->top];
    return temp;
}

void push(Stack *s, Item val)
{
    s->data[s->top]= val;
    s->top++;
    //top++;
    // s->top++;

}

void destroy(Stack *s)
{
    int count=0;

    while(!isEmpty(s))
    {
        count++;
        push(s,pop(s));
    }
    for(int i=1; i<count; i++)
        pop(s);
}

int Operators(char* c)
{
    if(strcmp(c,"^")==0|| strcmp(c,"*")==0|| strcmp(c, "/")==0|| strcmp(c,"+")==0|| strcmp(c,"-")==0 || strcmp(c,")")==0 || strcmp(c,"(")==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int operationOrder(char* symbol)
{
    if(strcmp(symbol,"^") == 0)
    {
        return(3);
    }
    else if(strcmp(symbol,"*")==0 || strcmp(symbol,"/")==0)
    {
        return(2);
    }
    else if(strcmp(symbol,"+")==0 || strcmp(symbol,"-")==0)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}
void infixToPostfix(char* infix, char* postfix)
{
    Stack stack;
    init(&stack);
    Item data;
    Item ch;
    char *token;
    char space[2] = " ";
    token = strtok(infix, space);
    while (token != NULL)
    {
        data.cpData = token;
        if (Operators(data.cpData) == 0)
        {
            strcat(postfix,data.cpData);
            strcat(postfix," ");
        }
        else if (Operators(data.cpData) == 1)
        {
            if (data.cpData == '(')
            {
                push(&stack, data);
            }
            else
            {
                if (data.cpData == ')')
                {
                    while (top(&stack).cpData != '(')
                    {
                        ch=pop(&stack);
                        strcat(postfix,ch.cpData);
                        strcat(postfix," ");
                    }
                    if (data.cpData == '(')
                    {
                        pop(&stack);
                    }
                }
                else if(strcasecmp(data.cpData,"+") == 0 || strcasecmp(data.cpData,"-") == 0 || strcasecmp(data.cpData,"^") == 0 || strcasecmp(data.cpData,"*") == 0 || strcasecmp(data.cpData,"/") == 0)
                {
                    while (!isEmpty(&stack) && operationOrder(data.cpData) <= operationOrder(top(&stack).cpData))
                    {
                        ch=pop(&stack);
                        strcat(postfix,ch.cpData);
                        strcat(postfix," ");
                    }
                    push(&stack, data);
                    if (!isEmpty(&stack) && operationOrder(data.cpData) > operationOrder(top(&stack).cpData))
                    {
                        push(&stack, data);
                    }
                }
            }
        }
        token = strtok(NULL, space);
    }
    while (!isEmpty(&stack))
    {
        ch=pop(&stack);
        strcat(postfix,ch.cpData);
        strcat(postfix," ");
    }
    strcat(postfix,"\0");
}



float evaluatePostfix(char* postfix)
{


    int i ;
    Item ch;
    Item val;
    Item A, B ;
    Stack s;
    init(&s);

    char *token;
    char space[2] = " ";
    //token = strtok(infix, space);
    while (token != NULL)
    {
        ch.cpData = token;

        if (isdigit(postfix[i]))
        {
            ch.fData= postfix[i]- '0';

            push( &s,ch );
        }
        else
        {
            A.fData = pop(&s).fData;
            B.fData = pop(&s).fData;
           if(strcmp(ch.cpData,"*")==0)
                val.fData = B.fData * A.fData;
            if(strcmp(ch.cpData,"/")==0)
                val.fData = B.fData / A.fData;
            if(strcmp(ch.cpData,"+")==0)
                val.fData = B.fData + A.fData;
            if(strcmp(ch.cpData,"-")==0)
                val.fData =B.fData - A.fData;
     }
        push(&s,val);

    }
    val.fData=pop(&s).fData;
    return val.fData;
}

void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);

        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);

        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);

        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
