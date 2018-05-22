#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

typedef struct{
	int id;
	char name[20];
	char adr[30];

}element;

element stack[MAX_SIZE];
element queue[MAX_SIZE];
element circular_queue[MAX_SIZE];

int top = -1;
int f = -1;
int r = -1;
int fc = 0;
int rc = 0;

void push(element item);element pop();void stackFull();element stackEmpty();

void addq(element item);void queueFull();element deleteq();element queueEmpty();

void addcq(element item);element deletecq();

int main()
{
	
	char plag;
	int i;

	element temp;
	
	
	printf("==============1������===============\n");
	// ���� �Ի�
	plag = 'Y';
	printf("������ �Է��Ͻÿ�.\n");
	while(plag == 'Y')
	{
		printf("id, �̸�, �ּ� ������ �Է��Ͻÿ�\n");
		printf("id = ");
		scanf("%d", &temp.id);

		printf("�̸� = ");
		scanf("%s", temp.name);

		printf("�ּ� = ");
		scanf("%s", temp.adr);

		fflush(stdin);

		push(temp);
		addq(temp);
		addcq(temp);

		printf("�� �Է��Ͻðڽ��ϱ�? Y/N   : ");
		scanf("%c", &plag);

	}
	
	printf("===Stack===\n");

	for(i = 0; i < top + 1; i++)
		printf("%d  %s  %s\n", stack[i].id, stack[i].name, stack[i].adr);

	printf("\n\n");
	printf("===Queue===\n");

	for(i = f + 1; i < r + 1; i++)
		printf("%d  %s  %s\n", queue[i].id, queue[i].name, queue[i].adr);

	printf("\n\n");
	printf("===Circular Queue===\n");
	
	if(fc < rc)
	{
		for(i = fc + 1; i < rc + 1; i++)
			printf("%d  %s  %s\n", circular_queue[i].id, circular_queue[i].name, circular_queue[i].adr);
	}

	else if(fc > rc)
	{
		for(i = fc + 1; i < MAX_SIZE; i++)
			printf("%d  %s  %s\n", circular_queue[i].id, circular_queue[i].name, circular_queue[i].adr);
	
		for(i = 0; i < rc + 1; i++)
			printf("%d  %s  %s\n", circular_queue[i].id, circular_queue[i].name, circular_queue[i].adr);
	
	}

	printf("\n\n");
	printf("==============2������===============\n");
	printf("3�� ���\n");

	//3�� ���
	printf("===Stack===\n");
	pop();pop();pop();

	printf("\n\n");
	printf("===Queue===\n");
	deleteq();deleteq();deleteq();
	
	printf("\n\n");
	printf("===Circular Queue===\n");
	deletecq();deletecq();deletecq();

	printf("\n\n");
	printf("==============3������===============\n");
	//�� ���� �Ի�
	plag = 'Y';
	printf("�� ������ �Է��Ͻÿ�.\n");
	while(plag == 'Y')
	{
		printf("id, �̸�, �ּ� ������ �Է��Ͻÿ�\n");
		printf("id = ");
		scanf("%d", &temp.id);

		printf("�̸� = ");
		scanf("%s", temp.name);

		printf("�ּ� = ");
		scanf("%s", temp.adr);

		fflush(stdin);

		push(temp);
		addq(temp);
		addcq(temp);

		printf("�� �Է��Ͻðڽ��ϱ�? Y/N   : ");
		scanf("%c", &plag);
	}

	printf("\n\n");
	printf("ȸ�翡 �����ִ� ������ �Ի��\n");

	printf("===Stack===\n");

	for(i = 0; i < top + 1; i++)
		printf("%d  %s  %s\n", stack[i].id, stack[i].name, stack[i].adr);

	printf("\n\n");
	printf("===Queue===\n");

	for(i = f + 1; i < r + 1; i++)
		printf("%d  %s  %s\n", queue[i].id, queue[i].name, queue[i].adr);

	printf("\n\n");
	printf("===Circular Queue===\n");
	
	if(fc < rc)
	{
		for(i = fc + 1; i < rc + 1; i++)
			printf("%d  %s  %s\n", circular_queue[i].id, circular_queue[i].name, circular_queue[i].adr);
	}

	else if(fc > rc)
	{
		for(i = fc + 1; i < MAX_SIZE; i++)
			printf("%d  %s  %s\n", circular_queue[i].id, circular_queue[i].name, circular_queue[i].adr);
	
		for(i = 0; i < rc + 1; i++)
			printf("%d  %s  %s\n", circular_queue[i].id, circular_queue[i].name, circular_queue[i].adr);
	
	}
	printf("\n\n");
	printf("==============4������===============\n");
	//6�� ���
	printf("===Stack===\n");
	pop();pop();pop();pop();pop();pop();

	printf("\n\n");
	printf("===Queue===\n");
	deleteq();deleteq();deleteq();deleteq();deleteq();deleteq();
	
	printf("\n\n");
	printf("===Circular Queue===\n");
	deletecq();deletecq();deletecq();deletecq();deletecq();deletecq();


	//�����ִ� ������
	printf("\n\n");
	printf("==============5������===============\n");
	printf("ȸ�翡 �����ִ� ������ �Ի��\n");

	printf("===Stack===\n");

	for(i = 0; i < top + 1; i++)
		printf("%d  %s  %s\n", stack[i].id, stack[i].name, stack[i].adr);

	printf("\n\n");
	printf("===Queue===\n");

	for(i = f + 1; i < r + 1; i++)
		printf("%d  %s  %s\n", queue[i].id, queue[i].name, queue[i].adr);

	printf("\n\n");
	printf("===Circular Queue===\n");
	
	if(fc < rc)
	{
		for(i = fc + 1; i < rc + 1; i++)
			printf("%d  %s  %s\n", circular_queue[i].id, circular_queue[i].name, circular_queue[i].adr);
	}

	else if(fc > rc)
	{
		for(i = fc + 1; i < MAX_SIZE; i++)
			printf("%d  %s  %s\n", circular_queue[i].id, circular_queue[i].name, circular_queue[i].adr);
	
		for(i = 0; i < rc + 1; i++)
			printf("%d  %s  %s\n", circular_queue[i].id, circular_queue[i].name, circular_queue[i].adr);
	
	}
	


	return 0;
}


