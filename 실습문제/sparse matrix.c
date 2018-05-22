#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N 36

typedef struct {
	int row;
	int col;
	int value;
} matrix;

matrix a[N], b[N];
matrix tran_b[N];
matrix mult[N];


void readMatrix();
void fastTranspose(matrix b[], matrix tran_b[]);
void printMatrix(matrix mat[]);
int compare(int x, int y);
void mmult(matrix a[], matrix b[], matrix d[]);
void storeSum(matrix d[], int *totalD, int row, int column, int *sum);

int main()
{
	
	readMatrix();

	fastTranspose(b, tran_b);

	printMatrix(a);
	printMatrix(b);
	printMatrix(tran_b);

	mmult(a, b, mult);
	printMatrix(mult);

	return 0;
}

void readMatrix()
{
	int i;
	int r, c, v;
	int buff;

	printf("Sparse Matrix를 입력하세요. (6x6)\n");
	printf("행렬 A : \n");

	printf("A의 0이 아닌 원소의 수를 입력하시오 : ");
	scanf("%d", &v);
	a[0].col = a[0].row = N;
	a[0].value = v;
	i = 1;
	while (1)
	{
		printf("원소가 0이 아닌 행, 열을 입력하세요.\n");
		printf("행 : ");
		scanf("%d", &r);
		printf("열 : ");
		scanf("%d", &c);
		printf("값 : ");
		scanf("%d", &v);
		printf("\n");
		a[i].row = r;
		a[i].col = c;
		a[i].value = v;
		i++;

		if (i == a[0].value + 1)
			break;
		
	}

	printf("행렬 B : \n");
	
	printf("B의 0이 아닌 원소의 수를 입력하시오 : ");
	scanf("%d", &v);
	b[0].col = b[0].row = N;
	b[0].value = v;

	i = 1;
	while (1)
	{
		printf("원소가 0이 아닌 행, 열을 입력하세요.\n");
		printf("행 : ");
		scanf("%d", &r);
		printf("열 : ");
		scanf("%d", &c);
		printf("값 : ");
		scanf("%d", &v);
		printf("\n");
		b[i].row = r;
		b[i].col = c;
		b[i].value = v;
		i++;

		if (i == b[0].value + 1)
			break;
	}
}

void fastTranspose(matrix b[], matrix tran_b[])
{
	int rowTerms[N], startingPos[N];
	int i, j;
	int numTerms = b[0].value;
	int numCols;
	numCols = tran_b[0].row = b[0].col;
	tran_b[0].col = b[0].row;
	tran_b[0].value = numTerms;

	if (numTerms > 0)
	{
		for (i = 0; i < numCols; i++)
			rowTerms[i] = 0;

		for (i = 1; i <= numTerms; i++)
			rowTerms[b[i].col]++;

		startingPos[0] = 1;

		for (i = 1; i < numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

		for (i = 1; i <= numTerms; i++)
		{
			j = startingPos[b[i].col]++;

			tran_b[j].col = b[i].row;
			tran_b[j].row = b[i].col;
			tran_b[j].value = b[i].value;
		}
	}
}

void printMatrix(matrix mat[])
{
	int i;

	for (i = 1; i <= mat[0].value; i++)
			printf("%2d %2d %3d\n", mat[i].row, mat[i].col, mat[i].value);
	printf("\n");

}

void mmult(matrix a[], matrix b[], matrix d[])
{/* multiply two sparse matrices */
	int i, j, d_column, totalB = b[0].value, totalD = 0;
	int rowsA = a[0].row, colsA = a[0].col, totalA = a[0].value;
	int colsB = b[0].col;
	int rowBegin = 1, d_row = a[1].row, sum = 0;
	matrix newB[N];
	if (colsA != b[0].row) {
		fprintf(stderr, "Incompatible matrices\n");
		exit(EXIT_FAILURE);
	}
	fastTranspose(b, newB);
	/* set boundary condition */
	a[totalA + 1].row = rowsA;
	newB[totalB + 1].row = colsB;
	newB[totalB + 1].col = 0;
	for (i = 1; i <= totalA; ) {
		d_column = newB[1].row;
		sum = 0;
		for (j = 1; j <= totalB + 1;) {
			/* multiply row of a by column of b */
			if (a[i].row != d_row) {
				storeSum(d, &totalD, d_row, d_column, &sum);
				i = rowBegin;
				for (; newB[j].row == d_column; j++);
				d_column = newB[j].row;
			}
			else if (newB[j].row != d_column) {
				storeSum(d, &totalD, d_row, d_column, &sum);
				i = rowBegin;
				d_column = newB[j].row;
			}
			else {
				switch (compare(a[i].col, newB[j].col)) {
				case -1: /* go to next term in a */
					i++; break;
				case 0: /* add terms, go to next term in a and b*/
					sum += (a[i++].value* newB[j++].value);
					break;
				case 1: /* advance to next term in b */
					j++;
				}
			}
		}
		for (; a[i].row == d_row; i++);
		rowBegin = i; d_row = a[i].row;
	} /* end of for i<=totalA */
	d[0].row = rowsA; d[0].col = colsB; d[0].value = totalD;
}

void storeSum(matrix d[], int *totalD, int row, int column, int *sum)
{/* if *sum != 0, then it along with its row and column
 position is stored as the *totalD+l entry in d */
	if (*sum) {
		if (*totalD < N) {
			d[++*totalD].row = row;
			d[*totalD].col = column;
			d[*totalD].value = *sum;
			*sum = 0;
		}
		else {
			fprintf(stderr, "Numbers of terms in product exceeds %d \n",
				N);
			exit(EXIT_FAILURE);
		}
	}
}

int compare(int x, int y)
{
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}