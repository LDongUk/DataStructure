#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SWAP(x,y,t) ( (t) = (x), (x) = (y), (y) = (t))
#define ORIGIN 200000
#define TEMP 10000

typedef struct {
	int value;
	int run;
} heap;

heap tree[8];
int r1[1024], r2[1024], r3[104], r4[1024];
int t1, t2, t3 ,t4;
int block_position = 1;

void selectionSort(int a[], int n);
void initializeBlock(int run[]);
void mergeRun(FILE *temp1, FILE *temp2);
void initializeBlock(int run[]);
void setTree();
void initializeTree(int index);


int main()
{
	int i, j, k, temp;
	int sorted[TEMP];
	int randNum[1000];
	

	FILE *origin;
	FILE *temp1;
	FILE *temp2;


	srand(time(NULL));
	origin = fopen("origin.dat", "wb+");

	sizeof(randNum);

	for(i = 0; i < ORIGIN / 1000; i++)
	{
		for(j = 0; j < 1000; j++)
			randNum[j] = rand();

		fwrite(randNum, sizeof(int), sizeof(randNum) / sizeof(int), origin);
	}
	
	
	temp1 = fopen("temp1.dat", "wb+");
	
	rewind(origin);
	for(i = 0; i < ORIGIN / TEMP; i++)
	{
		fread(sorted, sizeof(int), TEMP, origin);
		selectionSort(sorted, TEMP);
		fwrite(sorted, sizeof(int), TEMP, temp1);
	}

	rewind(temp1);

	
	fread(sorted,sizeof(int), TEMP, temp1);



	temp2 = fopen("temp2.dat", "wb+");
	
	mergeRun(temp1, temp2);

	return 0;
}

void selectionSort(int a[], int n)
{
	int i, j, min, temp;
	for (i = 0; i < n-1; i++) {
		min = i;
		for (j = i+1; j < n; j++)
			if (a[j] < a[min]) min = j;
		if (min != i)
			SWAP(a[i],a[min],temp);
	}
}


void initializeBlock(int run[])
{
	int i;

	for(i = 0; i < 1024; i++)
		run[i] = -1;

}

void setTree()
{
	int i, j;

	
	for (j = 2; j != 0; j /= 2)
	{
		for (i = j; i < j * 2; i++)
		{
			//둘 다 -1
			if(tree[2*i].value == -1 && tree[2*i+1].value == -1)
				tree[i].value = -1;
		
			// 하나만 -1
			else if(tree[2*i].value == -1)
			{
				tree[i].value = tree[2*i+1].value;
				tree[i].run = tree[2*i+1].run;
			}
			// 하나만 -1
			else if(tree[2*i+1].value == -1)
			{
				tree[i].value = tree[2*i].value;
				tree[i].run = tree[2*i].run;
			}
			//둘 다 -1이 아닐 때
			else if(tree[2*i].value != -1 && tree[2*i+1].value != -1)
			{
				tree[i].value = (tree[2 * i].value <= tree[2 * i + 1].value) ? tree[2 * i].value : tree[2 * i + 1].value;
				tree[i].run = (tree[2 * i].value <= tree[2 * i + 1].value) ? tree[2 * i].run : tree[2 * i + 1].run;	
			}
		}
	}

}

void initializeTree(int index)
{
	switch(index)
	{
	case 1 : tree[4].value = r1[t1]; break;
	case 2 : tree[5].value = r2[t2]; break;
	case 3 : tree[6].value = r3[t3]; break;
	case 4 : tree[7].value = r4[t4]; break;
	}
}

void mergeRun(FILE *temp1, FILE *temp2)
{
	int i, j, num;
	int newRun[4096];
	int index;
	long position;
	
	tree[4].run = 1;
	tree[5].run = 2;
	tree[6].run = 3;
	tree[7].run = 4;

	for(i = 0; i < ORIGIN / (TEMP * 4); i++)
	{
		initializeBlock(r1);
		initializeBlock(r2);
		initializeBlock(r3);
		initializeBlock(r4);

		rewind(temp1);

		for(j = 0; j < 1024 *(block_position - 1); j++)
			fscanf(temp1, "%d");	
		fread(r1, sizeof(int), TEMP, temp1);
		
		for(j = 0; j < 10000 - 1024; j++)
			fscanf(temp1, "%d");
		fread(r2, sizeof(int), TEMP, temp1);

		for(j = 0; j < 10000 - 1024; j++)
			fscanf(temp1, "%d");
		fread(r3, sizeof(int), TEMP, temp1);

		for(j = 0; j < 10000 - 1024; j++)
			fscanf(temp1, "%d");
		fread(r4, sizeof(int), TEMP, temp1);

		position = ftell(temp1) + 1;
		fseek(temp1, position, 0);
		fread(r2, sizeof(int), 5, temp1);

		tree[4].value = r1[0];
		tree[5].value = r2[0];
		tree[6].value = r3[0];
		tree[7].value = r4[0];


		j = 0;
		while(1)
		{
			initializeTree(tree[1].run);
			setTree();
			newRun[j] = tree[1].value;
			j++;
			
			switch(tree[1].run)
			{
			case 1 : t1++; break;
			case 2 : t2++; break;
			case 3 : t3++; break;
			case 4 : t4++; break;
			}

			if(tree[1].value == -1)
				break;
			
		}
		

	}


}

