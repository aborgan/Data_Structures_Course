#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

float floatstack[100];
int fstail = 0;

char charstack[100];
int cstail = 0;

void solve(){
    float op2 = floatstack[--fstail];
    float op1 = floatstack[--fstail];

    char symbol = charstack[--cstail];

    switch(symbol){
        case '*':
            floatstack[fstail++] = op1*op2;
            break;
        case '+':
            floatstack[fstail++] = op1+op2;
            break;
        case '-':
            floatstack[fstail++] = op1-op2;
            break;
        case '/':
            floatstack[fstail++] = op1/op2;
            break;
        default:
            break;
    }
    cstail--;
}

int main(int argc, char * argv[]){

    char str[strlen(argv[1])];
    strcpy(str, argv[1]);

    int i;
    for(int i = 0; i < strlen(str); i+=1){
        if(isdigit(str[i])){
            char temp[5];
            strncpy(temp, &str[i], 4);
            temp[4] = '\0';
            float f = atof(temp);
            floatstack[fstail++] = f;
            i+=3;
        }
        else if (str[i] != ')'){
            charstack[cstail++] = str[i];
        }
        else{
            solve();
        }
    }
    printf("total is %.2f\n", floatstack[fstail-1]);
    return 0;
}
