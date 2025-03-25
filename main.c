#include<stdio.h>
#include <string.h>
#include "parse.h"

int main()
{
    printf("Enter: ");
    char str[100];
    char terminals[100];
    int arr[100] = {0};
    fgets(str, 100, stdin);
    printf(str);
    removeSpace(str);
    printf(str);
    
    Token t[100];
    if(tokenize(str, t))
        printf("FAILED\n");
    printf("x\n");
    if(isBalanced(t))
        printf("BALANCED\n");

    return 0;
}