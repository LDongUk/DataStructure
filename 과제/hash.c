#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 500

typedef struct add *Pointer;

typedef struct {
	int value;
} bucket;


struct add {
	bucket slot[8];
};

typedef struct {
	int ld;
	Pointer addressPointer;
}hash;

int a[MAX];
int gd = 4, size = 16;
int top_of_a = 0;
hash *directory;


void random_num();
void initializeDR();
int h(int key);
int h_index(int k, int p);
void copyDR();
void initialize_OneDR(int index);
void insertDR(int key);
void printDR();
int searchDR(int key); // 0을 리턴 : 찾기 실패 // 1을 리턴 : 찾기 성공
int deleteDR(int key);

int main()
{
	int i;

	directory = (hash*)malloc(sizeof(hash) * size);
	random_num();
	initializeDR();

	for (i = 0; i < MAX; i++)
	{
		//if (i == 60)
		//	printf(" ");
		insertDR(a[i]);
	}
	
	for(i = 0; i < MAX; i++)
		searchDR(a[i]);
	
	for (i = 0; i < MAX - 10; i++)
		deleteDR(a[i]);
	printDR();

	return 0;
}


void random_num()
{
	int i;

	srand(time(NULL));

	for (i = 0; i < 1000; i++)
		a[i] = rand();
}


void initializeDR()
{
	int i, j;

	for (i = 0; i < 16; i++)
	{
		directory[i].ld = gd;

		directory[i].addressPointer = (struct add*)malloc(sizeof(struct add));
		for (j = 0; j < 8; j++)
			directory[i].addressPointer->slot[j].value = -1;
	}
}

int h(int key)
{
	return key % size;
}

int h_index(int k, int p)
{
	int h_k, count;
	int mask = 0x01;

	h_k = h(k);

	for (count = 1; count < p; count++)
		mask = (mask << 1) + (0x01);


	return h_k & mask;
}


void copyDR()
{
	int i;

	for (i = size / 2; i < size; i++)
		directory[i] = directory[i - size / 2];
}

void initialize_OneDR(int index)
{
	int i;

	directory[index].ld = gd;
	
	for (i = 0; i < 8; i++)
		directory[index].addressPointer->slot[i].value = -1;
}

void printDR()
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		printf("directory[%d] : local depth = %d  bucket(", i, directory[i].ld);

		for (j = 0; j < 8; j++)
			printf("%d, ", directory[i].addressPointer->slot[j].value);
		printf("\b\b)\n");
	}
}

void insertDR(int key)
{
	int index, i;
	int flag_input = 0;
	int new_index;
	int new_bucketValue;
	int temp[8];

	index = h_index(key, gd);

	if (index - size / 2 >= 0)
	{
		if (directory[index].addressPointer == directory[index - size / 2].addressPointer)
		{
			directory[index].addressPointer = (struct add*)malloc(sizeof(struct add));
			initialize_OneDR(index);
		}
	}

	if (index >= 16 && directory[index].ld == 4)
	{
		directory[index].addressPointer = (struct add*)malloc(sizeof(struct add));
		initialize_OneDR(index);
	}
	
	//slot이 비어있으면 입력
	for (i = 0; i < 8; i++)
	{
		if (directory[index].addressPointer->slot[i].value == -1)
		{
			directory[index].addressPointer->slot[i].value = key;
			flag_input = 1;
			break;
		}
	}
	//slot이 가득 찼을 경우
	if (flag_input == 0)
	{
		size *= 2;
		gd++;
		directory[index].ld++;
		directory = (hash*)realloc(directory, sizeof(hash) * size);
		copyDR();

		for (i = 0; i < 8; i++)
			temp[i] = directory[index].addressPointer->slot[i].value;

		initialize_OneDR(index);

		for (i = 0; i < 8; i++)
		{
			new_index = h_index(temp[i], gd);
			if (new_index >= size / 2)
			{
				directory[new_index].addressPointer = (struct add*)malloc(sizeof(struct add));
				initialize_OneDR(new_index);
			}
			insertDR(temp[i]);

		}

		insertDR(key);
	}

}


int searchDR(int key)
{
	int index, i;
	int global_depth;
	int count = 0;

	for (global_depth = 4; global_depth <= gd; global_depth++)
	{
		index = h_index(key, global_depth);


		if (global_depth == gd)
		{
			for (i = 0; i < 8; i++)
			{
				if (directory[index].addressPointer->slot[i].value == -1)
					count++;
			}
		}


		if (count == 8)
		{
			printf("%d is not exist.\n", key);
			return 0;
		}

		for (i = 0; i < 8; i++)
		{
			if (directory[index].addressPointer->slot[i].value == key)
			{
				printf("directory[%d} : local depth = %d , slot%d = %d\n", index, directory[index].ld, i+1, key);
				return 1;
			}

		}


	}
	
	printf("%d is not exist.\n", key);
	return 0;
}


int deleteDR(int key)
{
	int index, i, j;
	int global_depth;
	int count = 0;
	int sibling;

	for (global_depth = 4; global_depth <= gd; global_depth++)
	{
		index = h_index(key, global_depth);


		if (global_depth == gd && directory[index].addressPointer->slot[i].value == -1)
		{
			for (i = 0; i < 8; i++)
				count++;
		}
		if (count == 8)
		{
			printf("%d is not exist.\n", key);
			return 0;
		}


		for (i = 0; i < 8; i++)
		{
			if (directory[index].addressPointer->slot[i].value == key)
			{
				for (j = i + 1; j < 8; j++)
					directory[index].addressPointer->slot[j - 1].value = directory[index].addressPointer->slot[j].value;
				
				directory[index].addressPointer->slot[7].value = -1;
			}

		}

		//삭제후 slot이 비었을 시
		if (directory[index].addressPointer->slot[0].value == -1)
		{
			if (directory[index].ld != 4)
			{
				sibling = size / 2;

				if (index >= size / 2)
				{
					directory[index] = directory[index - sibling];
					directory[index].ld = directory[index - sibling].ld;
					if (directory[index].ld != 4)
					{
						directory[index].ld--;
						directory[index - sibling].ld--;
					}


					for (i = 0; i < size / 2; i++)
					{
						if (directory[i].ld < gd)
							count++;
					}

					if (count == size / 2)
					{
						size /= 2;
						gd--;

						for (i = 0; i < size / 2; i++)
						{
							if (directory[i].addressPointer->slot[0].value == -1)
								directory[i] = directory[i + sibling];
						}

						directory = (hash *)realloc(directory, sizeof(hash) * size);
						return 1;
					}


				}

				else
				{
					directory[index] = directory[index + sibling];
					if (directory[index].ld != 4)
					{
						directory[index].ld--;
						directory[index + sibling].ld--;
					}


					for (i = 0; i < size / 2; i++)
					{
						if (directory[i].ld < gd)
							count++;
					}

					if (count == size / 2)
					{
						size /= 2;
						gd--;

						for (i = 0; i < size / 2; i++)
						{
							if (directory[i].addressPointer->slot[0].value == -1)
								directory[i] = directory[i + sibling];
						}

						directory = (hash *)realloc(directory, sizeof(hash) * size);
						return 1;
					}
				}

			}

		}

	}

	printf("%d is not exist.\n", key);
	return 0;
}