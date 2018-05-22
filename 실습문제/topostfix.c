#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// isp and icp arrays for precedence
// (, ), +, -, *, /, %, eos 순서
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;

void toPostfix(FILE *fp1, FILE *fp2, char stack[], int *top);
void push(char stack[], int *top, char indicator);
char pop(char stack[], int *top);
precedence checkPrecedence(char indicator);

int main()
{
	FILE *fp1 = NULL, *fp2 = NULL;
	char stack[20];
	int top = 0;

	printf("<HW0503>\n");
	printf("주어진 infix expression을 postfix expression으로 변환하여 출력하는 프로그램을 작성하시오.\n");
	printf("사용하는 연산자는 + , -, / , *이며 left parenthesis와 right parenthesis를 고려한다.\n");

	stack[0] = ' '; top = 1; // stack[0]에 우선순위가 가장 낮은 char를 넣고 top을 1로 올려 시작한다.

	// 데이터를 읽을 fopen과 내용을 넣을 file포인터 2개를 설정. 오류가 있으면 exit
	fp1 = fopen("HW0503_02.txt", "r");
	fp2 = fopen("OuputOfHW0503.txt", "w");
	if (fp1 == NULL || fp2 == NULL)
	{
		printf("fopen이 정상적으로 이루어지지 않았습니다.\n");
		exit(1);
	}

	toPostfix(fp1, fp2, stack, &top); // infix를 postfix로 수정하는 함수
	printf("\n");// 콘솔에서 '계속하시려면~' 이 문구를 그냥 한 줄 띄우기 위해 설정

	fclose(fp1); fclose(fp2);
	return 0;
}

// infix를 postfix로 수정하는 함수
// 매개변수에 데이터를 읽고 결과를 적을 file 포인터 2개와 연산자를 넣을 스택 그리고 top을 받는다.
void toPostfix(FILE *fp1, FILE *fp2, char stack[], int *top)
{
	char indicator; // 파일포인터에서 fgetc를 하여 입력받을 char 변수
	precedence token; // 우선순위 변수

	do
	{
		indicator = fgetc(fp1);

		if ((int)indicator == -1) // 더이상 읽을 것이 없을 경우 스택에 있는 연산자를 모두 pop하고 끝낸다
		{
			while (*top != 1)
				fprintf(fp2, "%c", pop(stack, top));
			break;
		}

		// 만약 중간에 띄어쓰기가 있다면 continue로 무시하고 진행
		if (indicator == ' ')
			continue;

		token = checkPrecedence(indicator); // 입력받은 연산자의 우선순위를 계산

		if (token == operand)
			fprintf(fp2, "%c", indicator); // 피연산자일 경우 바로 출력
		else if (token == lparen) // ( 일 경우 recursive로 안에를 다시 시작
		{
			push(stack, top, indicator);
			toPostfix(fp1, fp2, stack, top);
		}
		else if (token == rparen) // ) 일 경우 stack에서 ) 까지 pop하고 recursive를 종료
		{
			while (stack[*top - 1] != '(')
				fprintf(fp2, "%c", pop(stack, top));
			pop(stack, top);
			return;
		}
		else
		{
			// 연산자 스택에 넣기 & 우선순위 비교
			if (isp[checkPrecedence(stack[*top - 1])] >= icp[token])
				fprintf(fp2, "%c", pop(stack, top));
			push(stack, top, indicator);
		}

	} while (1);
} // End toPostfix

// 연산자의 우선순위를 확인하는 함수
precedence checkPrecedence(char indicator)
{
	switch (indicator)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case ' ': return eos;
	default: return operand;
	}
} // End checkPrecedence

// 스택 push 함수
void push(char stack[], int *top, char indicator)
{
	if (*top >= 21)
		printf("스택이 꽉차서 안됩니다.\n");
	else
		stack[(*top)++] = indicator;
}

// 스택 pop 함수
char pop(char stack[], int *top)
{
	if (*top == 1)
		return -1;
	else
		return stack[--(*top)];
}