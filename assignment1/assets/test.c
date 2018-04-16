#include <stdio.h>
#include <stdlib.h>

int main()
{
    signed int test = 2147483647;
    char test2 [500] = "123456123456";
    printf("test is %d\n", test);
    printf("test2 is %d\n", atoi(test2));
    return 0;
}
