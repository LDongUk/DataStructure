#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_SIZE 30
#define FALSE 0
#define TRUE 1
#define MIN2 (x, y) ((x) < (y) ? (x) : (y))

typedef struct node *nodePointer;

typedef struct node{
	int vertex;
	nodePointer link;
};

typedef struct{
	int me;
	int child;
}st;

nodePointer adjacencyList[MAX_VERTICES];
st stack[MAX_SIZE];
short visited[MAX_VERTICES];
int queue[MAX_SIZE];
int top = -1;
int front, rear;
short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
int num;

void readGraph();
void printAdj();
void init();
void dfnlow(int me, int parent);
void bicon(int me, int parent);
void push(int me, int child);
void pop(int *x, int *y);
void dfnlow_print();
void added_edge();

void dfs(int v);

int main()
{
	int i;
	readGraph();
	printAdj();
	
	//dfs(3);

	dfnlow_print();

	init();
	bicon(3, -1);

	printf("\n\n");
	added_edge();
	printAdj();
	dfnlow_print();

	init();
	bicon(3, -1);

	return 0;
}

void dfs(int v)
{
	nodePointer search;
	visited[v] = TRUE;
	printf("%d, ",v);
	for (search = adjacencyList[v]; search; search = search->link) {
		if ( !visited[search->vertex])
			dfs(search->vertex);
	}
}

void added_edge()
{
	int i;
	nodePointer v1, v2;

	printf("edge (0,2), (6,9)를 마지막에 추가합니다.\n\n");

	v1 = (struct node*)malloc(sizeof(struct node));
	v1->vertex = 2;
	v1->link = NULL;

	if(adjacencyList[0] == NULL)
		adjacencyList[0] = v1;			

	else
	{
		for(v2 = adjacencyList[0]; v2->link != NULL; v2 = v2->link);

		v2->link = v1;

	}

	v1 = (struct node*)malloc(sizeof(struct node));
	v1->vertex = 0;
	v1->link = NULL;

	if(adjacencyList[2] == NULL)
		adjacencyList[2] = v1;			

	else
	{
		for(v2 = adjacencyList[2]; v2->link != NULL; v2 = v2->link);

		v2->link = v1;
	}

	v1 = (struct node*)malloc(sizeof(struct node));
	v1->vertex = 9;
	v1->link = NULL;

	if(adjacencyList[6] == NULL)
		adjacencyList[6] = v1;			

	else
	{
		for(v2 = adjacencyList[6]; v2->link != NULL; v2 = v2->link);

		v2->link = v1;

	}

	v1 = (struct node*)malloc(sizeof(struct node));
	v1->vertex = 6;
	v1->link = NULL;

	if(adjacencyList[9] == NULL)
		adjacencyList[9] = v1;			

	else
	{
		for(v2 = adjacencyList[9]; v2->link != NULL; v2 = v2->link);

		v2->link = v1;
	}


}

void dfnlow_print()
{
	int i;

	init();
	dfnlow(3,-1);
	printf("\n");

	printf("%7s : ", "Vertex");
	for(i = 0; i < MAX_VERTICES; i++)
		printf("%3d", i);
	printf("\n");

	printf("%7s : ", "Dfs");
	for(i = 0; i < MAX_VERTICES; i++)
		printf("%3d", dfn[i]);
	printf("\n");

	printf("%7s : ", "Low");
	for(i = 0; i < MAX_VERTICES; i++)
		printf("%3d", low[i]);
	printf("\n");

	printf("\n");
}

void bicon(int me, int parent)
{
	/* compute dfn and low, and output the edges of G by their
	biconnected components, v is the parent (if any) of u
	in the resulting spanning tree. It is assumed that all
	entries of dfn[] have been initialized to -1, num is
	initially to 0, and the stack is initially empty */
	nodePointer ptr;
	int child,x,y;
	dfn[me] = low[me] = num++;
	for (ptr = adjacencyList[me]; ptr; ptr = ptr->link) {
		child = ptr->vertex;
		if (parent != child && dfn[child] < dfn[me]) {// 이 부분이 교재의 오류
			// either an edge to an unvisited vertex or a back-edge
			push(me,child); /*add edge to stack*/
		}
		if (dfn[child] <0) { /* child has not been visited */
			bicon (child, me);
			low[me] = (low[me] < low[child]) ? low[me] : low[child];
			if (low[child] >= dfn[me]) {
				printf("New biconnected component: ");
				do { /* delete edge from stack */
					pop(&x, &y);
					printf(" <%d,%d>",x,y);
				} while (! ((x == me) && (y == child)));
				printf("\n");
			}
		} else if (child != parent) // a back-edge is found
			low[me] = (low[me] < dfn[child]) ? low[me] : dfn[child];
	}
}

