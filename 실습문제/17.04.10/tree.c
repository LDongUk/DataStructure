#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100 /* max size of expression */


typedef enum {lparen, rparen, or, and, not, eos, operand, True, False} logical;


typedef struct node *nodePointer;

typedef struct node {
	nodePointer leftChild;
	logical data;
	char var;
	short int value;
	nodePointer rightChild;
};


int stack[MAX_STACK_SIZE]; /* global stack */
char expr[MAX_EXPR_SIZE]; /* global input string (a postfix expression)*/
char postfix_expr[MAX_EXPR_SIZE];
nodePointer stack_tree[MAX_STACK_SIZE];
char variable[MAX_EXPR_SIZE];
//nodePointer start;

//lparen rparen or and not eos
static int isp[] = { 0, 19, 11, 12, 13, 0 };
static int icp[] = { 20, 19, 11, 12, 13, 0 };
int top = -1;
int top_eval = 0;
int top_post = -1;
int top_var = 0;

void push(int item);  int pop(); void stackFull(); logical stackEmpty();
logical getToken(char *tokenChar_ptr, int *tokenIndex_ptr); void postfix(void);
void printToken(logical token);
logical getTokenForTree(char *tokenChar_ptr, int *tokenIndex_ptr) ;
nodePointer structTree();
void preorder(nodePointer ptr);
void sort_variable_ascending();
void postOrderEval(nodePointer node);
void find_variable(nodePointer ptr, int bin[]);
void eval_all_possible(nodePointer root);

int main()
{
	nodePointer root;
	root = (struct node*)malloc(sizeof(struct node));
	
	printf("중위식 표현을 입력하시오 : ");
	scanf("%s", expr);
	printf("\n");
	printf("infix = %s\n\n", expr);

	postfix();
	printf("postfix = %s\n\n", postfix_expr);

	root = structTree();
	
	printf("preorder tree traversal : ");
	preorder(root);
	printf("\n\n");

	sort_variable_ascending();
	eval_all_possible(root);

	return 0;
}


void sort_variable_ascending()
{
	int i, j;
	char temp;

	for (i = 0; i < strlen(variable) - 1; i++)
	{
		for (j = i + 1; j < strlen(variable); j++)
		{
			if (variable[i] >= variable[j])
			{
				temp = variable[i];
				variable[i] = variable[j];
				variable[j] = temp;
			}
		}
	}

}

void eval_all_possible(nodePointer root)
{
	int *binary;
	int max_possible;
	int i, j, num;
	int top_bin;



	binary = (int*)malloc(sizeof(int) * strlen(variable));
	max_possible = pow(2.0, strlen(variable));

	
	for (i = 0; i < max_possible; i++)
	{
		top_bin = strlen(variable) - 1;
		num = i;

		while (1) // make binary number for compute all possible compositions
		{		  // from 0000 to 1111
			binary[top_bin] = num % 2;
			num = num / 2;
			top_bin--;

			if (top_bin == -1)
				break;
		}
		
		find_variable(root, binary); // initialize value of variable
		postOrderEval(root); // evaluate root


		printf("combination: ");
		for (j = 0; j < strlen(variable); j++)
		{
			printf("%c = %d ", variable[j], binary[j]);
		}

		printf(" result: %d\n", root->value);
	}

	free(binary);
}

