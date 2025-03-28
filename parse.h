#include<stdio.h>


typedef enum tok{
    DIGIT,
    FLOAT,
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    MOD,
    POW,
    SIN,
    COS,
    TAN,
    MAX,
    LEFT_P,
    RIGHT_P,
    ARITH,
    FUNC,
    TERM,
    FACTOR,
    FUNCTION,
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
        else if(t[i].token == ADD || t[i].token == SUBTRACT || t[i].token == MULTIPLY || t[i].token == DIVIDE || t[i].token == POW)
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

float solve(float* numbers, Token_t* queue, int rear)
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
                    break;
                case SUBTRACT:
                    stack[top - 1]= stack[top - 1] - stack[top];    //store sum of two nums to top - 1
                    break;
                case DIVIDE:
                    stack[top - 1]= stack[top - 1] / stack[top];    //store sum of two nums to top - 1
                    break;
                case MULTIPLY:
                    stack[top - 1]= stack[top - 1] * stack[top];    //store sum of two nums to top - 1
                    break;
                case MOD:
                    stack[top - 1] =(int) stack[top-1] % (int) stack[top];
                    break;
                //add pow
                    
            }
            top--;
        }
        i++;
    }

    return stack[0];
}
