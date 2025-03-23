#include<stdio.h>

char* readString(){
    char* str;
    scanf("%c[^\n]%*c", str);

    return str;
}

void removeSpace(char* str){
    char* str2 = str;
    do{
        while(*str2 == ' ')
            str2++;
    }while(*str++ = *str2++);
    str = '\0';
}