void push(element item)
{

	if(top >= MAX_SIZE -1)
		stackFull();

	stack[++top] = item;

}

element pop()
{
	if(top == -1)
		return stackEmpty();

	printf("%d  %s  %s\n", stack[top].id, stack[top].name, stack[top].adr);

	return stack[top--];
}


void stackFull()
{
	fprintf(stderr, "Stack is full, cannot add element");
	exit(EXIT_FAILURE);
}element stackEmpty()
{
	fprintf(stderr, "Stack is empty, cannot delete element");
	exit(EXIT_FAILURE);
}


void addq(element item)
{
	/* add an item to the queue */
	if (r == MAX_SIZE-1)
		queueFull();
	queue[++r] = item;
}

void queueFull()
{
	fprintf(stderr, "Queue is full, cannot add element");
	exit(EXIT_FAILURE);

}


element deleteq()
{
	int i;
	
	/* remove element at the front of the queue */
	if (f == r)
		return queueEmpty(); /*return an error key*/
	
	printf("%d  %s  %s\n", queue[0].id, queue[0].name, queue[0].adr);

	for(i = 0; i < r; i++)
		queue[i] = queue[i + 1];


	return queue[r--];
}

element queueEmpty()
{
	fprintf(stderr, "Queue is empty, cannot delete element");
	exit(EXIT_FAILURE);
}

void addcq(element item)
{
	/* add an item to the queue */
	rc = (rc+1) % MAX_SIZE;
	if (fc == rc)
		queueFull(); /*print error and exit*/
	circular_queue[rc] = item;
}element deletecq()
{
	/* remove front element from the queue */
	element item;
	if (fc == rc)
		return queueEmpty(); /* return an error key*/

	fc = (fc+1) % MAX_SIZE;

	printf("%d  %s  %s\n", circular_queue[fc].id, circular_queue[fc].name, circular_queue[fc].adr);
	return circular_queue[fc];
}