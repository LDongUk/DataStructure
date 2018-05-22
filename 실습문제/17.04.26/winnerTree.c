#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 101

int r0[15];
int r1[15];
int r2[15];
int r3[15];
int r4[15];
int r5[15];
int r6[15];
int r7[15];

typedef struct {
	int value;
	int run;
} heap;

int top0, top1, top2, top3, top4, top5, top6, top7;

heap max_heap[16];
int merged_array[MAX_NUM];
int top = -1;

void initializeRun();
void printRun();
void setHeap();
void initializeHeap();
void merge();
void push(int item);


int main()
{
	int i;
	initializeRun();

	printRun();

	initializeHeap();
	setHeap();
	printf("An adjusted winner tree : ");
	for (i = 1; i < 8; i++)
		printf("%d ", max_heap[i].value);



	merge();
	printf("\nMerge sort : \n");
	for (i = 0; i < MAX_NUM; i++)
		printf("%d ", merged_array[i]);
	printf("\n");
	return 0;
}

void initializeRun()
{
	int i, j;
	int index0, index1, index2, index3, index4, index5, index6, index7;

	j = 0;
	index0 = index1 = index2 = index3 = index4 = index5 = index6 = index7 = 0;
	for (i = 0; i < MAX_NUM; i++)
	{

		if (j % 2 == 0)
		{
			switch (i % 8)
			{

			case 0:r0[index0] = i; index0++; break;
			case 1:r1[index1] = i; index1++; break;
			case 2:r2[index2] = i; index2++; break;
			case 3:r3[index3] = i; index3++; break;
			case 4:r4[index4] = i; index4++; break;
			case 5:r5[index5] = i; index5++; break;
			case 6:r6[index6] = i; index6++; break;
			case 7:r7[index7] = i; index7++; break;
			}
		}

		else
		{
			switch (i % 8)
			{

			case 0:r7[index7] = i; index7++; break;
			case 1:r6[index6] = i; index6++; break;
			case 2:r5[index5] = i; index5++; break;
			case 3:r4[index4] = i; index4++; break;
			case 4:r3[index3] = i; index3++; break;
			case 5:r2[index2] = i; index2++; break;
			case 6:r1[index1] = i; index1++; break;
			case 7:r0[index0] = i; index0++; break;
			}
		}

		if (i % 8 == 7)
			j++;

	}

	for (i = index0; i < 15; i++)
		r0[i] = 1000;

	for (i = index1; i < 15; i++)
		r1[i] = 1000;
	
	for (i = index2; i < 15; i++)
		r2[i] = 1000;
	
	for (i = index3; i < 15; i++)
		r3[i] = 1000;
	
	for (i = index4; i < 15; i++)
		r4[i] = 1000;
	
	for (i = index5; i < 15; i++)
		r5[i] = 1000;
	
	for (i = index6; i < 15; i++)
		r6[i] = 1000;
	
	for (i = index7; i < 15; i++)
		r7[i] = 1000;
}


void printRun()
{
	int i;

	printf("run 0 :");
	for (i = 0; i < 13; i++)
		printf("%d ", r0[i]);
	printf("\n");

	printf("run 1 :");
	for (i = 0; i < 13; i++)
		printf("%d ", r1[i]);
	printf("\n");

	printf("run 2 :");
	for (i = 0; i < 13; i++)
		printf("%d ", r2[i]);
	printf("\n");

	printf("run 3 :");
	for (i = 0; i < 13; i++)
		printf("%d ", r3[i]);
	printf("\n");

	printf("run 4 :");
	for (i = 0; i < 13; i++)
		printf("%d ", r4[i]);
	printf("\n");

	printf("run 5 :");
	for (i = 0; i < 12; i++)
		printf("%d ", r5[i]);
	printf("\n");

	printf("run 6 :");
	for (i = 0; i < 12; i++)
		printf("%d ", r6[i]);
	printf("\n");

	printf("run 7 :");
	for (i = 0; i < 12; i++)
		printf("%d ", r7[i]);
	printf("\n");
}

void merge()
{
	int num;


	while (1)
	{
		initializeHeap();
		setHeap();
		num = max_heap[0].value;

		switch (max_heap[0].run)
		{
		case 0: top0++; break;
		case 1: top1++; break;
		case 2: top2++; break;
		case 3: top3++; break;
		case 4: top4++; break;
		case 5: top5++; break;
		case 6: top6++; break;
		case 7: top7++; break;
		}


		if (num == 1000)
			break;

		push(num);

	}




}

void setHeap()
{
	int i, j;

	
	for (j = 4;; j /= 2)
	{
		for (i = j; i < j * 2; i++)
		{
			max_heap[i].value = (max_heap[2 * i].value <= max_heap[2 * i + 1].value) ? max_heap[2 * i].value : max_heap[2 * i + 1].value;
			max_heap[i].run = (max_heap[2 * i].value <= max_heap[2 * i + 1].value) ? max_heap[2 * i].run : max_heap[2 * i + 1].run;	
		}

		if (j == 0)
			break;
	}

	max_heap[0] = max_heap[1];

}

void initializeHeap()
{

	max_heap[8].value = r0[top0];
	max_heap[9].value = r1[top1];
	max_heap[10].value = r2[top2];
	max_heap[11].value = r3[top3];
	max_heap[12].value = r4[top4];
	max_heap[13].value = r5[top5];
	max_heap[14].value = r6[top6];
	max_heap[15].value = r7[top7];

	max_heap[8].run = 0;
	max_heap[9].run = 1;
	max_heap[10].run = 2;
	max_heap[11].run = 3;
	max_heap[12].run = 4;
	max_heap[13].run = 5;
	max_heap[14].run = 6;
	max_heap[15].run = 7;

}

void push(int item)
{
	if (top == MAX_NUM + 1)
	{
		fprintf(stderr, "STACK IS FULL");
		exit(EXIT_FAILURE);
	}

	merged_array[++top] = item;
}
