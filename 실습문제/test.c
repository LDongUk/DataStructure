#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nodePointer;
typedef struct
{
	int id;
	char name[20];
	char address[100];
}element;
typedef struct node
{
	element data;
	nodePointer rightChild;
	nodePointer leftChild;
}node;
nodePointer first = NULL;


nodePointer allocate_node();
void initialize_node(nodePointer current, int id, char name[], char address[]);
void add(int id, char name[], char address[]);
void insertBST(node **rootPtr, node x);
int searchParentToInsert(node *root, int key, node **parentPtr);
void delete_node(nodePointer *first, nodePointer prev, nodePointer current);
void printList(nodePointer current);
int search_node(nodePointer current, int id);
int del(int id, nodePointer current);

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
		fflush(stdin);

		switch (input)
		{
		case 'i': {
			printf("삽입할 자료(학번, 이름, 주소)를 입력하시오 :");
			scanf("%d", &id);
			scanf("%s", name);

			gets(address);
			fflush(stdin);
			add(id, name, address);

			break;
		}

		case 'd': {
			printf("삭제할 자료의 학번을 입력하시오:");
			scanf("%d", &id);
			fflush(stdin);

			if (del(id, first) == 1)
				printf("해당 학번은 업는 자료입니다.\n\n");
			break;
		}

		case 'f': {
			printf("탐색할 자료의 학번을 입력하시오:");
			scanf("%d", &id);
			fflush(stdin);
			if (search_node(first, id) == 1)
				printf("해당 학번은 업는 자료입니다.\n\n");
			break;
		}

		case 'r': printList(first); break;

		case 'q': break;

		}
	}

	return 0;
}

nodePointer allocate_node()
{
	nodePointer ptr;
	//MALLOC(ptr, sizeof(node));
	ptr = (struct node *) malloc(sizeof(struct node));
	return ptr;
}

void initialize_node(nodePointer current, int id, char name[], char address[])
{
	current->id = id;
	strcpy(current->name, name);
	strcpy(current->address, address);
	current->next = NULL;
}


void add(int id, char name[], char address[])
{
	nodePointer current;
	current = allocate_node();
	initialize_node(current, id, name, address);
	insert(&first, current);
}


void insertBST(node **rootPtr, node x)
{
	node *ptr, *parent;
	int found = 0;
	found = searchParentToInsert(*rootPtr, x.id, &parent);
	if (found == 1) {
		printf("The key already exists in the tree!\n");
	}
	else { /* x.key is not in the tree */
		ptr = (node *)malloc(sizeof(node));
		
		ptr->data = x.data;
		ptr->leftChild = ptr->rightChild = NULL;
		if (*rootPtr == NULL) {
			*rootPtr = ptr;
		}
		else { /* insert ptr as a child of the parent */
			if (x.data.id < parent->data.id) parent->leftChild = ptr;
			else parent->rightChild = ptr;
		}
	}
}
int searchParentToInsert(node *root, int key, node **parentPtr)
{
	int found = 0;
	node *parent = NULL, *search = root;
	while (search != NULL) {
		if (key == search->data.id) {
			found = 1;
			break;
		}
		else {
			parent = search;
			if (key < search->data.id)
				search = search->leftChild;
			else
				search = search->rightChild;
		}
	}
	*parentPtr = parent;
	return found;
}

void delete_node(nodePointer *first, nodePointer prev, nodePointer current)
{
	if (prev) prev->next = current->next;
	else *first = current->next;

	printf("<학번, 이름, 주소> = <%d, %s, %s>이 삭제되었습니다.\n\n", current->id, current->name, current->address);
	free(current);
}

void printList(nodePointer current)
{
	printf("The list contains: \n");
	for (; current; current = current->next)
		printf("<%d, %s, %s>\n", current->id, current->name, current->address);
	printf(" \n");
}

node* searchBST(node *root, int key)
{
	node *search;
	search = root;
	while (search != NULL) {
		if (key == search->data.id) break;
		if (key < search->data.id) search = search->leftChild;
		else search = search->rightChild;
	}
	return search;
}
