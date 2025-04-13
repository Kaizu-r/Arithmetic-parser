#ifndef PARSER_H
#define PARSER_H
#include<stdio.h>
#include<math.h>
#include "error.h"

typedef enum tok{
    DIGIT,
    FLOAT,
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    MOD,
    POW,
    LEFT_P,
    RIGHT_P,
    SIN,
    COS,
    TAN,
    SEC,
    CSC,
    COT,
    LOG,
    FLR,
    CEI,
    END
    
}Token_t;

typedef struct {
    Token_t token;
    int start;  //starting index in string
    int end;    //ending index in string
}Token;

int arithParse(Token_t** t);    //crumbs
int digitParse(Token_t** t);
int factorPostParse(Token_t **t);
int factorParse(Token_t **t);
int termPostParse(Token_t **t);
int termParse(Token_t **t);
int arithPostParse(Token_t **t);
int arithParse(Token_t **t);
void printToken(Token_t t);


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
        case '^':
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

int isTokenFunction(Token_t t)
{
    switch(t){
        case SIN:
        case COS:
        case TAN:
        case CSC:
        case COT:
        case SEC:
        case CEI:
        case FLR:
        case LOG:
            return 1;
    }
    return 0;
}

int isStringFunction(char* str){
    switch(*str){
        case 's':
            if(*(str+1) == 'i' && *(str+2) == 'n')
                return 1;
            if(*(str+1) == 'e' && *(str+2) == 'c')
                return 1;
            break;
        case 'c':
            if(*(str+1) == 's' && *(str+2) == 'c')
                return 1;
            if(*(str+1) == 'o' && *(str+2) == 's')
                return 1;
            if(*(str+1) == 'o' && *(str+2) == 't')
                return 1;
            if(*(str+1) == 'e' && *(str+2) == 'i')
                return 1;
            break;
        case 'f':
            if(*(str+1) == 'l' && *(str+2) == 'r')
                return 1;
            break;
        case 't':
            if(*(str+1) == 'a' && *(str+2) == 'n')
                return 1;
            break;
        case 'l':
            if(*(str+1) == 'o' && *(str+2) == 'g')
                return 1;
            break;
    }
    return 0;
}

Token_t checkStringFunction(char* str){
    switch(*str){
        case 's':
            if(*(str+1) == 'i' && *(str+2) == 'n')
                return SIN;
            if(*(str+1) == 'e' && *(str+2) == 'c')
                return SEC;
            break;
        case 'c':
            if(*(str+1) == 's' && *(str+2) == 'c')
                return CSC;
            if(*(str+1) == 'o' && *(str+2) == 's')
                return COS;
            if(*(str+1) == 'o' && *(str+2) == 't')
                return COT;
            if(*(str+1) == 'e' && *(str+2) == 'i')
                return CEI;
            break;
        case 'f':
            if(*(str+1) == 'l' && *(str+2) == 'r')
                return FLR;
            break;
        case 't':
            if(*(str+1) == 'a' && *(str+2) == 'n')
                return TAN;
            break;
        case 'l':
            if(*(str+1) == 'o' && *(str+2) == 'g')
                return LOG;
            break;
    }

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
        else if(str[i] == '.')   //float
        {
            arr[j].token = FLOAT;
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
                case '^': arr[j].token = POW; break;
            }
            j++;
        }
        else if(isStringFunction(&str[i])){
            arr[j].token = checkStringFunction(&str[i]);
            arr[j].start = i;
            arr[j].end = i+2;
            i+=2;
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
int isBalanced(Token* t, error* e)
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
    if(!top){
        *e = UNBALANCED;
        return 1;
    }
    return 0; 
}




int digitParse(Token_t** t){
    printf("DIGIT PARSE\n");
    if(**t == FLOAT){
        printf("FLOAT");
        (*t)++;
        return 1;
    }
    if(**t == DIGIT){
        printf("DIGIT ");
        (*t)++;
        if(**t == FLOAT){
            printf("FLOAT ");
            (*t)++;
        }
        return 1;
    }
    return 0;
    
}

