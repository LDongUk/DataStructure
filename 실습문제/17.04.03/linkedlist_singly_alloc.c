#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nodePointer;
typedef struct node
{
	int id;
	char name[20];
	char address[100];
	nodePointer next;
};
nodePointer first = NULL;


nodePointer allocate_node();
void initialize_node(nodePointer current, int id, char name[], char address[]);
void add(int id, char name[], char address[]);
nodePointer find_prev_node(nodePointer first, nodePointer current);
void insert(nodePointer *first, nodePointer prev, nodePointer current);
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

	while(input != 'q')
	{
		printf("i(����), d(����), f(Ž��), r(��ü �б�), q(�۾�����)�� �����Ͻÿ�: ");
		scanf("%c", &input);
		fflush(stdin);
		
		switch(input)
		{
		case 'i' : {
			printf("������ �ڷ�(�й�, �̸�, �ּ�)�� �Է��Ͻÿ� :");
			scanf("%d", &id);
			scanf("%s", name);
			
			gets(address);
			fflush(stdin);
			add(id, name, address);

			break;
				   }
		
		case 'd' : {
			printf("������ �ڷ��� �й��� �Է��Ͻÿ�:");
			scanf("%d", &id);
			fflush(stdin);
			
			if(del(id, first) == 1)
				printf("�ش� �й��� ���� �ڷ��Դϴ�.\n\n");
			break;
				   }
		
		case 'f' : {
			printf("Ž���� �ڷ��� �й��� �Է��Ͻÿ�:");
			scanf("%d", &id);
			fflush(stdin);
			if(search_node(first, id) == 1)
				printf("�ش� �й��� ���� �ڷ��Դϴ�.\n\n");
			break;
				   }
		
		case 'r' : printList(first);break;
		
		case 'q' : break;
		
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
	nodePointer prev, current;
	current = allocate_node();
	initialize_node(current, id, name, address);
	prev = find_prev_node(first, current);
	insert(&first, prev, current);
}

nodePointer find_prev_node(nodePointer first, nodePointer current)
{
	nodePointer prev, search;
	prev = NULL;
	search = first;
	while (1) {
		if (search == NULL) break;
		if (search->id >= current->id) break;
		prev = search;
		search = search->next;
	}
	return prev;
}

void insert(nodePointer *first, nodePointer prev, nodePointer current)
{
	if (*first) {
		if (prev == NULL) { 
			current->next = *first;
			*first = current; 
		}
		else { 
			current->next = prev->next;
			prev->next = current;
		}
	}
	
	else {
		*first = current; 
	}
}

void delete_node(nodePointer *first, nodePointer prev, nodePointer current)
{
	if (prev) prev->next = current->next;
	else *first = current->next;

	printf("<�й�, �̸�, �ּ�> = <%d, %s, %s>�� �����Ǿ����ϴ�.\n\n", current->id, current->name, current->address);
	free(current);
}

void printList(nodePointer current)
{
	printf("The list contains: \n");
	for (; current; current = current->next)
		printf("<%d, %s, %s>\n", current->id, current->name, current->address);
	printf(" \n");
}

int search_node(nodePointer current, int id)
{
	for (; current; current = current->next)
	{
		if(current->id == id)
		{
			printf("<%d, %s, %s>\n\n", current->id, current->name, current->address);
			return 0;
		}
	}

	return 1;

}

int del(int id, nodePointer current)
{
	nodePointer prev;
	
	for (; current; current = current->next)
	{
		if(current->id == id)
		{
			prev = find_prev_node(first, current);
			delete_node(&first, prev, current);
			return 0;
		}
	}
	return 1;
}