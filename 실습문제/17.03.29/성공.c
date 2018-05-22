#include "main.h"


void push(element item) ;
element pop() ;
element peek() ;
void del() ;
void printStack();
element evalPostfix(char *exp);
void postfix_case_bloack(char* postfix, int *p);
void postfix_case_operator_1(char* postfix, char symbol, int *p);
void postfix_case_operator_2(char* postfix, char symbol, int *p);
void postfix_case_default(char* postfix, char symbol, char* exp, int *p, int i);
char* infix_to_postfix(char* exp);
int syntaxsearch(char *exp);

void main(void) 
{ 		
	char buf[100 + 1];
	char *postfix;
	element result;


	printf("Enter the \"Infix notation\"\n");
	printf("[Enter]: ");
	scanf("%s", buf);
	fflush(stdin);


	if(syntaxsearch(buf) != -1)
	{
		postfix = infix_to_postfix(buf);
		result = evalPostfix(postfix);

		printf("\nInfix notation : %s", buf);
		printf("\nPostfix notation : %s", postfix);
		printf("\nResult value : %d\n", (int) result);
	}

} 

void push(element item) 
{	
	stackNode* temp=(stackNode *)malloc(sizeof(stackNode));
	temp->data = item; 
	temp->link = top;	
	top = temp; 
} 

element pop() 
{ 
	element item;
	stackNode* temp=top;
	
	if(top == NULL)
	{ 	 
		printf("\n\n Stack is empty !\n");	 
		return 0; 
	} 
	else 
	{ 
		item = temp->data;	
		top = temp->link;	 
		free(temp);				
		return item; 
	} 
} 

element peek() 
{	
	if(top == NULL) 
	{		 
		printf("\n\n Stack is empty !\n");	 
		return 0;	 
	} 
	else
	{ 
		return top->data; 
	} 
} 

void del() 
{  
	stackNode* temp; 
	
	if(top == NULL) 
	{		
		printf("\n\n Stack is empty !\n");			
	} 
	else 
	{ 
		temp = top;	
		top = top->link;	 
		free(temp); 
	} 
} 

void printStack()
{
	stackNode* p=top;
	
	printf("\n STACK [ ");
	
	while(p)
	{
		printf("%d ",p->data);
		p = p->link;
	}
	printf("] ");
}

// 후위 표기 연산
element evalPostfix(char *exp)
{
	double opr1, opr2;
	int value, i=0, count=0;
	int length = strlen(exp);
	char symbol;
	
	for(i=0; i<length; i++)
	{
		symbol = exp[i];
		
		if(symbol >= '0' && symbol <= '9')
		{
			while(exp[i + count] != ' ') // 숫자 구분을 위해 검사
			{
				count++;
			}
			value = atoi(&exp[i]);
			i+=count;
			count=0;
			push(value);
		}
		else
		{
			if(symbol != ' ') // 숫자 구분을 위한 ' ' 이 아닌 경우에만 
			{
				opr2 = pop();
				opr1 = pop();
				
				switch(symbol)
				{
				case '+' : push(opr1 + opr2); break;
				case '-' : push(opr1 - opr2); break;
				case '*' : push(opr1 * opr2); break;
				case '/' : push(opr1 / opr2); break;
				case '%' : push((int) opr1 % (int) opr2); break;
			}
			}
		}
	}
	return pop();
}

void postfix_case_bloack(char* postfix, int *p)
{
	char temp;

	while(1)
	{
		temp = (char)pop(); // 스택에서 하나를 꺼냄
		
		if((temp != '(') && (temp != '{') && (temp != '[')) // 열림 괄호가 아니라면
		{
			postfix[(*p)++] = temp; // 문자 배열에 저장
			postfix[(*p)++] = ' ';
		}
		else
		{
			break; 
		}
	}
}

void postfix_case_operator_1(char* postfix, char symbol, int *p)
{
	char temp;

	while(1)
	{
		if(top == NULL)
		{
			break;
		}
		temp = (char)pop(); // 스택에서 하나를 꺼냄
		
		if(temp == '+' || temp == '-' || temp == '*' || temp == '/' || temp == '%') // 연산 기호라면
		{
			postfix[(*p)++] = temp; // 문자 배열에 저장	
			postfix[(*p)++] = ' ';
		}
		else
		{
			push(temp); // 연산 기호가 아니면 다시 스택에 저장
			break;
		}
	}
	push(symbol); // 현재 연산 기호 저장
}

