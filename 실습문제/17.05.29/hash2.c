#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nodePointer;

typedef struct node{
	int index;
	char name[30];
	nodePointer link;

} hash;

typedef struct{
	char major[30];
	int id;
	char name[30];
}student;

nodePointer ht[13];
student a[40];
int length_of_chain[13];

void initializeHT();
void insertHT();
void printHT();
void searchHT();
void deleteHT();
int h(int k);
void setArray();
int stringToint(char *key);

int main()
{
	setArray();
	insertHT();
	printHT();
	searchHT();
	deleteHT();
	printHT();

	return 0;
}

int h(int k)
{
	return k % 13;
}

void initializeHT()
{
	int i;

	for(i = 0; i < 13; i++)
		ht[i] = NULL;
}

void insertHT()
{
	int i;
	int hash_address;
	char major[30];
	int id;
	char name[30];

	nodePointer x, y;

	for(i = 0; i < 40; i++)
	{
		hash_address = h(stringToint(a[i].name));
		x = (struct node*)malloc(sizeof(struct node));
		sprintf(x->name, a[i].name);
		x->index = i;
		x->link = NULL;

		if(ht[hash_address] == NULL)
			ht[hash_address] = x;	
		else
		{
			for(y = ht[hash_address]; y->link != NULL; y = y->link);
				y->link = x;
		}

		length_of_chain[hash_address]++;

	}
}

void printHT()
{
	int i;
	nodePointer x;
	
	printf("========================\n");
	for(i = 0; i < 13; i++)
	{
		printf("Ht[%d]: ", i);
		if(ht[i] == NULL)
		{
			printf("\n");
			continue;
		}
		else
		{
			for(x = ht[i]; x != NULL; x = x->link)
				printf("<%s, %d>, ", x->name, x->index);
			printf("\b\b \n");
		}
	}
	printf("\n");
}

void searchHT()
{
	int i, count;
	char flag;
	int hash_address;
	char searchName[30];

	nodePointer x;

	printf("========================\n\n");
	while(1)
	{
		printf("탐색할 이름을 입력하시오(종료 x) : ");
		scanf("%s", searchName);

		if(strcmp(searchName, "x") == 0 || strcmp(searchName, "X") == 0)
			break;

		hash_address = h(stringToint(searchName));

		flag = 'x';
		if(ht[hash_address] == NULL)
			printf("학생정보 : 없음\n");
		else
		{
			for(x = ht[hash_address], count = 1; x != NULL; x = x->link, count++)
			{
				if(strcmp(x->name, searchName) == 0)
				{
					printf("학생정보 : index = %d, <%s, %d, %s>\n", x->index, a[x->index].major, a[x->index].id, a[x->index].name);
					flag = 'y';
				}
			}
		}

		if(flag == 'x')
				printf("학생정보 : 없음\n");
	}
}

void deleteHT()
{
	int i, count;
	int hash_address;
	char searchName[30];
	nodePointer pre, current;

	printf("========================\n\n");
	while(1)
	{
		printf("삭제할 이름을 입력하시오 (종료 : x) : ");
		scanf("%s", &searchName);

		if(strcmp(searchName, "x") == 0 || strcmp(searchName, "X") == 0)
			break;

		hash_address = h(stringToint(searchName));
		if(ht[hash_address] == NULL)
			printf("%s은(는) hash table에 존재하지 않습니다.\n", searchName);
		else
		{
			pre = ht[hash_address];
			for(current = ht[hash_address], count = 1; current != NULL; current = current->link, count++)
			{
				if(strcmp(current->name, searchName) == 0)
				{
					printf("%s을(를) hash table의 %d번째 엔트리의 레코드 %d 에서 삭제합니다.\n", searchName, hash_address, count);
					
					if(current == ht[hash_address])
					{
						ht[hash_address] = ht[hash_address]->link;
						break;
					}
					else
					{
						pre->link = current->link;
						free(current);
						break;
					}
				}
				pre = current;
			}

			if(current == NULL)
				printf("%s은(는) hash table에 존재하지 않습니다.\n", searchName);
		}
	}
}


void setArray()
{
	int i;
	char major[30];
	int id;
	char name[30];

	printf("40명의 학생 정보를 입력합니다.\n소속, 학번, 이름 순으로 입력하시오.\n");
	for(i = 0; i < 40; i++)
	{
		scanf("%s", a[i].major);
		scanf("%d", &a[i].id);
		scanf("%s", a[i].name);
	}

	printf("\n\n");
	for(i = 0; i < 40; i++)
		printf("<%s, %d, %s>\n", a[i].major, a[i].id, a[i].name);

}

int stringToint(char key[])
{
	/* simple additive approach to create a natural number that is within the integer range */
	int number = 0;
	int i = 0;
	while (key[i] != '\0')
		number += key[i++];

	if(number < 0)
		return -number;
	
	else
		return number;
}