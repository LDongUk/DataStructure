#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100 /* max size of expression */

typedef enum { lparen, rparen, plus, minus, times, divide,
mod, eos, operand } token_type;

int stack[MAX_STACK_SIZE]; /* global stack */
char expr[MAX_EXPR_SIZE]; /* global input string (a postfix expression)*/
char expr_eval[MAX_EXPR_SIZE];


static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
int top = -1;
int top_eval = 0;

void push(int item);  int pop(); void stackFull(); token_type stackEmpty();
int eval(void); token_type getToken(char *tokenChar_ptr, int *tokenIndex_ptr); void postfix(void);
void printToken(token_type token);
token_type getToken2(char *tokenChar_ptr, int *tokenIndex_ptr);

int main()
{

	printf("중위식 표현을 입력하시오\n");
	
	scanf("%s", expr);

	printf("후위식 표현 : ");
	postfix();

	printf("계산 값 : \n\n%d\n", eval());

	return 0;
}



void push(int item)
{

	if (top >= MAX_STACK_SIZE - 1)
		stackFull();

	stack[++top] = item;

}

int pop()
{
	if (top == -1)
		return stackEmpty();

	return stack[top--];
}


void stackFull()
{
	fprintf(stderr, "Stack is full, cannot add element");
	exit(EXIT_FAILURE);
}

token_type stackEmpty()
{
	fprintf(stderr, "Stack is empty, cannot delete element");
	exit(EXIT_FAILURE);
}

int eval(void)
{
	/* evaluate a postfix expression, expr, maintained as a global variable. '\0' is the end of the expression. The stack 

and top of the stack are global variables. getToken is used to return the token type and the character symbol. Operands are 

assumed to be single character digits */
	token_type tokenType;
	char tokenChar;
	int opdl, opd2;
	int tokenIndex = 0; /* counter for the expression string */
	int top = -1;
	while (1) {
		tokenType = getToken2(&tokenChar, &tokenIndex);
		if (tokenType == eos) break;
		if (tokenType == operand) push(tokenChar - '0');
		else {
			/* pop two operands, perform operation, and
			push result to the stack */



			opd2 = pop();
			opdl = pop();

			switch(tokenType) {
			case plus: push(opdl+opd2); break;
			case minus: push(opdl-opd2); break;
			case times: push(opdl*opd2); break;
			case divide: push(opdl/opd2); break;
			case mod: push(opdl%opd2);
			}
		}
	}
	return pop();
}

token_type getToken(char *tokenChar_ptr, int *tokenIndex_ptr) 
{ /* get the next token, symbol is the character representation, 
  which is returned, the token is represented by its enumerated value, 
  which is returned in the function name */ 
	*tokenChar_ptr= expr[(*tokenIndex_ptr)++];
	switch (*tokenChar_ptr) 
	{ 
	case '(' : return lparen;
	case ')' : return rparen; 
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times; 
	case '%' : return mod; 
	case '\0' : return eos; 
	default : return operand; 
		/* no error checking, default is operand */
	} 
}

token_type getToken2(char *tokenChar_ptr, int *tokenIndex_ptr)
{ /* get the next token, symbol is the character representation,
  which is returned, the token is represented by its enumerated value,
  which is returned in the function name */
	*tokenChar_ptr = expr_eval[(*tokenIndex_ptr)++];
	switch (*tokenChar_ptr)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
		/* no error checking, default is operand */
	}
}

void postfix(void)
{/* output the postfix of the expression.
 The expression string, the stack, and top are global */
	char tokenChar;
	token_type tokenType, to;
	int tokenIndex = 0;
	char t;
	top = 0;
	stack[0] = eos;
	while(1) {
		tokenType= getToken(&tokenChar, &tokenIndex);
		if (tokenType == eos) break;
		if (tokenType == operand)
		{
			expr_eval[top_eval] = tokenChar; top_eval++;
			printf("%c", tokenChar);
		}
		else if (tokenType == rparen) {
			/* unstack tokens until left parenthesis */
			while (stack[top] != lparen)
			{
				to = pop();

				switch (to)
				{
				case lparen: t = '('; break;
				case rparen: t = ')'; break;
				case plus: t = '+'; break;
				case minus: t = '-'; break;
				case divide: t = '/'; break;
				case times: t = '*'; break;
				case mod: t = '%'; break;
				}
				expr_eval[top_eval] = t;
				top_eval++;
				printToken(to);
			}
			pop(); /* discard the left parenthesis */
		} else {
			/* remove and print symbols whose isp is greater than or equal to the current token's icp */
			while (isp[stack[top]] >= icp[tokenType])
			{
				to = pop();
				switch (to)
				{
				case lparen: t = '('; break;
				case rparen: t = ')'; break;
				case plus: t = '+'; break;
				case minus: t = '-'; break;
				case divide: t = '/'; break;
				case times: t = '*'; break;
				case mod: t = '%'; break;
				}

				expr_eval[top_eval] = t; top_eval++;
				printToken(to);
			}
			push(tokenType);
			
		}
	}
	while ((tokenType = pop()) != eos)
	{
		switch (tokenType)
		{
		case lparen: t = '('; break;
		case rparen: t = ')'; break;
		case plus: t = '+'; break;
		case minus: t = '-'; break;
		case divide: t = '/'; break;
		case times: t = '*'; break;
		case mod: t = '%'; break;
		}

		expr_eval[top_eval] = t; top_eval++;
		printToken(tokenType);
	}
	printf("\n");
}

//lparen, rparen, plus, minus, times, divide,mod, eos, operand
void printToken(token_type token)
{
	char operation = '\0';
	switch (token)

	{
	case lparen:
	case rparen: operation = pop(); break;
	case plus: operation = '+'; break;
	case minus: operation = '-'; break;
	case times: operation = '*'; break;
	case divide: operation = '/'; break;
	case mod: operation = '%'; break;
	}

	printf("%c", operation);
}