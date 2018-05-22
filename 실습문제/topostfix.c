#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// isp and icp arrays for precedence
// (, ), +, -, *, /, %, eos ����
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
	printf("�־��� infix expression�� postfix expression���� ��ȯ�Ͽ� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.\n");
	printf("����ϴ� �����ڴ� + , -, / , *�̸� left parenthesis�� right parenthesis�� ����Ѵ�.\n");

	stack[0] = ' '; top = 1; // stack[0]�� �켱������ ���� ���� char�� �ְ� top�� 1�� �÷� �����Ѵ�.

	// �����͸� ���� fopen�� ������ ���� file������ 2���� ����. ������ ������ exit
	fp1 = fopen("HW0503_02.txt", "r");
	fp2 = fopen("OuputOfHW0503.txt", "w");
	if (fp1 == NULL || fp2 == NULL)
	{
		printf("fopen�� ���������� �̷������ �ʾҽ��ϴ�.\n");
		exit(1);
	}

	toPostfix(fp1, fp2, stack, &top); // infix�� postfix�� �����ϴ� �Լ�
	printf("\n");// �ֿܼ��� '����Ͻ÷���~' �� ������ �׳� �� �� ���� ���� ����

	fclose(fp1); fclose(fp2);
	return 0;
}

// infix�� postfix�� �����ϴ� �Լ�
// �Ű������� �����͸� �а� ����� ���� file ������ 2���� �����ڸ� ���� ���� �׸��� top�� �޴´�.
void toPostfix(FILE *fp1, FILE *fp2, char stack[], int *top)
{
	char indicator; // ���������Ϳ��� fgetc�� �Ͽ� �Է¹��� char ����
	precedence token; // �켱���� ����

	do
	{
		indicator = fgetc(fp1);

		if ((int)indicator == -1) // ���̻� ���� ���� ���� ��� ���ÿ� �ִ� �����ڸ� ��� pop�ϰ� ������
		{
			while (*top != 1)
				fprintf(fp2, "%c", pop(stack, top));
			break;
		}

		// ���� �߰��� ���Ⱑ �ִٸ� continue�� �����ϰ� ����
		if (indicator == ' ')
			continue;

		token = checkPrecedence(indicator); // �Է¹��� �������� �켱������ ���

		if (token == operand)
			fprintf(fp2, "%c", indicator); // �ǿ������� ��� �ٷ� ���
		else if (token == lparen) // ( �� ��� recursive�� �ȿ��� �ٽ� ����
		{
			push(stack, top, indicator);
			toPostfix(fp1, fp2, stack, top);
		}
		else if (token == rparen) // ) �� ��� stack���� ) ���� pop�ϰ� recursive�� ����
		{
			while (stack[*top - 1] != '(')
				fprintf(fp2, "%c", pop(stack, top));
			pop(stack, top);
			return;
		}
		else
		{
			// ������ ���ÿ� �ֱ� & �켱���� ��
			if (isp[checkPrecedence(stack[*top - 1])] >= icp[token])
				fprintf(fp2, "%c", pop(stack, top));
			push(stack, top, indicator);
		}

	} while (1);
} // End toPostfix

// �������� �켱������ Ȯ���ϴ� �Լ�
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

// ���� push �Լ�
void push(char stack[], int *top, char indicator)
{
	if (*top >= 21)
		printf("������ ������ �ȵ˴ϴ�.\n");
	else
		stack[(*top)++] = indicator;
}

// ���� pop �Լ�
char pop(char stack[], int *top)
{
	if (*top == 1)
		return -1;
	else
		return stack[--(*top)];
}