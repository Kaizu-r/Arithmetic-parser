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

int tokenize(int* arr, char* str)
{     //push an int to arr depending on the symbol
    int i = 0;
    while(str[i] != EOF){
        switch(str[i]){
            case '+':
            case '-':
            case '/':
            case '*':
                printf("0");
                arr[i] = 1;
                break;
            case '(':
                printf("0");
                arr[i] = 2;
                break;
            case ')':
                arr[i] = 3;
                break;
            case'1':
            case'2':
            case'3':
            case'4':
            case'5':
            case'6':
            case'7':
            case'8':
            case'9':
            case'0':
                printf("0");
                arr[i] = 4;
                break;
            case ' ':
                break;
            
        }
        i++;
    }
    printf("2");
    return 0;
}

void toTerminal(char* str, int* arr)    //converts per char token to terminal string
{
    int i = 0, j = 0; 
    while(arr[i] != -1)
    {
        if(arr[i] == 4) //digit
        {
            do{} while(arr[i++] == 4 && arr[i] != -1);
            str[j] = 'a';
        }
        if(arr[i] == 1)
            str[j] = 'b';   //operatr
        if(arr[i] == 2)
            str[j] = 'c';   //open parenthesis
        if(arr[i] == 3){
            str[j]  == 'd'; //close parenthesis
        }
        i++, j++;
    }
    str[j] = '\0';   //end
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