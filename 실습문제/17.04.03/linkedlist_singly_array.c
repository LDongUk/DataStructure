#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
	int id;
	char name[20];
	char address[100];
} element;

typedef struct node {
	element data;
	int next;
}node;

node list_array[MAX_SIZE];
int avail = 0, first = -1;


void add(int id, char name[], char address[]);
void initialize_node(int id, char name[], char address[]);
void insert(int first, int current);
void printList(int first);
int del(int id);
void delete_node(int pre, int current, int next);
int search_node(int id);

int main()
{

	char input = 's';
	char temp = 's';
	int id;
	char name[20];
	char address[100];


	while (input != 'q')
	{
		printf("i(삽입), d(삭제), f(탐색), r(전체 읽기), q(작업종료)를 선택하시오: ");
		scanf("%c", &input);
		getchar();

		switch (input)
		{
		case 'i': 
		{
			printf("삽입할 자료(학번, 이름, 주소)를 입력하시오 :");
			scanf("%d", &id);
			scanf("%s", name);

			gets(address);

			add(id, name, address);

			break;
		}
		case 'd':
		{
			printf("삭제할 자료의 학번을 입력하시오 :");
			scanf("%d", &id);
			getchar();
			
			if (del(id) == 1)
				printf("해당 자료는 없습니다.\n\n");
			break;
		}
		case 'f': 
		{
			printf("검색할 자료의 학번을 입력하시오 :");
			scanf("%d", &id);
			getchar();

			if (search_node(id) == 1)
				printf("해당 자료는 없습니다.\n\n");
			break;
		}
		case 'r': printList(first); break;
		case 'q': break;
		}


	}

	return 0;
}

void add(int id, char name[], char address[])
{
	int pre_first, current;
	int min;
	pre_first = first;
	initialize_node(id, name, address);
	current = avail - 1;
	if (pre_first == -1)
	{
		list_array[first].next = -1;
		first = 0;
	}
	else
	{
		insert(pre_first, current);
		
		if (list_array[first].data.id >= list_array[current].data.id)
			first = current;
	}
}

void initialize_node(int id, char name[], char address[])
{
	int i,current = first;
	int min;

	list_array[avail].data.id = id;
	strcpy(list_array[avail].data.name, name);
	strcpy(list_array[avail].data.address, address);
	list_array[avail].next = -1;
	avail++;

	
}



void insert(int first, int current)
{
	int pre_search = -1, search;

	search = first;

	while (1) {
		if (search == -1)
		{
			list_array[current].next = -1;
			list_array[pre_search].next = current;
			break;
		}

		if (list_array[search].data.id >= list_array[current].data.id)
		{

			list_array[pre_search].next = current;
			list_array[current].next = search;
			break;
		}

		else
		{
			pre_search = search;
			search = list_array[search].next;
		}
	}
}

void printList(int first)
{
	int current = first;

	printf("The list contains: \n");
	for (; current != -1; current = list_array[current].next)
		printf("%d, %s, %s\n", list_array[current].data.id, list_array[current].data.name, list_array[current].data.address);

	printf(" \n");
}

int del(int id)
{
	int pre = -1, current, next;
	current = first;

	for (; current != -1; pre = current, current = list_array[current].next)
	{
		if (list_array[current].data.id == id)
		{
			next = list_array[current].next;
			delete_node(pre, current, next);
			return 0;
		}
	}

	return 1;
}

void delete_node(int pre, int current, int next)
{
	if (pre == -1)
		first = next;
	else if (next == -1)
		list_array[pre].next = -1;
	else
		list_array[pre].next = next;

	printf("<%d, %s, %s>가 삭제되었습니다.\n\n", list_array[current].data.id, list_array[current].data.name, list_array[current].data.address);

}

int search_node(int id)
{
	int current = first;

	for (; current != -1; current = list_array[current].next)
	{
		if (list_array[current].data.id == id)
		{
			printf("검색하신 정보는 <%d, %s, %s>입니다.\n\n", list_array[current].data.id, list_array[current].data.name, list_array[current].data.address);
			return 0;
		}
	}

	return 1;
}