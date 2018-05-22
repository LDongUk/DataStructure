#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 15 /* maximum size of square */
void main(void)
{
	/*construct a magic square, iteratively */
		int square[MAX_SIZE][MAX_SIZE];
	int i, j, row, column; /* indexes */
	int count; /* counter */
	int size; /* square size */
	int sum;



	printf("Enter the size of the square: ");
	scanf("%d", &size);
	/* check for input errors */
	if (size < 1 || size > MAX_SIZE + 1) {
		fprintf(stderr, "Error! Size is out of range \ n");
		exit(EXIT_FAILURE);
	}
	if (!(size % 2)) {
		fprintf(stderr, "Error! Size is even\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			square[i][j] = 0;
	square[0][(size - 1) / 2] = 1; /*middle of first row*/



	//홀수 마방진 공식
	i = 0;
	j = (size - 1) / 2;

	for (count = 2; count <= size * size; count++)
	{
		row = (i - 1 < 0) ? size - 1 : i - 1;
		column = (j + 1 == size) ? 0 : j + 1;

		if (square[row][column] == 0)
		{
			square[row][column] = count;
			i = row;
			j = column;
		}
		else
		{
			square[i + 1][j] = count;
			i = i + 1;
		}
	}



	/* output the magic square */
	printf(" Magic Square of size %d : \n\n", size);
	for (i = 0; i < size; i++) {
		sum = 0;
		for (j = 0; j < size; j++)
		{
			sum = sum + square[i][j];
			printf("%5d", square[i][j]);
		}
		printf("\t\t%3d", sum);
		printf("\n");
	}
	printf("\n\n");
}