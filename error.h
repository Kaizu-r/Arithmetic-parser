#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

typedef enum {
    UNBALANCED, //for parenthesis
    INVALID,    //not valid stirng
    UNDEFINED,  //math error
    OUT_OF_FUNCTION_SCOPE //value not in function scope (for log)

} error;

void printError(error e){
    switch(e){
        case UNBALANCED:
            printf("ERROR (UNBALANCED): Parenthesis are not balanced\n\n");
            break;
        case INVALID:
            printf("ERROR (INVALID): String cannot be generated by the language\n\n");
            break;
        case UNDEFINED:
            printf("ERROR (UNDEFINED): Attempting to divide by zero\n\n");
            break;
        case OUT_OF_FUNCTION_SCOPE:
            printf("ERROR (OUT OF SCOPE): Value outside of function's domain\n\n");
    }
}





#endif