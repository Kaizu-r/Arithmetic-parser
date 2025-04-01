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
   
    Token_t arr[100];
    int l = 0;
    Token *k = t;
    while(k->token != END){
        arr[l++] = k++->token;
    }
    arr[l] = END;
    
    for(l = 0; arr[l] != END; l++){
        printToken(arr[l]);
    }




    if(!validate(arr)){
        printf("\n String not Valid\n");
        return 0;
    }



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
        else if (queue[i] == POW)
            printf("^ ");
        else if (queue[i] == MOD)
            printf("%% ");
    }

    float answer = solve(numbers, queue, rear);
    printf("\nResult: %f\n", answer);

    return 0;
}