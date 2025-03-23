#include<stdio.h>

void removeSpace(char* str){
    char* str2 = str;
    do{
        while(*str2 == ' ')
            str2++;
    }while(*str++ = *str2++);
    str = '\0';
}

void tokenize(int* arr, char* str){ //push an int to arr depending on the symbol
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
            
        }
        i++;
    }
}