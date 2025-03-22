#include<string.h>

void removeSpace(char* str){
    int i = 0;
    int j = 0;
    char* str2;
    while(str[i] != '\0'){
        if(str[i++] != ' '){
            strcat(str2, (char*) str[i]);
            j++;
        }
            
    }
    str2[j] = '\0';
    strcpy(str, str2);
    
}