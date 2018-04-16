#include <stdio.h>
#include <math.h>

int prime(int n, int devisor)
{
    if (n < 2)
    {
        return -1;
    }
    else if (n % devisor == 0)
    {
        return 0;
    }
    else if (devisor == 2)
    {
        return 1;
    }
    else
    {
        return prime(n, devisor-1);
    }
}

int main()
{
    double n;
    int total;

    printf("Enter which prime number in the sequence you want:\n");
    scanf("%lf", &n);

    total = prime(n, n-1);

    if (total == -1)
    {
        printf("number must be 2 or greater\n");
    }
    else if (total == 0)
    {
        printf("not prime\n");
    }
    else
    {
        printf("prime\n");
    }
    return 0;
}