void postfix_case_operator_2(char* postfix, char symbol, int *p)
{
	char temp;

	while(1)
	{
		if(top == NULL)
		{
			break;
		}
		temp = (char)pop(); // 스택에서 하나를 꺼냄
		
		if(temp == '*' || temp == '/' || temp == '%') // 우선순위가 같은 연산 기호라면
		{
			postfix[(*p)++] = temp; // 문자 배열에 저장		
			postfix[(*p)++] = ' ';
		}
		else
		{
			push(temp); // 연산 기호가 아니면 다시 스택에 저장 
			break;
		}
	}
	push(symbol); // 현재 연산 기호 저장
}

void postfix_case_default(char* postfix, char symbol, char* exp, int *p, int i)
{
	postfix[(*p)++] = symbol; // 숫자를 문자 배열에 저장
	
	// 숫자 구분을 위해
	if(exp[i+1] == '+' || exp[i+1] == '-' || exp[i+1] == '*' || exp[i+1] == '/' || exp[i+1] == '%' ||
		exp[i+1] == ')' || exp[i+1] == '}' || exp[i+1] == ']' || exp[i+1] == '\0')
	{
		postfix[(*p)++] = ' '; // 공란 삽입
	}
}

// 중위 표기를 후위 표기로 변환
char* infix_to_postfix(char* exp)
{
	int i=0, p=0;
	int length = strlen(exp);
	char symbol;
	char* postfix = (char*)malloc(length * 2);
	
	for(i=0; i<length; i++)
	{
		symbol = exp[i];
		
		switch(symbol)
		{		
		case '(' :
		case '{' :
		case '[' :
			push(symbol); // 열림 괄호를 스택에 저장
			break;
			
		case ')':
		case '}':
		case ']':
			postfix_case_bloack(postfix, &p);
			break;
			
		case '+' :			
		case '-' :	
			postfix_case_operator_1(postfix, symbol, &p);
			break;
			
		case '*' :			
		case '/' :		
		case '%' :
			postfix_case_operator_2(postfix, symbol, &p);
			break;
			
		default:
			postfix_case_default(postfix, symbol, exp, &p, i);
			break;
		}
	}
	
	while(top) // 스택에 남아 있는 값을
	{
		postfix[p++] = (char)pop(); // 문자 배열에 저장
		postfix[p++] = ' ';
	}
	postfix[p] = '\0'; // 문자 배열 마지막에 널 값 저장
	return postfix;
}

// 문장 검사
int syntaxsearch(char *exp)
{
	int length = strlen(exp);
	int i=0;
	int ncount=0;
	char symbol, opr;
	
	for(i=0; i<length; i++)
	{
		symbol = exp[i];
		
		switch(symbol)
		{
		case '+' : 
		case '-' : 
		case '*' : 
		case '/' : 	
		case '%' : 
			opr = exp[i+1];
			if(opr == '+' || opr == '-' || opr == '*' || opr == '/' || opr == '%')
			{
				printf("Operator error");
				return -1;
			}
			break;
			
		case '(' :
		case '{' :
		case '[' :
			push(symbol);
			break;
			
		case ')':
			if(top == NULL)
			{
				printf("' ) ' Syntax error!!\n");
				return -1;
			}
			else
			{
				if(pop() != '(')
				{
					printf("' ( ' Syntax error!!\n");
					return -1;
				}
			}
			break;
			
		case '}':
			if(top == NULL)
			{
				printf("' } ' Syntax error!!\n");
				return -1;
			}
			else
			{
				if(pop() != '{')
				{
					printf("' { ' Syntax error!!\n");
					return -1;
				}
			}
			break;
			
		case ']':
			if(top == NULL)
			{
				printf("' ] ' Syntax error!!\n");
				return -1;
			}
			else
			{
				if(pop() != '[')
				{
					printf("' [ ' Syntax error!!\n");
					return -1;
				}
			}
			break;
			
		default:
			if(symbol < '0' || symbol > '9')
			{
				printf("All not number!!\n");
				return -1;
			}
			else
			{
				ncount++;
			}
			break;
		}
	}
	if(!ncount || ncount == 1)
	{
		printf("Nmber is empty or unavailable!!");
		return -1;
	}
	while(top)
	{
		opr = (char)pop();
		if(opr == '(' || opr == '{' || opr == '[' ||
		   opr == '+' || opr == '-' || opr == '*' || opr == '/' || opr == '%')
		{
			printf("` %c ' syntax error!!\n", opr);
			return -1;
		}		
	}	
	return 0;
}
