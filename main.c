#include<stdio.h>
#include <string.h>
#include "parser.h"
#include "solver.h"
#include "error.h"

int main()
{
    char str[100];
    Token t[100];   //token array
    float numbers[100];
    Token_t queue[100];
    error e;
    int rear = -1;
    Token_t arr[100];
    int l = 0;  //counter for token_t array
    Token *k = t;   //pointer for parsing
    float answer;

    printf("====ARITHMETIC PARSER====\n\n");
    printf("Enter string: ");
    fgets(str, 100, stdin);
    printf("\nRemoving spaces...\n");
    removeSpace(str);
    
    printf("\nTokenizing...\n");
    if(tokenize(str, t)){
        printf("FAILED!!! Exiting progran...\n");
        return 1;
    }
    printf("Tokenizing Succeful!!\n");
    printf("Checking for balanced parenthesis....\n");
    if(!isBalanced(t, &e)){
        printError(e);
        return 1;
    }
   printf("Balanced parenthesis\n\n");
    
    while(k->token != END){
        arr[l++] = k++->token;
    }
    arr[l] = END;
    printf("Token String: ");
    for(l = 0; arr[l] != END; l++){
        printToken(arr[l]);
    }



    printf("\nParsing...\n");

    if(!validate(arr, &e)){
        printError(e);
        return 1;
    }
    printf("Valid string!!\n");

    printf("Converting to Reverse Polish Notation...\n");
    toRPN(str, numbers, queue, t, &rear);


    printf("Reverse Polish: ");
    for(int i = 0, j = 0; i <= rear; i++)
    {
        if(queue[i] == DIGIT)
            printf("%f ", numbers[j++]);
        else
            printNonDigitToken(queue[i]);

    }

    printf("\n");
    
    printf("\nSOLVING EXPRESSION...\n");
    if(solve(&answer, numbers, queue, rear, &e)){
        printf("\n");
        printError(e);
        return 1;
    }

    printf("\nResult: %f\n", answer);

    return 0;
}