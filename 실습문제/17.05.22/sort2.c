#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x,y,t) ( (t) = (x), (x) = (y), (y) = (t))
//#define MAX_SIZE 100000
int MAX_SIZE;
int *a;
void rand_num_generator(int n);
void selectionSort(int a[], int n);
void mergeSort(int orig[], int EndIndex);
void mergePass(int initList[], int mergedList[], int EndIndex, int runSize);
void merge(int initList[], int mergedList[], int LeftRunStart, int LeftRunEnd, int RightRunEnd);
void heapSort(int a[], int n);
void adjust(int a[], int root, int n);

int main()
{
	
	int i;
	int n;
	int repetitions;
	int step;
	double duration;
	clock_t start;

	printf("a의 크기를 입력하시오 (10, 100, 1000, 10000, 100000) : ");
	scanf("%d", &MAX_SIZE);

	a = (int *)malloc(sizeof(int) * (MAX_SIZE+1));

	srand(time(NULL));
	//rand_num_generator(MAX_SIZE);
	

	printf("\n");
	printf("%-25s%-10s%-10s\n", "SORTING NAME", "SIZE", "TIME");


	repetitions = 0;
	start= clock();
	do {
		repetitions++;
		rand_num_generator(MAX_SIZE);
		selectionSort(a, MAX_SIZE);
	} while (clock( ) - start< 1000); /* repeat until enough time has elapsed */

	duration= ((double) (clock() -start)) / CLOCKS_PER_SEC;
	duration /= repetitions;
	printf("%-19s : %6d       %f \n", "Selection Sort", MAX_SIZE, duration);


	start= clock();
	repetitions = 0;
	do {
		repetitions++;
		rand_num_generator(MAX_SIZE);
		mergeSort(a, MAX_SIZE);
	} while (clock( ) - start< 1000); /* repeat until enough time has elapsed */

	duration= ((double) (clock() -start)) / CLOCKS_PER_SEC;
	duration /= repetitions;
	printf("%-19s : %6d       %f \n", "Merge Sort", MAX_SIZE, duration);


	start= clock();
	repetitions = 0;
	do {
		repetitions++;
		rand_num_generator(MAX_SIZE);
		heapSort(a, MAX_SIZE);
	} while (clock( ) - start< 1000); /* repeat until enough time has elapsed */

	duration= ((double) (clock() -start)) / CLOCKS_PER_SEC;
	duration /= repetitions;
	printf("%-19s : %6d       %f \n", "Heap Sort", MAX_SIZE, duration);


	//for(i = 1; i < MAX_SIZE; i+=5)
	//	printf("%d %d %d %d %d\n", a[i], a[i+1], a[i+2], a[i+3], a[i+4]);


	return 0;
}

void rand_num_generator(int n)
{

	int i;


	
	for(i = 1; i <= n; i++)
		a[i] = rand() % 10000 + 1;

}

void selectionSort(int a[], int n)
{
	int i, j, min, temp;
	for (i = 1; i < n; i++) {
		min = i;
		for (j = i+1; j < n+1; j++)
			if (a[j] < a[min]) min = j;
		if (min != i)
			SWAP(a[i],a[min],temp);
	}
}

void mergeSort(int orig[], int EndIndex)
{
	/* sort orig[1:n] using the merge sort method */
	int runSize = 1;
	int *extra;

	extra = (int *)malloc(sizeof(int) * (MAX_SIZE+1));
	while (runSize <= MAX_SIZE) {
		mergePass(orig, extra, EndIndex, runSize);
		runSize *= 2;
		mergePass(extra, orig, EndIndex, runSize);
		runSize *= 2;
	}
}

void mergePass(int initList[], int mergedList[], int EndIndex, int runSize)
{
	int left, target;
	left = 1;
	// Merge 2 runs of equal size
	for (; left <= (EndIndex - 2*runSize + 1); left += 2*runSize)
		merge(initList,mergedList,left,left+runSize-1,left+2*runSize-1);
	if (left + runSize - 1 < EndIndex) {
		// merge 2 sublists of size s and size less than s
		merge(initList,mergedList,left,left+runSize-1,MAX_SIZE);
	} else {
		// 1 remaining sublist of size less than s
		for (target = left; target <= EndIndex; target++)
			mergedList[target] = initList[target];
	}
}

void merge(int initList[], int mergedList[], int LeftRunStart, int LeftRunEnd, int RightRunEnd)
{
	/* the sorted lists initList[LeftRunStart:LeftRunEnd] and initList[LeftRunEnd+l:RightRunEnd] are merged
	to obtain the sorted list mergedList[LeftRunStart:RightRunEnd] */
	int left, right, target;
	left = LeftRunStart;
	right = LeftRunEnd+1;
	target = LeftRunStart;
	while (left <= LeftRunEnd && right <= RightRunEnd) {
		if (initList[left] <= initList[right])
			mergedList[target++] = initList[left++];
		else
			mergedList[target++] = initList[right++];
	}
	if (left > LeftRunEnd) {
		for (; right <= RightRunEnd; )
			mergedList[target++] = initList[right++];
	} else {
		for (; left <= LeftRunEnd; )
			mergedList[target++] = initList[left++];
	}
}


void heapSort(int a[], int n)
{
	/* perform a heap sort on a[l:n] */
	int i;
	int temp;
	/* build the initial heap */
	for (i = n/2; i > 0; i--)
		adjust(a,i,n);
	/* sort */
	for (i = n-1; i > 0; i--) {
		SWAP(a[1],a[i+1],temp);
		adjust(a,1,i);
	}
}void adjust(int a[], int root, int n)
{
	/* a[root]를 제외하고 n까지의 그 하위 tree들은 max-heap이 구성되어 있다 */
	/* 이제 a[root]를 포함하여 그 tree의 max-heap을 구성하라 */
	int child,rootkey;
	int temp;
	temp= a[root];
	rootkey = a[root];
	child = 2*root; /* the left child */
	while (child <= n) {
		if ((child < n) && (a[child]< a[child+1]))
			child++;
		if (rootkey > a[child]) break;
		else {
			a[child/2] = a[child]; /* move child to parent */
			child *= 2;
		}
	}
	a[child/2] = temp;
}