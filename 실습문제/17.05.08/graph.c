/*
	교수님이 자료에 만들어 놓은 Adjacency List는 잘못됨.
	0 -> 1 -> 2 순이 아니라
	0 -> 2 -> 1 순으로 , 가장처음에 입력한 노드가 가장 끝에 있어야 함.
	새로 해볼것.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_SIZE 30
#define FALSE 0
#define TRUE 1


typedef struct node *nodePointer;

typedef struct node{
	int vertex;
	nodePointer link;
};

nodePointer adjacencyList[MAX_VERTICES];
nodePointer stack[MAX_SIZE];
short visited[MAX_VERTICES];
int queue[MAX_SIZE];
int top = -1;
int front, rear;


void readGraph();
void printAdj();
void initialize_visited();
void dfs(int v);
void dfs_iter(int v);
void search();
void push(nodePointer item);
nodePointer pop();
void add_queue(int v);
int delete_queue();
void bfs(int v);
void process_vertex(int v);
void bfs_rec(int v);

int main()
{
	
	readGraph();
	printAdj();
	search();

	return 0;
}


void readGraph()
{
	int edge, vert1, vert2;
	int i;
	nodePointer v1, v2;


	printf("Graph를 입력하시오.\n");
	printf("(edge 번호 vertex 번호 vertex 번호) -1 -1 -1에 입력종료\n");

	for(i = 0; i < MAX_VERTICES; i++)
		adjacencyList[i] = NULL;
	
	while(1)
	{
		scanf("%d %d %d", &edge, &vert1, &vert2);

		if(edge == -1 && vert1 == -1 && vert2 == -1)
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

void initialize_visited()
{
	int x;
	for (x=0; x<MAX_VERTICES; x++)
		visited[x] = FALSE;
}

/* depth first search of a graph beginning at vertex v */
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

/* depth first search of a graph beginning at vertex v */
void dfs_iter(int v)
{
	int i;
	nodePointer x;

	for(x = adjacencyList[v]; x!= NULL; x = x->link)
		push(x);

	printf("%d, ", v);
	visited[v] = TRUE;

	while(1)
	{
		v = pop()->vertex;

		if(visited[v] == FALSE)
		{
			printf("%d, ", v);

			visited[v] = TRUE;

			for(x = adjacencyList[v]; x!= NULL; x = x->link)
				push(x);
		}

		
		if(top == -1)
			break;
	}


	
	printf("\b\b \n");
}

void search()
{
	int v;

	printf("Starting vertex의 number를 입력하시오: ");
	scanf("%d", &v);

	initialize_visited();
	printf("DFS(recursive version)의 결과: ");
	dfs(v);
	printf("\b\b \n");

	initialize_visited();
	printf("DFS(iterative version)의 결과: ");
	dfs_iter(v);
	
	initialize_visited();
	printf("BFS(iterative version)의 결과: ");
	bfs(v);
	printf("\b\b \n");

	initialize_visited();
	printf("BFS(recursive version)의 결과: ");
	bfs_rec(v);
	printf("\b\b \n");

}

void push(nodePointer item)
{
	if(top == MAX_SIZE)
	{
		fprintf(stderr,"STACK IS FULL");
		exit(EXIT_FAILURE);
	}
	
	stack[++top] = item;
}

nodePointer pop()
{
	if(top == -1)
	{
		fprintf(stderr,"STACK IS EMPTY");
		exit(EXIT_FAILURE);
	}
	return stack[top--];
}


void process_vertex(int v)
{
	printf("%d, ", v);
	visited[v] = TRUE;
	add_queue(v);
}
/* breath first search of a graph beginning at vertex v */
void bfs(int v)
{
	nodePointer search;
	front = rear = 0;
	process_vertex(v);
	while (rear != front) {
		v = delete_queue () ;
		for (search = adjacencyList[v]; search; search = search->link) {
			if (!visited[search->vertex])
				process_vertex(search->vertex);
		}
	}
}

void add_queue(int v)
{
	rear = (rear + 1) % MAX_SIZE;

	if(front == rear)
	{
		fprintf(stderr,"QUEUE IS FULL");
		exit(EXIT_FAILURE);
	}

	queue[rear] = v;
}

int delete_queue()
{
	/* remove front element from the queue */
	if (front == rear)
	{
		fprintf(stderr,"QUEUE IS EMPTY");
		exit(EXIT_FAILURE);
	}
	front = (front+1) % MAX_SIZE;
	return queue[front];
}

void bfs_rec(int v)
{
	nodePointer x;

	if(visited[v] == FALSE)
	{
		printf("%d, ", v);
		visited[v] = TRUE;
		for(x = adjacencyList[v]; x != NULL; x = x->link)
			add_queue(x->vertex);

		v = delete_queue();

		bfs_rec(v);
	}

	else
	{
		if(front == rear)
			return;

		v = delete_queue();
		bfs_rec(v);
	}

}
/*
0 0 1
1 1 2
2 1 3
3 2 4
4 3 4
5 3 5
6 5 6
7 5 7
8 6 7
9 7 8
10 7 9
-1 -1 -1
*/