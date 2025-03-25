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

int isDigit(char c) //chewck if digit
{
    switch(c)
    {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            return 1;
    }
    return 0;
}


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
    while(str[i] != EOF)    //read string, tokenize
    {
        if(str[i] )
    }
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