#include<stdio.h>

typedef enum tok{
    DIGIT,
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    MOD,
    LEFT_P,
    RIGHT_P,
    
}Token_t;

typedef struct {
    Token_t token;
    int start;  //starting index in string
    int end;    //ending index in string
}Token;

void removeSpace(char* str)
{
    char* str2 = str;
    do{
        while(*str2 == ' ')
            str2++;
    }while(*str++ = *str2++);
    str = '\0';
}

void tokenize(char* str, Token* arr)
{
    int i = 0;
    
}



//checks balanced parenthesis
int isBalanced(char* str){
    int top = 0, i = 0;
    char stack[strlen(str)];

    while(i++ < strlen(str)){
        if(str[i] == 'c')
        {
            stack[top++] = 'c'; 
        }
        else if(str[i] == 'd')
            top--;
    }
    if(!(top))  //top = 0
    {
        return 1;
    }
    return 0;


}