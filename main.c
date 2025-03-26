#include<stdio.h>
#include <string.h>
#include "parse.h"

int main()
{
    char str[100];
    Token t[100];
    float numbers[100];
    Token_t queue[100];
    int rear = -1;

    printf("Enter: ");
    fgets(str, 100, stdin);
    removeSpace(str);
    
    if(tokenize(str, t))
        printf("FAILED\n");
    if(isBalanced(t))
        printf("BALANCED\n");
   
    toRPN(str, numbers, queue, t, &rear);

    for(int i = 0, j = 0; i <= rear; i++)
    {
        if(queue[i] == DIGIT)
            printf("%f ", numbers[j++]);
        else if(queue[i] == ADD)
            printf("+ ");
        else if(queue[i] == SUBTRACT)
            printf("- ");
        else if(queue[i] == MULTIPLY)
            printf("* ");
        else if(queue[i] == DIVIDE)
            printf("/ ");
        else
            printf("e ");
    }

    float answer = solve(numbers, queue, rear);
    printf("\nResult: %f\n", answer);

    return 0;
}