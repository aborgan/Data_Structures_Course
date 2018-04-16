//This is an example of a stack data structure

#include <stdio.h>
#include <string.h>

char stack[100];
int top = 0;

void push(char c)
{
    stack[top] = c;
    top+=1;
}

char pop()
{
    top-=1;
    return stack[top];
}

int main()
{
    char str[100];
    printf("Input\n");
    scanf("%s", str);

    int len = strlen(str);
    int i = 0;
    for (i; i < len; i+=1)
    {
        push(str[i]);
    }
    int flag = 1;
    i = 0;
    for (i; i < len; i+=1)
    {
        if(str[i] != pop())
        {
            flag = 0;
        }
    }
    if (flag)
    {
        printf("success\n");
    }
    else
    {
        printf("Not palindrome\n");
    }

    return 0;
}
