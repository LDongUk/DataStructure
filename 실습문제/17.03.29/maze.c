#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define EXIT_ROW1 12
#define EXIT_COL1 15
#define EXIT_ROW2 7
#define EXIT_COL2 7

typedef struct {
	int row;
	int col;
	int dir;
} element;

typedef struct {
	int vert;
	int horiz;
} offset;



element stack[MAX_STACK_SIZE];
element stack2[MAX_STACK_SIZE];
offset move[8];

int top = -1;
int top2 = -1;
int mark1[14][17];
int mark2[9][9];
int maze1[14][17];
int maze2[9][9];

void initialize_move();
void push(element item); element pop(); void stackFull(); element stackEmpty();
void push2(element item); element pop2();
void path1(void);void path2(void);
int main()
{
	FILE *fp;
	char a;
	int i, j;


	initialize_move();

	//미로 입력1
	fp = fopen("maze1.txt", "r");
	
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 17; j++)
		{
			fscanf(fp, "%c", &a);
			if (a == '0')
				maze1[i][j] = 0;

			else
				maze1[i][j] = 1;
		}
		fscanf(fp, "%c", &a);
	}

	fclose(fp);

	//미로 입력2
	fp = fopen("maze2.txt", "r");

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			fscanf(fp, "%c", &a);
			if (a == '0')
				maze2[i][j] = 0;

			else
				maze2[i][j] = 1;
		}

		fscanf(fp, "%c", &a);
	}


	//미로 출력
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 17; j++)
			printf("%2d", maze1[i][j]);

		printf("\n");
	}
	printf("\n");
	path1();
	
	printf("\n\n");
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
			printf("%2d", maze1[i][j]);

		printf("\n");
	}
	printf("\n");
	path2();

	return 0;
}

void initialize_move()
{
	move[0].vert = -1; move[0].horiz = 0;
	move[1].vert = -1; move[1].horiz = 1;
	move[2].vert = 0; move[2].horiz = 1;
	move[3].vert = 1; move[3].horiz = 1;
	move[4].vert = 1; move[4].horiz = 0;
	move[5].vert = 1; move[5].horiz = -1;
	move[6].vert = 0; move[6].horiz = -1;
	move[7].vert = -1; move[7].horiz = -1;

}

void push(element item)
{

	if (top >= MAX_STACK_SIZE - 1)
		stackFull();

	stack[++top] = item;

}

element pop()
{
	if (top == -1)
		return stackEmpty();

	return stack[top--];
}

void push2(element item)
{

	if (top2 >= MAX_STACK_SIZE - 1)
		stackFull();

	stack2[++top2] = item;

}

element pop2()
{
	if (top2 == -1)
		return stackEmpty();

	return stack2[top2--];
}

void stackFull()
{
	fprintf(stderr, "Stack is full, cannot add element");
	exit(EXIT_FAILURE);
}

element stackEmpty()
{
	fprintf(stderr, "Stack is empty, cannot delete element");
	exit(EXIT_FAILURE);
}


void path1(void)
{    /* output a path through the maze if such a path exists */
	int i, row, col, nextRow, nextCol, dir, found = 0;
	element position;
	mark1[1][1] = 1;

	// top = -1; position.row=1; position.col=1;  position.dir=1; push(position); 
	top = 0; stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (top >= 0 && !found) {
		

		position = pop();
		
		row = position.row; col = position.col;  dir = position.dir;
		while (dir < 8 && !found) {
			/* move in direction dir */

			//벽부분 수정!

			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW1 && nextCol == EXIT_COL1)
				found = 1;
			else if (!maze1[nextRow][nextCol] && !mark1[nextRow][nextCol]) {
				mark1[nextRow][nextCol] = 1;
				position.row = row; position.col = col; position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;



		}
	}


	if (found) {
		printf("The path is:\n");
		printf("row col\n");
		for (i = 0; i <= top; i++) printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW1, EXIT_COL1);
	}
	else
		printf("The maze does not have a path\n");
}

void path2(void)
{    /* output a path through the maze if such a path exists */
	int i, row, col, nextRow, nextCol, dir, found = 0;
	element position;
	mark2[1][1] = 1;

	// top = -1; position.row=1; position.col=1;  position.dir=1; push(position); 
	top2 = 0; stack2[0].row = 1; stack2[0].col = 1; stack2[0].dir = 1;
	while (top2 >= 0 && !found) {
		

		position = pop2();
		
		row = position.row; col = position.col;  dir = position.dir;
		while (dir < 8 && !found) {
			/* move in direction dir */

			//벽부분 수정!

			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW2 && nextCol == EXIT_COL2)
				found = 1;
			else if (!maze2[nextRow][nextCol] && !mark2[nextRow][nextCol]) {
				mark2[nextRow][nextCol] = 1;
				position.row = row; position.col = col; position.dir = ++dir;
				push2(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;



		}
	}


	if (found) {
		printf("The path is:\n");
		printf("row col\n");
		for (i = 0; i <= top2; i++) printf("%2d%5d\n", stack2[i].row, stack2[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW2, EXIT_COL2);
	}
	else
		printf("The maze does not have a path\n");
}