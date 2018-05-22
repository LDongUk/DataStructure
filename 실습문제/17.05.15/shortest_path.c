#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 6
#define FALSE 0
#define TRUE 1
#define INT_MAX 50

int cost[MAX_VERTICES][MAX_VERTICES] = {{ 0, 50, 45, 10, 9999, 9999 },
										{ 9999, 0, 10, 15, 9999, 9999 },
										{ 9999, 9999, 0, 9999, 30, 9999 },
										{ 20, 9999, 9999, 0, 15, 9999 },
										{ 9999, 20, 35, 9999, 0, 9999 },
										{ 9999, 9999, 9999, 9999, 3, 9999 }};
// cost is the adjacency matrix

int distance[MAX_VERTICES]; // distance[x] represents the distance of the shortest path from vertex start_vertex to x
int parent[MAX_VERTICES];
short found[MAX_VERTICES]; // found[x] is 0 if the shortest path from vertex start_vertex to x has not been found and a 1 if it has
int total_vertex_count;

void shortestPath(int start_vertex);
int choose_min_distance_vertex();
void update_distance_parent(int new_vertex);
void print_parent_child(int start_vertex);
void find_shortest_path(int start_vertex);

int main()
{
	total_vertex_count = MAX_VERTICES;
	shortestPath(0);
	print_parent_child(0);
	find_shortest_path(0);

	return 0;
}



void shortestPath(int start_vertex)
{
	int x, new_vertex;
	int i;
	for (x = 0; x < total_vertex_count; x++) {
		found[x] = FALSE;
		distance[x] = cost[start_vertex][x]; parent[x] = start_vertex;
	}
	found[start_vertex] = TRUE;
	distance[start_vertex] = 0;
	for (x = 0; x < total_vertex_count - 2; x++) {
		new_vertex = choose_min_distance_vertex();
		found[new_vertex] = TRUE;

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
	min = INT_MAX;
	minpos = -1;
	for (x = 0; x < total_vertex_count; x++) {
		if (!found[x] && distance[x] < min) {
			min = distance[x];
			minpos = x;
		}
	}
	return minpos;
}void update_distance_parent(int new_vertex)
{
	int x;
	int new_distance;
	for (x = 0; x < total_vertex_count; x++) {
		if (!found[x]) {
			new_distance = distance[new_vertex] + cost[new_vertex][x];
			if (new_distance < distance[x]) {
				distance[x] = new_distance;
				parent[x] = new_vertex;
			}
		}
	}
}void print_parent_child(int start_vertex){	int i;	printf("parent\t\t");	for (i = 0; i < MAX_VERTICES; i++)	{		if (found[i] != 0)		{			if (i == start_vertex)			{				parent[i] = -1;				printf("%3d\t", parent[i]);			}			else				printf("%3d\t", parent[i]);		}		else		{			parent[i] = -1;			printf("%3d\t", parent[i]);		}	}	printf("\n");	printf("child\t\t");	for (i = 0; i < MAX_VERTICES; i++)		printf("%3d\t", i);	printf("\n");}void find_shortest_path(int start_vertex){	int i, j;	int min, min_pos;	int c;	int count_parent_true = 0;	for (i = 0; i < MAX_VERTICES; i++)	{		if (parent[i] != -1)			count_parent_true++;	}	min = 9999;	for(j = 0; j < count_parent_true; j++)	{		min = 9999;		for (i = 0; i < MAX_VERTICES; i++)		{			if (distance[i] < min && parent[i] != -1)			{				min = distance[i];				min_pos = i;			}		}		if (min == INT_MAX)			break;		printf("length = %d\t\t", min);		printf("path : ");		c = min_pos;		while (c != -1)		{			printf("%-8d", c);			c = parent[c];		}		distance[min_pos] = INT_MAX;		printf("\n");	}}