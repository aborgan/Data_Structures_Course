#include <stdio.h>

int factorial(int n)
{
    int total = 1;
    if (n == 1 || n == 0)
    {
        return total;
    }
    else if (n < 0)
    {
        return -1;
    }
    else
    {
        return n * factorial(n-1);
    }
}

int main(void)
{
    int n;
    int total;

    printf("Enter the number you wish to take the factorial of\n");
    scanf("%d", &n);
    total = factorial(n);
    if (total != -1)
    {
        printf("The factorial of %d is %d\n", n, total);
    }
    else
    {
        printf("you can't take the factorial of a negative number!\n");
    }
    return 0;
}
