#include<stdio.h>
#include <string.h>
#include "parse.h"

int main(){
    printf("Enter: ");
    char str[100];
    int arr[100] = {0};
    fgets(str, 100, stdin);
    printf(str);
    removeSpace(str);
    printf(str);
    tokenize(arr, str);
    for(int i = 0; i < strlen(str) -1; i++)
        printf("%d", arr[i]);
    return 0;
}