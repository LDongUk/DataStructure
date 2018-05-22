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

heap winner_tree[16];
int result[MAX_NUM];
int top = -1;

void initializeRun();
void printRun();
void setTree();
void initializeWinnerValue();
void initializeWinnerRun();
void merge();
void push(int item);
void printAdjustedTree();
void printMergedTree();

int main()
{
	
	initializeRun();
	printRun();
	printAdjustedTree();
	merge();
	printMergedTree();

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
	//각 run의 마지막에 -1 삽입
	r0[index0] = -1;
	r1[index1] = -1;
	r2[index2] = -1;
	r3[index3] = -1;
	r4[index4] = -1;
	r5[index5] = -1;
	r6[index6] = -1;
	r7[index7] = -1;
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
	int index;

	for(index = 0; index < 8; index++)
		initializeWinnerValue(index);

	while (1)
	{
		initializeWinnerValue(index);
		setTree();
		num = winner_tree[0].value;

		if (num == -1)
			break;

		//각 run의 index 상승
		switch (winner_tree[0].run)
		{
		case 0: top0++; index = 0; break;
		case 1: top1++; index = 1; break;
		case 2: top2++; index = 2; break;
		case 3: top3++; index = 3; break;
		case 4: top4++; index = 4; break;
		case 5: top5++; index = 5; break;
		case 6: top6++; index = 6; break;
		case 7: top7++; index = 7; break;
		}

		push(num);
	}
}

void setTree()
{
	int i, j;

	
	for (j = 4; j != 0; j /= 2)
	{
		for (i = j; i < j * 2; i++)
		{
			//둘 다 -1
			if(winner_tree[2*i].value == -1 && winner_tree[2*i+1].value == -1)
				winner_tree[i].value = -1;
		
			// 하나만 -1
			else if(winner_tree[2*i].value == -1)
			{
				winner_tree[i].value = winner_tree[2*i+1].value;
				winner_tree[i].run = winner_tree[2*i+1].run;
			}
			// 하나만 -1
			else if(winner_tree[2*i+1].value == -1)
			{
				winner_tree[i].value = winner_tree[2*i].value;
				winner_tree[i].run = winner_tree[2*i].run;
			}
			//둘 다 -1이 아닐 때
			else if(winner_tree[2*i].value != -1 && winner_tree[2*i+1].value != -1)
			{
				winner_tree[i].value = (winner_tree[2 * i].value <= winner_tree[2 * i + 1].value) ? winner_tree[2 * i].value : winner_tree[2 * i + 1].value;
				winner_tree[i].run = (winner_tree[2 * i].value <= winner_tree[2 * i + 1].value) ? winner_tree[2 * i].run : winner_tree[2 * i + 1].run;	
			}
		}
	}

	winner_tree[0] = winner_tree[1];
}

void initializeWinnerValue(int index)
{
	switch(index)
	{
	case 0 : winner_tree[8].value = r0[top0]; break;
	case 1 : winner_tree[9].value = r1[top1]; break;
	case 2 : winner_tree[10].value = r2[top2]; break;
	case 3 : winner_tree[11].value = r3[top3]; break;
	case 4 : winner_tree[12].value = r4[top4]; break;
	case 5 : winner_tree[13].value = r5[top5]; break;
	case 6 : winner_tree[14].value = r6[top6]; break;
	case 7 : winner_tree[15].value = r7[top7]; break;
	}

}

void push(int item)
{
	if (top == MAX_NUM + 1)
	{
		fprintf(stderr, "STACK IS FULL");
		exit(EXIT_FAILURE);
	}

	result[++top] = item;
}

void initializeWinnerRun()
{
	winner_tree[8].run = 0;
	winner_tree[9].run = 1;
	winner_tree[10].run = 2;
	winner_tree[11].run = 3;
	winner_tree[12].run = 4;
	winner_tree[13].run = 5;
	winner_tree[14].run = 6;
	winner_tree[15].run = 7;
}

void printAdjustedTree()
{
	int i;

	initializeWinnerRun();
	for(i = 0; i < 8; i++)
		initializeWinnerValue(i);
	setTree();

	printf("An adjusted winner tree : ");
	for (i = 1; i < 16; i++)
		printf("%d ", winner_tree[i].value);
}

void printMergedTree()
{
	int i;

	printf("\nMerge sort : \n");
	for (i = 0; i < MAX_NUM; i++)
		printf("%d ", result[i]);
	printf("\n");
}