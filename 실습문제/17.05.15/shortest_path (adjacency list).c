#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//#define MAX_VERTICES 6
#define MAX_VERTICES 8
/*
0 1 50
0 3 10
0 2 45
1 2 10
1 3 15
2 4 30
3 0 20
3 4 15
4 1 20
4 2 35
5 4 3
-1 -1 -1
*/

/*
1 0 300
2 1 800
2 0 1000
3 2 1200
4 3 1500
4 5 250
5 3 1000
5 7 1400
5 6 900
6 7 1000
7 0 1700
-1 -1 -1
*/


#define FALSE 0
#define TRUE 1


typedef struct node *nodePointer;
typedef struct node{
	int vert;
	int cost;
	nodePointer next;
};

nodePointer cost[MAX_VERTICES];
int distance[MAX_VERTICES]; // distance[x] represents the distance of the shortest path from vertex start_vertex to x
int parent[MAX_VERTICES];
short found[MAX_VERTICES]; // found[x] is 0 if the shortest path from vertex start_vertex to x has not been found and a 1 if it has
int total_vertex_count;
short count[MAX_VERTICES];

void shortestPath(int start_vertex);
int choose_min_distance_vertex();
void update_distance_parent(int new_vertex);
void print_parent_child(int start_vertex);
void find_shortest_path(int start_vertex);
void scanList();


int main()
{
	int n;
	total_vertex_count = MAX_VERTICES;
	
	scanList();

	printf("Start Vertex : ");
	scanf("%d", &n);

	shortestPath(n);
	print_parent_child(n);
	find_shortest_path(n);

	return 0;
}


void scanList()
{
	int start_vert, end_vert, cost_edge;
	nodePointer x, y;
	printf("그래프를 입력합니다.\n");
	printf("Start Vertex, End Vertex, Cost 순으로 입력하시오 (종료 : -1 -1 -1) :\n");
	
	while(1)
	{
		scanf("%d %d %d", &start_vert, &end_vert, &cost_edge);

		if(start_vert == -1 && end_vert == -1 && cost_edge == -1)
			break;

		x = (struct node*)malloc(sizeof(struct node));
		x->vert = end_vert;
		x->cost = cost_edge;
		x->next = NULL;

		if(cost[start_vert] == NULL)
			cost[start_vert] = x;

		else
		{
			for(y = cost[start_vert]; y->next != NULL; y = y->next);
			y->next = x;
		}

	}

}


void shortestPath(int start_vertex)
{
	int x, new_vertex;
	int i;
	nodePointer p;

	
	for(i = 0; i < MAX_VERTICES; i++)
			count[i] = 0;

	for (x = 0; x < total_vertex_count; x++) {
		found[x] = FALSE;

		for(p = cost[start_vertex]; p != NULL; p = p->next)
		{
			if(p->vert == x)
			{
				distance[x] = p->cost;
				count[p->vert] = 1;
			}
		}
		parent[x] = start_vertex;
	}

	for(i = 0; i < MAX_VERTICES; i++)
	{
		if(i == start_vertex)
			distance[i] = 0;

		else if(count[i] == 0)
			distance[i] = 9999;
	}

	found[start_vertex] = TRUE;
	distance[start_vertex] = 0;
	for (x = 0; x < total_vertex_count - 1; x++) {
		new_vertex = choose_min_distance_vertex();
		found[new_vertex] = TRUE;

		if(MAX_VERTICES == 6 && x == 4)
			continue;

		for (i = 0; i < MAX_VERTICES; i++)
			printf("%-10d", distance[i]);

		printf("<= edge (%d, %d) : weight = %d\n", parent[new_vertex], new_vertex, distance[new_vertex]);

		update_distance_parent(new_vertex);
	}
}

int choose_min_distance_vertex()
{
	/* find the smallest distance not yet checked */
	int x, min, minpos;
	min = 0;

	for(x = 0; x < MAX_VERTICES; x++)
	{
		if(distance[x] > min && distance[x] != 9999)
			min = distance[x];
	}
	minpos = -1;
	for (x = 0; x < total_vertex_count; x++) {
		if (!found[x] && distance[x] <= min) {
			min = distance[x];
			minpos = x;
		}
	}
	return minpos;
}

void update_distance_parent(int new_vertex)
{
	int x;
	int k;
	int new_distance;
	nodePointer search;
	for (x = 0; x < total_vertex_count; x++) {
		if (!found[x]) {

			for(search = cost[new_vertex]; search != NULL; search = search->next)
			{
				if(search->vert == x)
				{
					new_distance = distance[new_vertex] + search->cost;
					if (new_distance < distance[x]) {
						distance[x] = new_distance;
						parent[x] = new_vertex;
					}
				}
			}

		}
	}
}

void print_parent_child(int start_vertex)
{
	int i;

	printf("parent\t\t");
	for (i = 0; i < MAX_VERTICES; i++)
	{
		if (found[i] != 0)
		{
			if (i == start_vertex)
			{
				parent[i] = -1;
				printf("%3d\t", parent[i]);
			}
			else
				printf("%3d\t", parent[i]);
		}

		else
		{
			parent[i] = -1;
			printf("%3d\t", parent[i]);
		}
	}

	printf("\n");
	printf("child\t\t");
	for (i = 0; i < MAX_VERTICES; i++)
		printf("%3d\t", i);
	printf("\n");
}

void find_shortest_path(int start_vertex)
{
	int i, j;
	int min, min_pos;
	int c;
	int count_parent_true = 0;

	for (i = 0; i < MAX_VERTICES; i++)
	{
		if (parent[i] != -1)
			count_parent_true++;
	}
	
	for(j = 0; j < count_parent_true; j++)
	{
		min = 9999;
		for (i = 0; i < MAX_VERTICES; i++)
		{
			if (distance[i] < min && parent[i] != -1)
			{
				min = distance[i];
				min_pos = i;
			}
		}

		if (min == INT_MAX)
			break;

		printf("length = %d\t\t", min);
		printf("path : ");
		c = min_pos;
		while (c != -1)
		{
			printf("%-8d", c);
			c = parent[c];
		}


		distance[min_pos] = 9999;

		printf("\n");
	}
}
