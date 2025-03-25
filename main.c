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

    int j = 0;
    while(t[j].token != END){
        printf("%d ", t[j].token);
        j++;
    }
    printf("%d ", t[j].token);

    return 0;
}