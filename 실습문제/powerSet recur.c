#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char data[] = { 'a','b','c' };
int flag[] = { 0,0,0 };

void powerset(int n, int depth)
{
	if (n == depth) {
		int i;
		printf("{");
		for (i = 0; i<n; i++) {
			if (flag[i] == 1)printf("%c ", data[i]);
		}
		printf("}\n");
		return;
	}
	flag[depth] = 1;
	powerset(n, depth + 1);
	flag[depth] = 0;
	powerset(n, depth + 1);
}

int main()
{
	powerset(sizeof(data) / sizeof(char), 0);
	return 0;
}