void postOrderEval(nodePointer node)
{/* modified post order traversal to evaluate a propositional calculus tree */
	if (node) {
		postOrderEval(node->leftChild);
		postOrderEval(node->rightChild);
		switch (node->data) {
		
		case not: 
		{
			if (node->rightChild->value == 0)
				node->value = 1;
			else
				node->value = 0;
			break; 
		}
		case and: 
		{
			if (node->leftChild->value == 1 && node->rightChild->value == 1)
				node->value = 1;
			else
				node->value = 0;
			break; 
		}
		case or : 
		{
			if (node->leftChild->value == 0 && node->rightChild->value == 0)
				node->value = 0;
			else
				node->value = 1;
			break; 
		}


		} //end switch
	}
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

logical stackEmpty()
{
	fprintf(stderr, "Stack is empty, cannot delete element");
	exit(EXIT_FAILURE);
}



logical getToken(char *tokenChar_ptr, int *tokenIndex_ptr) 
{ /* get the next token, symbol is the character representation, 
  which is returned, the token is represented by its enumerated value, 
  which is returned in the function name */ 
	*tokenChar_ptr= expr[(*tokenIndex_ptr)++];
	switch (*tokenChar_ptr) 
	{ 
	case '(' : return lparen;
	case ')' : return rparen; 
	case '!' : return not;
	case '&' : return and;
	case '|' : return or;
	case '\0': return eos;
	default : return operand; 


		/* no error checking, default is operand */
	} 
}

logical getTokenForTree(char *tokenChar_ptr, int *tokenIndex_ptr) 
{ /* get the next token, symbol is the character representation, 
  which is returned, the token is represented by its enumerated value, 
  which is returned in the function name */ 
	*tokenChar_ptr= postfix_expr[(*tokenIndex_ptr)++];
	switch (*tokenChar_ptr) 
	{  
	case '!' : return not;
	case '&' : return and;
	case '|' : return or;
	case '\0': return eos;
	default : return operand;


		/* no error checking, default is operand */
	} 
}


void postfix(void)
{/* output the postfix of the expression.
 The expression string, the stack, and top are global */
	char tokenChar;
	logical tokenType, to;
	int tokenIndex = 0;
	char t;
	//nodePointer x;
	top = 0;
	stack[0] = eos;
	while(1) {
		tokenType= getToken(&tokenChar, &tokenIndex);
		if (tokenType == eos) break;
		if (tokenType == operand)
		{
			postfix_expr[top_eval] = tokenChar; 
			top_eval++;
			//printf("%c", tokenChar);
		}
		else if (tokenType == rparen) {
			/* unstack tokens until left parenthesis */
			while (stack[top] != lparen)
			{
				to = (logical) pop();

				switch (to)
				{
				case lparen: t = '('; break;
				case rparen: t = ')'; break;
				case not: t = '!'; break;
				case or: t = '|'; break;
				case and: t = '&'; break;
				}
				postfix_expr[top_eval] = t;
				top_eval++;
				//printToken(to);
			}
			
			pop(); /* discard the left parenthesis */
		} else {
			/* remove and print symbols whose isp is greater than or equal to the current token's icp */
			while (isp[stack[top]] >= icp[tokenType])
			{
				to =(logical) pop();
				switch (to)
				{
				case lparen: t = '('; break;
				case rparen: t = ')'; break;
				case not: t = '!'; break;
				case or: t = '|'; break;
				case and: t = '&'; break;
				}

				postfix_expr[top_eval] = t; top_eval++;
				//printToken(to);
			}
			push(tokenType);
			
		}
	}
	while ((tokenType = (logical) pop()) != eos)
	{
		switch (tokenType)
		{
		case lparen: t = '('; break;
		case rparen: t = ')'; break;
		case not: t = '!'; break;
		case or: t = '|'; break;
		case and: t = '&'; break;
		
		}

		postfix_expr[top_eval] = t; top_eval++;
		//printToken(tokenType);
	}
}

//lparen, rparen, plus, minus, times, divide,mod, eos, operand
void printToken(logical token)
{
	char operation = '\0';
	switch (token)

	{
	case lparen:
	case rparen: operation = pop(); break;
	case not: operation = '!'; break;
	case or: operation = '|'; break;
	case and: operation = '&'; break;
	}

	printf("%c", operation);
}

nodePointer structTree()
{
	char token_char;
	int token_index = 0;
	int i, k;
	logical token;
	nodePointer x;
	nodePointer pre;

	
	
	
	// saving leaves
	while(1)
	{
		token= getTokenForTree(&token_char, &token_index);

		if(token == operand)
		{
			x = (struct node*)malloc(sizeof(struct node));
			x->data = token;
			x->leftChild = x->rightChild = NULL;
			x->var = token_char;
			x->value = 0;

			stack_tree[++top_post] = x;
		}

		else if(token == not)
		{
			x = (struct node*)malloc(sizeof(struct node));
			pre = (struct node*)malloc(sizeof(struct node));
			x->data = token;
			x->leftChild = NULL;
			pre = stack_tree[top_post];
			x->rightChild = pre;
			
			stack_tree[top_post] = x;

		}

		else if(token == or || token == and)
		{
			x = (struct node*)malloc(sizeof(struct node));
			x->data = token;
			
			stack_tree[++top_post] = x;
		}


		else if(token == eos)
			break;

	}


	// struct tree
	for (k = 0; stack_tree[k] != NULL; k++)
	{
		if (stack_tree[k]->data == or || stack_tree[k]->data == and)
		{
			x = (struct node*)malloc(sizeof(struct node));
			x->leftChild = x->rightChild = NULL;
			x->data = stack_tree[k]->data;

			for (i = k - 1;; i--)
			{
				if (stack_tree[i] != NULL)
				{

					pre = stack_tree[i];

					if (x->rightChild == NULL && x->leftChild == NULL)
					{
						x->rightChild = pre;
						stack_tree[i] = NULL;
					}

					else if (x->rightChild != NULL && x->leftChild == NULL)
					{
						x->leftChild = pre;
						stack_tree[k] = x;
						stack_tree[i] = NULL;
						break;
					}

				}
			}//end for

		} //end if
	}//end for

	return stack_tree[k - 1];

}

void preorder(nodePointer ptr)
{
	char data;
	int i, count;
	/* preorder tree traversal */
	if (ptr) {

		switch (ptr->data)
		{
		case not: data = '!'; break;
		case and: data = '&'; break;
		case or : data = '|'; break;
		default: //store mutually distinct variable
		{
			data = ptr->var;
			
			count = 0;
			for (i = 0; i < top_var + 1; i++)
			{
				if (data == variable[i])
					break;

				else
					count++;
			}

			if (count == top_var + 1)
			{
				variable[top_var] = data;
				top_var++;
			}

			break;
		} //end default


		} //end switch

		printf("%c ", data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);

	}
}

void find_variable(nodePointer ptr, int bin[])
{
	char data;
	int i, count;
	/* preorder tree traversal */
	if (ptr) {

		switch (ptr->data)
		{
		case not:
		case and:
		case or : break;
		default: //find variable
		{
			for (i = 0; i < strlen(variable); i++)
			{
				if (variable[i] == ptr->var)
				{
					ptr->value = bin[i];
					break;
				}
			}


			break;
		} //end default


		} //end switch

		find_variable(ptr->leftChild, bin);
		find_variable(ptr->rightChild, bin);

	}
}