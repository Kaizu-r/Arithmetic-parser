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
    END
    
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

int isOperator(char c){
    switch(c){
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
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
    *str = '\0';
}

int tokenize(char* str, Token* arr)
{
    int i = 0, j= 0;
    while(str[i] != '\0')    //read string, tokenize
    {

        if(isDigit(str[i]))
        {
            arr[j].token = DIGIT;
            arr[j].start = i;
            while(isDigit(str[i+1]) && str[i+1] != EOF) 
                i++;
            arr[j++].end = i;
            
        }
        else if(isOperator(str[i]))
        {
            arr[j].start = i;
            arr[j].end = i;
            switch(str[i])
            {
                case '+': arr[j].token = ADD; break;
                case '-': arr[j].token = SUBTRACT; break;
                case '*': arr[j].token = MULTIPLY; break;
                case '/': arr[j].token = DIVIDE; break;
                case '%': arr[j].token = MOD; break;
            }
            j++;
        }
        else if(str[i] == '(')
        {
            arr[j].start = i;
            arr[j].end = i;
            arr[j++].token = LEFT_P;
        }
        else if(str[i] == ')')
        {
            arr[j].start = i;
            arr[j].end = i;
            arr[j++].token = RIGHT_P;
        }
        else if(str[i] == '\0' || str[i] == '\n')
        {
            arr[j].start = i;
            arr[j].end = i;
            arr[j++].token = END;
            return 0;
        }
        else    //not in language
        {
            return 1;   
        }
        i++;
    }

}

//checks balanced parenthesis
int isBalanced(Token* t)
{
    int top = 0, i = 0;
    while(t[i].token != END && top >= 0)
    {
        if(t[i].token == LEFT_P)
            top++;  
        else if(t[i].token == RIGHT_P)   //means there must already be LEFT_P
            top--;
        i++;
    }
    if(!top)    //balanced
        return 1;
    return 0; 
}

int toInt(char* str, Token t, int curr)
{
    int factor = 1;
    int i, digit;
    if(curr > t.end)
        return 0;
    for(i = 0; i < t.end - curr; i++, factor*=10);
    
    digit = ((int) str[curr]) - 48; //30 is ascii for 0
    return digit*factor + toInt(str, t, curr+1);
}