#ifndef SOLVER_H
#define SOLVER_H

#include <math.h>
#include "parser.h"

float power(float num, float pow)
{
    if(pow > 0 )
        return num * power(num, pow - 1);
    else if (pow < 0)
        return (1/num) * power(num, pow + 1);
    else
        return 1;
}

int precedence(Token_t t)
{
    switch(t)
    {
        case ADD:
        case SUBTRACT:
            return 1;
        case MULTIPLY:
        case DIVIDE:
        case MOD:
            return 2;
        case POW:
            return 3;
    }
}

int toInt(char* str, Token t, int curr)
{
    int factor = 1;
    int i, digit;
    if(curr > t.end)
        return 0;
    for(i = 0; i < t.end - curr; i++, factor*=10);
    
    digit = ((int) str[curr]) - 48; //48 is ascii for 0
    return digit*factor + toInt(str, t, curr+1);
}

float toFloat(char* str, Token t, int curr)
{
    float factor = 1;
    int i, digit;
    if(curr > t.end)
        return 0;
    if(str[curr] == '.')
        curr++;
    for(i = 0; i <= t.end - curr; i++, factor /= 10);

    digit = ((int) str[curr]) - 48;
    return digit*factor + toFloat(str, t, curr+1);
}

//shunting yard
void toRPN(char* str, float* numbers, Token_t* queue, Token* t,  int* rear)   //turns to RPN and uses array of float to check each num
{
    int i = 0, j = 0, negative = 1;
    int top = -1;
    Token_t stack[100];
    while(t[i].token != END)
    {
        if(t[i].token == DIGIT)
        {
            numbers[(j++)] = toInt(str, t[i], t[i].start);  //store to number collection
            if(t[i+1].token == FLOAT)
            {
                numbers[j-1] +=toFloat(str, t[++i], t[i].start);   //add floating point part to that index
            }
            numbers[j-1] *= negative;
            negative = 1;
            queue[++(*rear)] = DIGIT;   //store to output queue
        }
        else if(t[i].token == FLOAT)
        {
            numbers[j++] = toFloat(str, t[i], t[i].start);
            numbers[j-1] *= negative;
            negative = 1;
            queue[++(*rear)] = DIGIT;
        }
        else if(isTokenFunction(t[i].token)){
            stack[++top] = t[i].token;
        }
        else if(t[i].token == ADD || t[i].token == SUBTRACT || t[i].token == MULTIPLY || t[i].token == DIVIDE || t[i].token == POW || t[i].token == MOD)
        {
            if(t[i].token == SUBTRACT && *rear > -1 && (t[i-1].token != FLOAT && t[i-1].token != DIGIT)) //check if prev symbol is not a num
            {
                negative = -1;
            }
            else{
                while(top >= 0 && stack[top] != LEFT_P && (precedence(stack[top]) >= precedence(t[i].token)) && (t[i].token != POW))
                {
                    queue[++(*rear)] = stack[top--]; //pop from stack then push to output queue
                }
                stack[++top] = t[i].token;   //push to stack
            }
        }
        else if(t[i].token == LEFT_P)
        {
            stack[++top] = LEFT_P;  //push left_p to stack
        }
        else if(t[i].token == RIGHT_P)
        {
            while(top != -1 && stack[top] != LEFT_P)
            {
                queue[++(*rear)] = stack[top--];
            }
            if(top != -1)
                top--;   //remove left_p 
        }
        i++;
    }
    while(top != -1)
        queue[++(*rear)] = stack[top--]; //pop remaining operators into queue
}

int solve(float* res, float* numbers, Token_t* queue, int rear, error *e)
{

    float stack[100];
    int top = -1;
    int i = 0, j = 0;

    while(i <= rear)
    {
        if(queue[i] == DIGIT)
            stack[++top] = numbers[j++];
        else    //found operator
        {
            switch(queue[i])
            {
                case ADD:
                    stack[top - 1] = stack[top - 1] + stack[top];    //store sum of two nums to top - 1
                    top--;
                    break;
                case SUBTRACT:
                    stack[top - 1]= stack[top - 1] - stack[top];    //store sum of two nums to top - 1
                    top--;
                    break;
                case DIVIDE:
                    if(stack[top] == 0){
                        *e = UNDEFINED;
                        return 1;
                    }
                    stack[top - 1]= stack[top - 1] / stack[top];    //store sum of two nums to top - 1
                    top--;
                    break;
                case MULTIPLY:
                    stack[top - 1]= stack[top - 1] * stack[top];    //store sum of two nums to top - 1
                    top--;
                    break;
                case MOD:
                    if(stack[top] == 0){
                        *e = UNDEFINED;
                        return 1;
                    }
                    stack[top - 1] =(int) stack[top-1] % (int) stack[top];
                    top--;
                    break;
                case POW:
                    stack[top - 1] = power(stack[top - 1], stack[top]);
                    top--;
                    break;
                case SIN:
                    stack[top] = sin(stack[top]);
                    break;
                case COS:
                    stack[top] = cos(stack[top]);
                    break;
                case TAN:
                    stack[top] = tan(stack[top]);
                    break;
                case SEC:
                    stack[top] = 1/cos(stack[top]);
                    break;
                case CSC:
                    stack[top] = 1/sin(stack[top]);
                    break;
                case COT:
                    stack[top] = 1/tan(stack[top]);
                    break;
                case LOG:
                    if(stack[top] == 0){
                        *e = OUT_OF_FUNCTION_SCOPE;
                        return 1;
                    }
                    stack[top] = log(stack[top]);
                    break;
                case FLR:
                    stack[top] = floor(stack[top]);
                    break;
                case CEI:
                    stack[top] = ceil(stack[top]);
                    break;
            }
        }
        i++;
    }

    *res = stack[0];
    return 0;
}


#endif