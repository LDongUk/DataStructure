#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ( (t) = (x), (x) = (y), (y) = (t))
#define MIDD(x,y,z) (((x) < (y)) ? ((y < z) ? y : ((x < z)  ? z : x)) : ((x) < (z) ? ((y < z) ? y : z) : y))

void selectionSort(int a[], int n);
void insertionSort(int a[], int n);
void insert(int e, int a[], int i);
void quickSort(int a[], int left, int right);
void quickSort_median(int a[], int left, int right);
int getMiddle(int a[], int left, int middle, int right);

int main()
{
	int *a;
	int size, i;
	long repetitions = 0;
	double duration;
	clock_t start;
	

	
	printf("Sequence의 크기를 입력하시오 (10, 100, 1000, 10000, 100000) : ");
	scanf("%d", &size);

	a = (int *)malloc(sizeof(int) * (size + 1));

	printf("\n");
	printf("%-25s%-10s%-10s\n", "SORTING NAME", "SIZE", "TIME");


	start= clock();
	do {
		repetitions++;
		for (i = 0; i < size; i++) a[i] = size - i; /* initialize with worst-case data */

		selectionSort(a, size);
	} while (clock( ) - start< 1000); /* repeat until enough time has elapsed */

	duration= ((double) (clock() -start)) / CLOCKS_PER_SEC;
	duration /= repetitions;
	printf("%-19s : %6d       %f \n", "Selection Sort", size, duration);






	start= clock();
	repetitions = 0;
	do {
		repetitions++;
		for (i = 0; i < size; i++) a[i] = size - i; /* initialize with worst-case data */
		insertionSort(a, size);
	} while (clock( ) - start< 1000); /* repeat until enough time has elapsed */

	duration= ((double) (clock() -start)) / CLOCKS_PER_SEC;
	duration /= repetitions;
	printf("%-19s : %6d       %f \n","Insertion Sort", size, duration);



	start= clock();
	repetitions = 0;
	do {
		repetitions++;
		for (i = 0; i < size; i++) a[i] = size - i; /* initialize with worst-case data */
		a[size] = size+1;
		quickSort_median(a, 0, size-1);
	} while (clock( ) - start< 1000); /* repeat until enough time has elapsed */

	duration= ((double) (clock() -start)) / CLOCKS_PER_SEC;
	duration /= repetitions;
	printf("%-19s : %6d       %f \n", "QUICK Sort(median)", size, duration);


	start= clock();
	repetitions = 0;
	do {
		repetitions++;
		for (i = 0; i < size; i++) a[i] = size - i; /* initialize with worst-case data */
		a[size] = size+1;
		quickSort(a, 0, size-1);
	} while (clock( ) - start< 1000); /* repeat until enough time has elapsed */

	duration= ((double) (clock() -start)) / CLOCKS_PER_SEC;
	duration /= repetitions;
	printf("%-19s : %6d       %f \n", "QUICK SORT", size, duration);

	/*for(i = 0; i < size; i += 5)
		printf("%d %d %d %d %d\n", a[i], a[i+ 1],a[i+ 2],a[i+ 3],a[i+ 4]); */
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

void insertionSort(int a[], int n)
{
	/* sort a[l:n] into nondecreasing order */
	int j;
	int temp;
	for (j = 1; j < n; j++) {
		temp= a[j];
		insert(temp, a, j-1);
	}
}

void insert(int e, int a[], int i)
{
	/* insert e into the ordered list a[l:i] such that the
	resulting list a[l:i+l] is also ordered, the array a
	must have space allocated for at least i+2 elements */
	while (a[i] > e) {
		a[i+1] = a[i];
		i--;
	}
	a[i+1] = e;
}

void quickSort(int a[], int left, int right)
{
	/* sort a[left:right] into nondecreasing order on the key field; a[left].key is arbitrarily
	chosen as the pivot key; it is assumed that a[left].key <= a[right+l].key */
	int pivot,i,j;
	int temp;
	if (left < right) {
		i = left; j = right + 1;
		pivot = a[left];
		do {/* search for keys from the left and right sublists,
			swapping out-of-order elements until the left and right boundaries cross or meet */
			do { i++; } while (a[i]< pivot);
			do { j--; } while (pivot<a[j]);
			if (i < j) SWAP(a[i],a[j],temp);
		} while ( i < j) ;
		SWAP(a[left],a[j],temp);
		quickSort(a,left,j-1);
		quickSort(a,j+1,right);
	}
}void quickSort_median(int a[], int left, int right)
{
	/* sort a[left:right] into nondecreasing order on the key field; a[left].key is arbitrarily
	chosen as the pivot key; it is assumed that a[left].key <= a[right+l].key */
	int pivot,i,j;
	int temp;
	int middle;
	int midd_index;
	
	middle = (left + right) / 2;
	
	if (left < right) {
		
		midd_index = getMiddle(a, left, middle, right);
		pivot = a[midd_index];
		SWAP(a[left], a[midd_index], temp);

		i = left; j = right + 1;
		do {/* search for keys from the left and right sublists,
			swapping out-of-order elements until the left and right boundaries cross or meet */
			do { i++; } while (a[i]< pivot);
			do { j--; } while (pivot<a[j]);
			if (i < j) SWAP(a[i],a[j],temp);
		} while ( i < j) ;
		SWAP(a[left],a[j],temp);
		quickSort(a,left,j-1);
		quickSort(a,j+1,right);
	}
}int getMiddle(int a[], int left, int middle, int right){	int midd = MIDD(a[left], a[middle], a[right]);		if(midd == a[left])		return left;	else if(midd == a[middle])		return middle;	else		return right;}