void readGraph()
{
	int edge, vert1, vert2;
	int i;
	nodePointer v1, v2;


	for(i = 0; i < MAX_VERTICES; i++)
		adjacencyList[i] = NULL;	
	printf("Graph를 입력하시오.\n");
	printf("(vertex 번호 vertex 번호) -1 -1에 입력종료\n");

	while(1)
	{

		scanf("%d %d", &vert1, &vert2);

		if(vert1 == -1 && vert2 == -1)
			break;


		v1 = (struct node*)malloc(sizeof(struct node));
		v1->vertex = vert2;
		v1->link = NULL;

		if(adjacencyList[vert1] == NULL)
			adjacencyList[vert1] = v1;			

		else
		{
			for(v2 = adjacencyList[vert1]; v2->link != NULL; v2 = v2->link);

			v2->link = v1;
			/*v2 = (struct node*)malloc(sizeof(struct node));
			v2 = adjacencyList[vert1];
			v1->link = v2;
			adjacencyList[vert1] = v1;*/
		}

		v1 = (struct node*)malloc(sizeof(struct node));
		v1->vertex = vert1;
		v1->link = NULL;

		if(adjacencyList[vert2] == NULL)
			adjacencyList[vert2] = v1;			

		else
		{
			for(v2 = adjacencyList[vert2]; v2->link != NULL; v2 = v2->link);

			v2->link = v1;
			/*v2 = (struct node*)malloc(sizeof(struct node));
			v2 = adjacencyList[vert2];
			v1->link = v2;
			adjacencyList[vert2] = v1;*/
		}

	}
	
	printf("\n");
}

void printAdj()
{
	int i, j;
	nodePointer x;

	printf("출력 형태: Vertex(Adjacent vertex list)\n");

	for(i = 0; i < MAX_VERTICES; i++)
	{
		if(adjacencyList[i] == NULL)
			break;

		printf("%d ", i);
		printf("(");
		for(x = adjacencyList[i]; x != NULL; x = x->link)
			printf("%d,", x->vertex);

		printf("\b)\n");
	}
}

void dfnlow(int me, int parent)
{
	/* compute dfn and low while performing a dfs search
	beginning at vertex me. parent is the parent of me (if any) */
	nodePointer ptr;
	int child;
	dfn[me] = low[me] = num++;
	for (ptr = adjacencyList[me]; ptr; ptr = ptr->link) {
		child = ptr->vertex;
		if (dfn[child] < 0) {/* child is an unvisited vertex */
			dfnlow(child, me);
			low[me] = (low[me] <low[child]) ? low[me] : low[child];
		}
		else if (child != parent) // a back-edge is found
			low[me] = (low[me] < dfn[child]) ? low[me] : dfn[child];
	}
}
void init(void)
{
	int i;
	for (i = 0; i < MAX_VERTICES; i++) {
		visited[i] = FALSE;
		dfn[i] = low[i] = -1;
	}
	num = 0;
}

void push(int me, int child)
{
	if(top == MAX_SIZE)
	{
		fprintf(stderr,"STACK IS FULL");
		exit(EXIT_FAILURE);
	}
	
	stack[++top].me = me;
	stack[top].child = child;
}

void pop(int *x, int *y)
{
	if(top == -1)
	{
		fprintf(stderr,"STACK IS EMPTY");
		exit(EXIT_FAILURE);
	}
	*x = stack[top].me;
	*y = stack[top--].child;
}



/*
0 1
1 2
2 4
3 4
3 1
3 5
5 6
5 7
6 7
7 9
7 8
-1 -1
*/