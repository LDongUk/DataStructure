#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
	int id;
	char name[20];
	char address[100];
} element;

typedef struct node{
	element data;
	int next;
}node;

node list_array[MAX_SIZE];
int avail = 0, first = -1;


void add(int id, char name[], char address[]);
void initialize_node(int id, char name[], char address[]);
int find_prev_node(int id);
void insert(int first, int prev, int current);
void printList(int first);

int main()
{

	char input = 's';
	char temp = 's';
	int id;
	char name[20];
	char address[100];

	
	while(input != 'q')
	{
		printf("i(삽입), d(삭제), f(탐색), r(전체 읽기), q(작업종료)를 선택하시오: ");
		scanf("%c", &input);
		fflush(stdin);

		switch(input)
		{
		case 'i' : {
			printf("삽입할 자료(학번, 이름, 주소)를 입력하시오 :");
			scanf("%d", &id);
			scanf("%s", name);
			
			gets(address);

			add(id, name, address);

			break;
				   }
		case 'd' : break;
		case 'f' : break;
		case 'r' : printList(first); break;
		
		}

		printf("%d %d %d //%d\n", list_array[0].next,list_array[1].next,list_array[2].next, first);

		
	}		

	return 0;
}

void add(int id, char name[], char address[])
{
	int prev, current, min, min_index, i;
	initialize_node(id, name, address);
	prev = find_prev_node(first - 1, avail - 1);
	current = avail - 1;
	

	
	insert(first, prev, current);
}

void initialize_node(int id, char name[], char address[])
{
	int i, min, min_index;

	list_array[avail].data.id = id;
	strcpy(list_array[avail].data.name, name);
	strcpy(list_array[avail].data.address, address);
	
	avail++;

	if(avail == 1) first = 0;
	else{
		for(i = 0; i < avail; i++)
		{
			min = list_array[0].data.id;
			if(min >= list_array[i].data.id)
			{
				min = list_array[i].data.id;
				min_index = i;
			}
		}
		
		first = min_index;
	}
}

int find_prev_node(int first, int current)
{
	int prev, search;
	prev = -1;
	search = first;
	while (1) {
		if (search == -1) break;
		if (list_array[search].data.id >= list_array[current].data.id) {
			list_array[search].next = current;
			list_array[current].next = search;
			break;
		}
		prev = search;
		search = list_array[search].next;
	}
	return prev;
}


void insert(int first, int prev, int current)
{
	if (first != -1) {
		if (prev == -1) { 
			list_array[current].next = -1;
		}
		else { 
			list_array[current].next = list_array[prev].next;
			list_array[prev].next = current;
		}
	}
}

void printList(int first)
{

	printf("The list contains: \n");
	for(;first != -1; first = list_array[first].next)
		printf("%d, %s, %s\n", list_array[first].data.id, list_array[first].data.name, list_array[first].data.address);

	printf(" \n");
}












// 동적할당 singly

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct node *nodePointer;
//typedef struct node
//{
//	int id;
//	char name[20];
//	char address[100];
//	nodePointer next;
//};
//nodePointer first = NULL;
//
//
//nodePointer allocate_node();
//void initialize_node(nodePointer current, int id, char name[], char address[]);
//void add(int id, char name[], char address[]);
//nodePointer find_prev_node(nodePointer first, nodePointer current);
//void insert(nodePointer *first, nodePointer prev, nodePointer current);
//void delete_node(nodePointer *first, nodePointer prev, nodePointer current);
//void printList(nodePointer current);
//int search_node(nodePointer current, int id);
//int del(int id, nodePointer current);
//
//int main()
//{
//	char input = 's';
//	char temp = 's';
//	int id;
//	char name[20];
//	char address[100];
//
//	while(input != 'q')
//	{
//		printf("i(삽입), d(삭제), f(탐색), r(전체 읽기), q(작업종료)를 선택하시오: ");
//		scanf("%c", &input);
//		fflush(stdin);
//		
//		switch(input)
//		{
//		case 'i' : {
//			printf("삽입할 자료(학번, 이름, 주소)를 입력하시오 :");
//			scanf("%d", &id);
//			scanf("%s", name);
//			
//			gets(address);
//			fflush(stdin);
//			add(id, name, address);
//
//			break;
//				   }
//		
//		case 'd' : {
//			printf("삭제할 자료의 학번을 입력하시오:");
//			scanf("%d", &id);
//			fflush(stdin);
//			
//			if(del(id, first) == 1)
//				printf("해당 학번은 업는 자료입니다.\n\n");
//			break;
//				   }
//		
//		case 'f' : {
//			printf("탐색할 자료의 학번을 입력하시오:");
//			scanf("%d", &id);
//			fflush(stdin);
//			if(search_node(first, id) == 1)
//				printf("해당 학번은 업는 자료입니다.\n\n");
//			break;
//				   }
//		
//		case 'r' : printList(first);break;
//		
//		case 'q' : break;
//		
//		}
//	}
//
//	return 0;
//}
//
//nodePointer allocate_node()
//{
//	nodePointer ptr;
//	//MALLOC(ptr, sizeof(node));
//	ptr = (struct node *) malloc(sizeof(struct node));
//	return ptr;
//}
//
//void initialize_node(nodePointer current, int id, char name[], char address[])
//{
//	current->id = id;
//	strcpy(current->name, name);
//	strcpy(current->address, address);
//	current->next = NULL;
//}
//
//
//void add(int id, char name[], char address[])
//{
//	nodePointer prev, current;
//	current = allocate_node();
//	initialize_node(current, id, name, address);
//	prev = find_prev_node(first, current);
//	insert(&first, prev, current);
//}
//
//nodePointer find_prev_node(nodePointer first, nodePointer current)
//{
//	nodePointer prev, search;
//	prev = NULL;
//	search = first;
//	while (1) {
//		if (search == NULL) break;
//		if (search->id >= current->id) break;
//		prev = search;
//		search = search->next;
//	}
//	return prev;
//}
//
//void insert(nodePointer *first, nodePointer prev, nodePointer current)
//{
//	if (*first) {
//		if (prev == NULL) { 
//			current->next = *first;
//			*first = current; 
//		}
//		else { 
//			current->next = prev->next;
//			prev->next = current;
//		}
//	}
//	
//	else {
//		*first = current; 
//	}
//}
//
//void delete_node(nodePointer *first, nodePointer prev, nodePointer current)
//{
//	if (prev) prev->next = current->next;
//	else *first = current->next;
//
//	printf("<학번, 이름, 주소> = <%d, %s, %s>이 삭제되었습니다.\n\n", current->id, current->name, current->address);
//	free(current);
//}
//
//void printList(nodePointer current)
//{
//	printf("The list contains: \n");
//	for (; current; current = current->next)
//		printf("<%d, %s, %s>\n", current->id, current->name, current->address);
//	printf(" \n");
//}
//
//int search_node(nodePointer current, int id)
//{
//	for (; current; current = current->next)
//	{
//		if(current->id == id)
//		{
//			printf("<%d, %s, %s>\n\n", current->id, current->name, current->address);
//			return 0;
//		}
//	}
//
//	return 1;
//
//}
//
//int del(int id, nodePointer current)
//{
//	nodePointer prev;
//	
//	for (; current; current = current->next)
//	{
//		if(current->id == id)
//		{
//			prev = find_prev_node(first, current);
//			delete_node(&first, prev, current);
//			return 0;
//		}
//	}
//	return 1;
//}