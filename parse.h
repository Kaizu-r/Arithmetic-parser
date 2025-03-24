#include<stdio.h>

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
    while(str[i] != '\0'){
        switch(str[i]){
            case '+':
            case '-':
            case '/':
            case '*':
                arr[i] = 1;
                break;
            case '(':
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
                arr[i] = 4;
                break;
            default:
                arr[i] = 0; //for error
                return 1;   //error
            
        }
        i++;
    }
    arr[++i] = -1;  //terminating 
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
            str[j] = 'b';
        if(arr[i] == 2)
            str[j] = 'c';
        if(arr[i] == 3){
            str[j]  == 'd';
        }
        i++, j++;
    }
    str[j] = 'e';   //end
}

