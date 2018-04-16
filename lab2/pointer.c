#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int isVowel(char* c)
{
    char * temp = malloc(sizeof(char));
    *temp = *c;
    *c = tolower(*c);
    if(*c == 'a' || *c == 'e' || *c == 'i' || *c == 'o' || *c == 'u' || *c == 'y')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    char str[100];

    printf("Enter a String\n");
    scanf("%s", str);

    for (int i = 0; strlen(str); i+=1)
    {
        if (isVowel(str[i]))
        {
            str[i] = toupper(str[i]);
        }
    }
    printf("%s\n", str);
    return 0;
}
