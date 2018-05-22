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
nodePointer root = NULL;


void deletion();
void insertion();
void insertBST(node **rootPtr, node x);
int searchParentToInsert(node *root, int key, node **parentPtr);
void printList(nodePointer current);
int searchParentTargetToDelete(node *root, int id, node **parentPtr, node **searchPtr);
int deleteBST(node **rootPtr, int id);
void searchSmallestAmongLagerNodes(node *target, int id, node **parentSmallPtr, node **smallPtr);
void findChildren();
void find();

int main()
{
	char input = 's';
	char temp = 's';
	int id;
	char name[20];
	char address[100];

	while (input != 'q')
	{
		printf("i(삽입), d(삭제), f(탐색), r(전체 읽기), c(자식들 읽기), q(작업종료)를 선택하시오: ");
		scanf("%c", &input);
		fflush(stdin);

		switch (input)
		{
		case 'i': insertion(); break;
		case 'd': deletion(); break;
		case 'f': find(); break;
		case 'r': printList(root); printf("\n"); break;
		case 'c': findChildren(); break;
		case 'q': break;
		}
	}

	return 0;
}

void deletion()
{
	int id;
	printf("삭제할 자료의 학번을 입력하시오:");
	scanf("%d", &id);
	fflush(stdin);

	deleteBST(&root, id);
	printf("\n");
}


void insertion()
{
	node current;
	int id;
	char name[20];
	char address[100];
	
	while(1)
	{
		printf("삽입할 자료(학번, 이름, 주소)를 입력하시오 (종료 -1) :");
		scanf("%d", &id);

		if(id == -1)
			break;

		scanf("%s", name);

		gets(address);
		fflush(stdin);

		current.data.id = id;
		strcpy(current.data.name, name);
		strcpy(current.data.address, address);
		current.leftChild = NULL;
		current.rightChild = NULL;

		insertBST(&root, current);
	}
	fflush(stdin);
	printf("\n");
}


void insertBST(node **rootPtr, node x)
{
	node *ptr, *parent;
	int found = 0;
	found = searchParentToInsert(*rootPtr, x.data.id, &parent);
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



void printList(nodePointer current)
{
	if(current)
	{
		printList(current->leftChild);
		printf("<%d, %s, %s>\n", current->data.id, current->data.name, current->data.address);
		printList(current->rightChild);
	}

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


int deleteBST(node **rootPtr, int id)
{
	node *root, *parent, *search, *parentSmall, *searchSmall;
	root = *rootPtr;
	
	if(searchParentTargetToDelete(root, id, &parent, &search) == 0)
		return 0; //not found

	//leaf
	if((search->leftChild == NULL) && (search->rightChild == NULL))
	{
		//delete root
		if(parent == NULL)
		{
			*rootPtr = NULL;
			return 1;
		}


		if(parent->leftChild == search)
			parent->leftChild = NULL;

		else if(parent->rightChild == search)
			parent->rightChild = NULL;

		free(search);
		return 1;
	}

	//case 2
	if((search->leftChild == NULL) || (search->rightChild == NULL))
	{
		//delete root
		if(parent == NULL)
		{
			if(search->leftChild != NULL)
				*rootPtr = (*rootPtr)->leftChild;

			else if(search->rightChild != NULL)
				*rootPtr = (*rootPtr)->rightChild;
		
			return 1;
		}
		
		if(parent->leftChild == search)
		{
			if(search->leftChild != NULL)
				parent->leftChild = search->leftChild;

			else if(search->rightChild != NULL)
				parent->leftChild = search->rightChild;
		}

		else if(parent->rightChild == search)
		{
			if(search->leftChild != NULL)
				parent->rightChild = search->leftChild;

			else if(search->rightChild != NULL)
				parent->rightChild = search->rightChild;
		}

		free(search);
		return 1;
	}

	//case 3
	if((search->leftChild != NULL)&&(search->rightChild != NULL))
	{
		searchSmallestAmongLagerNodes(search, id, &parentSmall, &searchSmall);

		if(search == parentSmall)
		{
			search->data.id = searchSmall->data.id;
			strcpy(search->data.name, searchSmall->data.name);
			strcpy(search->data.address, searchSmall->data.address);

			search->rightChild = searchSmall->rightChild;

			free(searchSmall);
			return 1;
		}

		else
		{
			search->data.id = searchSmall->data.id;
			strcpy(search->data.name, searchSmall->data.name);
			strcpy(search->data.address, searchSmall->data.address);

			parentSmall->leftChild = searchSmall->rightChild;
			free(searchSmall);
			return 1;
		}

	}



}


int searchParentTargetToDelete(node *root, int id, node **parentPtr, node **searchPtr)
{
	node *parent = NULL;
	while(root != NULL)
	{
		if(root->data.id == id)
		{
		*searchPtr = root;
		*parentPtr = parent;
		return 1;
		}
		
		parent = root;
		if(root->data.id > id)
			root = root->leftChild;

		else
			root = root->rightChild;

	}
	
	return 0;
}

void searchSmallestAmongLagerNodes(node *target, int id, node **parentSmallPtr, node **smallPtr)
{
	node *ptr;

	ptr = target->rightChild;
	*parentSmallPtr = target;
	while(ptr->leftChild != NULL)
	{
		*parentSmallPtr = ptr;
		ptr = ptr->leftChild;
	}

	*smallPtr = ptr;

}

void findChildren()
{
	int id;
	int flag = 0;
	node *parent = NULL;
	node *rootptr = root;


	printf("탐색할 자료의 학번을 입력하시오: ");
	scanf("%d", &id);
	fflush(stdin);

	while(rootptr != NULL)
	{
		if(rootptr->data.id == id)
		{
			flag = 1;
			printf("<학번, 이름, 주소> = <%d, %s, %s>\n", rootptr->data.id, rootptr->data.name, rootptr->data.address);
			
			if(rootptr->leftChild == NULL)
				printf("왼쪽 자식 : 없음\n");

			else
				printf("왼쪽 자식 : <%d, %s, %s>\n", rootptr->leftChild->data.id, rootptr->leftChild->data.name, rootptr->leftChild->data.address);
		
		
			if(rootptr->rightChild == NULL)
				printf("오른쪽 자식 : 없음\n");
		
			else
				printf("오른쪽 자식 : <%d, %s, %s>\n", rootptr->rightChild->data.id, rootptr->rightChild->data.name, rootptr->rightChild->data.address);
		
			break;
		}
		

		if(rootptr->data.id > id)
			rootptr = rootptr->leftChild;

		else
			rootptr = rootptr->rightChild;

	}

	if(flag == 0)
		printf("해당 학번은 없는 학번입니다.\n");

	printf("\n");
}

void find()
{
	int id;
	int flag = 0;
	node *parent = NULL;
	node *rootptr = root;


	printf("탐색할 자료의 학번을 입력하시오: ");
	scanf("%d", &id);
	fflush(stdin);

	while(rootptr != NULL)
	{
		if(rootptr->data.id == id)
		{
			flag = 1;
			printf("<학번, 이름, 주소> = <%d, %s, %s>\n", rootptr->data.id, rootptr->data.name, rootptr->data.address);	
			break;
		}
		

		if(rootptr->data.id > id)
			rootptr = rootptr->leftChild;

		else
			rootptr = rootptr->rightChild;

	}
	
	if(flag == 0)
		printf("해당 학번은 없는 학번입니다.\n");

	printf("\n");
}