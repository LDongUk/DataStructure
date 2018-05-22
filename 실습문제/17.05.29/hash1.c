#include <stdio.h>
#include <stdlib.h>

typedef struct node *nodePointer;

typedef struct node{
	int key;
	nodePointer link;

} hash;

nodePointer ht[7];


void initializeHT();
void insertHT();
void printHT();
void searchHT();
void deleteHT();
int h(int k);

int main()
{
	initializeHT();
	insertHT();
	printHT();
	searchHT();
	deleteHT();
	printHT();

	return 0;
}

int h(int k)
{
	return k % 7;
}

void initializeHT()
{
	int i;

	for(i = 0; i < 7; i++)
		ht[i] = NULL;
}

void insertHT()
{
	int i;
	int input_key, hash_address;
	nodePointer x, y;
	printf("========================\n");
	printf("10, 8, 14, 12, 6, 18, 17, 24를 입력하시오\n");
	
	for(i = 0; i < 8; i++)
	{
		scanf("%d", &input_key);

		hash_address = h(input_key);
		x = (struct node*)malloc(sizeof(struct node));
		x->key = input_key;
		x->link = NULL;

		if(ht[hash_address] == NULL)
			ht[hash_address] = x;	
		else
		{
			for(y = ht[hash_address]; y->link != NULL; y = y->link);
				y->link = x;
		}

	}
}

void printHT()
{
	int i;
	nodePointer x;
	
	printf("========================\n");
	for(i = 0; i < 7; i++)
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
				printf("%d, ", x->key);
			printf("\b\b \n");
		}
	}
	printf("\n");
}

void searchHT()
{
	int i, count;
	int searchNum, hash_address;
	nodePointer x;

	printf("========================\n\n");
	printf("8, 12, 40, 17, 60\n");
	for(i = 0; i < 5; i++)
	{
		printf("탐색할 키를 입력하시오: ");
		scanf("%d", &searchNum);

		hash_address = h(searchNum);
		if(ht[hash_address] == NULL)
			printf("%d은(는) hash table에 존재하지 않습니다.\n", searchNum);
		else
		{
			for(x = ht[hash_address], count = 1; x != NULL; x = x->link, count++)
			{
				if(x->key == searchNum)
				{
					printf("%d은(는) hash table의 %d번째 엔트리의 레코드 %d 입니다.\n", searchNum, hash_address, count);
					break;
				}
			}

			if(x == NULL)
				printf("%d은(는) hash table에 존재하지 않습니다.\n", searchNum);
		}
	}
}

void deleteHT()
{
	int i, count;
	int searchNum, hash_address;
	nodePointer pre, current;

	printf("========================\n\n");
	printf("8, 12, 40, 17, 60\n");
	for(i = 0; i < 5; i++)
	{
		printf("삭제할 키를 입력하시오: ");
		scanf("%d", &searchNum);

		hash_address = h(searchNum);
		if(ht[hash_address] == NULL)
			printf("%d은(는) hash table에 존재하지 않습니다.\n", searchNum);
		else
		{
			pre = ht[hash_address];
			for(current = ht[hash_address], count = 1; current != NULL; current = current->link, count++)
			{
				if(current->key == searchNum)
				{
					printf("%d을(를) hash table의 %d번째 엔트리의 레코드 %d 에서 삭제합니다.\n", searchNum, hash_address, count);
					
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
				printf("%d은(는) hash table에 존재하지 않습니다.\n", searchNum);
		}
	}
}