int factorPostParse(Token_t **t){
    printf("FACTOR PARSE\n");
    if(**t == POW ){
        printf("POW ");
        (*t)++;
        if(digitParse(t)){
            if(factorPostParse(t))
                return 1;
        }
        return 0;
    }
    
    
    return 1;
}

int factorParse(Token_t **t){
    printf("FACTOR\n");
    if(**t == DIGIT || **t == FLOAT){
        if(digitParse(t)){
            if(factorPostParse(t))
                return 1;
        }
    }
    else if(**t == SUBTRACT){
        (*t)++;
        if(digitParse(t)){
            if(factorPostParse(t))
                return 1;
        }
    }
    else if(isTokenFunction(**t)){
        printToken(**t);
        (*t)++;
        if(**t == LEFT_P)
        {
            (*t)++;
            if(arithParse(t)){
                if(**t == RIGHT_P){
                    printf("RIGHT_P");
                    (*t)++;
                    return 1;
                }
            }
        }
    }
    else if(**t == LEFT_P){
        printf("LEFT_P ");
        (*t)++;
        if(arithParse(t)){
            printToken(**t);
            if(**t == RIGHT_P){
                printf("RIGHT_P ");
                (*t)++;
                return 1;
            }
        }
    }

    return 0;
    
}
int termPostParse(Token_t **t){
    printf("TERM POST\n");
    if(**t == MULTIPLY || **t == DIVIDE){
        printf(((**t == MULTIPLY) ? "MULTIPLY " : "DIVIDE "));
        (*t)++;
        if(factorParse(t)){
            if(termPostParse(t))
                return 1;
        }
        return 0;
    }
    return 1;
}

int termParse(Token_t **t){
    printf("TERM\n");
    if(factorParse(t)){
        (*t)++;
        if(termPostParse(t))
            return 1;
    }
    return 0;
}

int arithPostParse(Token_t **t){
    printf("ARITH POST\n");
    if(**t == SUBTRACT || **t == ADD){
        printf(((**t == SUBTRACT) ? "SUBTRACT " : "ADD "));
        (*t)++;
        if(termParse(t)){
            if(arithPostParse(t))
                return 1;
        }
        return 0;
    }
    return 1;
}

int arithParse(Token_t **t){
    printf("ARITH\n");
    if(termParse(t)){
        (*t)++;
        if(arithPostParse(t))
            return 1;
    }
    return 0;
}

int validate(Token_t *t, error* e){
    if(arithParse(&t))
        return 1;
    *e = INVALID;
    return 0;
}

void printToken(Token_t t){
    switch(t)
    {
        case DIGIT:
            printf("DIGIT ");
            break;
        case FLOAT:
            printf("FLOAT ");
            break;
        case ADD:
            printf("ADD ");
            break;
        case SUBTRACT:
            printf("SUBTRACT ");
            break;
        case MULTIPLY:
            printf("MULTIPLY ");
            break;
        case DIVIDE:
            printf("DIVIDE ");
            break;
        case POW:
            printf("POW ");
            break;
        case MOD:
            printf("MOD ");
            break;
        case LEFT_P:
            printf("LEFT_P ");
            break;
        case RIGHT_P:
            printf("RIGHT_P ");
            break;
        case SIN:
            printf("SIN ");
            break;
        case COS:
            printf("COS ");
            break;
        case CSC:
            printf("CSC ");
            break;
        case TAN:
            printf("TAN ");
            break;
        case SEC:
            printf("SEC ");
            break;
        case COT:
            printf("COT ");
            break;
        case LOG:
            printf("LOG ");
            break;
        case FLR:
            printf("FLR ");
            break;
        case CEI:
            printf("CEI ");
            break;
        case END:
            printf("END ");
            break;
        default:
            printf("ERR ");
    }
}



#endif