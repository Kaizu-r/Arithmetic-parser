#include<stdio.h>
#include<math.h>


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

int arithParse(Token_t* t);    //crumbs
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
    return 0;
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

float power(float num, float pow)
{
    if(pow > 0 )
        return num * power(num, pow - 1);
    else if (pow < 0)
        return (1/num) * power(num, pow + 1);
    else
        return 1;
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
                case POW:
                    stack[top - 1] = power(stack[top - 1], stack[top]);
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
                    stack[top] = log(stack[top]);
                    break;
                case FLR:
                    stack[top] = floor(stack[top]);
                    break;
                case CEI:
                    stack[top] = ceil(stack[top]);
                    break;
                

                    
            }
            top--;
        }
        i++;
    }

    return stack[0];
}


int digitParse(Token_t* t){
    printf("DIGIT PARSE\n");
    if(*t == FLOAT){
        printf("FLOAT");
        t++;
        return 1;
    }
    if(*t == DIGIT){
        printf("DIGIT ");
        t++;
        if(*t == FLOAT){
            printf("FLOAT ");
            t++;
        }
        return 1;
    }
    return 0;
    
}

int factorPostParse(Token_t *t){
    printf("FACTOR PARSE\n");
    if(*t == POW ){
        printf("POW ");
        t++;
        if(digitParse(t)){
            if(factorPostParse(t))
                return 1;
        }
        return 0;
    }
    
    
    return 1;
}

int factorParse(Token_t *t){
    printf("FACTOR\n");
    if(*t == DIGIT || *t == FLOAT){
        if(digitParse(t)){
            if(factorPostParse(t))
                return 1;
        }
    }
    else if(*t == SUBTRACT){
        if(digitParse(++t)){
            if(factorPostParse(t))
                return 1;
        }
    }
    else if(isTokenFunction(*t)){
        printToken(*t);
        if(*(++t) == LEFT_P)
        {
            if(arithParse(++t)){
                if(*(++t) == RIGHT_P){
                    printf("RIGHT_P");
                    t++;
                    return 1;
                }
            }
        }
    }
    else if(*t == LEFT_P){
        printf("LEFT_P ");
        if(arithParse(++t)){
            if(*(++t) == RIGHT_P){
                printf("RIGHT_P ");
                t++;
                return 1;
            }
        }
    }
    return 0;
    
}
int termPostParse(Token_t *t){
    printf("TERM POST\n");
    if(*t == MULTIPLY || *t == DIVIDE){
        printf(((*t == MULTIPLY) ? "MULTIPLY " : "DIVIDE "));
        if(factorParse(++t)){
            if(termPostParse(t))
                return 1;
        }
        return 0;
    }
    return 1;
}

int termParse(Token_t *t){
    printf("TERM\n");
    if(factorParse(t)){
        if(termPostParse(++t))
            return 1;
    }
    return 0;
}

int arithPostParse(Token_t *t){
    printf("ARITH POST\n");
    if(*t == SUBTRACT || *t == ADD){
        printf(((*t == SUBTRACT) ? "SUBTRACT " : "ADD "));
    
        if(termParse(++t)){
            if(arithPostParse(t))
                return 1;
        }
        return 0;
    }
    return 1;
}

int arithParse(Token_t *t){
    printf("ARITH\n");
    if(termParse(t)){
       if(arithPostParse(++t))
            return 1;
    }
    return 0;
}

int validate(Token_t *t){
    if(arithParse(t))
        return 1;
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