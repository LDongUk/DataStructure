#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 200 /* maximum heap size+l */
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)
typedef struct {
	int stud_num;
	char name[20];
	/* other fields */
} element;
element heap[MAX_ELEMENTS];
int current_size = 0;

void push(element item, int *current_size_ptr);
element pop(int *current_size_ptr);

int main()
{
	int i, j, k;
	char n;
	int buff;
	char flag;
	element item;
	

	//레코드 입력

	printf("다음 9개의 레코드를 입력하시오.\n");
	printf("7 일지매 16 홍길동 49 춘향 82 월매 5 이순신 31 홍명보 6 차두리 2 박지성 10 메시\n");
	printf("레코드 입력 : ");
	for(i = 0; i < 9; i++)	
	{
		scanf("%d", &item.stud_num);
		j = 0;
		getchar();

		for(k = 0; k < 20; k++)
				item.name[k] = '\0';

		while(1)
		{
			scanf("%c", &n);
			if(n == ' ' || n == '\n')
				break;

			item.name[j] = n;
			j++;
		}
		push(item, &current_size);
	}


	//힙 출력
	printf("\nMAX_HEAP 출력===\n\n");
	for (i = 0; i < current_size + 1; i++)
		printf("%3d %5s\n", heap[i].stud_num, heap[i].name);
	

	//루트노드 삭제
	printf("\n루트노드를 삭제합니다.===\n\n");
	while (1)
	{
		printf("Root 노드의 레코드를 삭제할까요 ? (y / n) :");
		scanf_s("%c", &flag, sizeof(char));

		
		
		if (flag == 'y' || flag == 'Y')
		{
			item = pop(&current_size);
			printf("<%d, \'%s\'>\n", item.stud_num, item.name);

			while ((buff = getchar()) != '\n' && buff != EOF); // 버퍼비우기
		}
		else if(flag == 'n' || flag == 'N')
			break;

		else
		{
			while ((buff = getchar()) != '\n' && buff != EOF); // 버퍼비우기
			continue;
		}
	}

	//힙 출력
	printf("MAX_HEAP 출력===\n\n");
	for (i = 0; i < current_size + 1; i++)
		printf("%3d %5s\n", heap[i].stud_num, heap[i].name);

	return 0;
}





/* insert item into a max heap of current size *current_size_ptr */
void push(element item, int *current_size_ptr)
{
	int i;
	if (HEAP_FULL(*current_size_ptr)) {
		fprintf(stderr, "The heap is full. \n");
		exit(EXIT_FAILURE);
	}
	i = ++(*current_size_ptr);
	while ((i != 1) && (item.stud_num > heap[i / 2].stud_num)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}/* delete element with the highest key from the heap */
element pop(int *current_size_ptr)
{
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*current_size_ptr)) {
		fprintf(stderr, "The heap is empty\n");
		exit(EXIT_FAILURE);
	}
	/* save value of the element with the highest key */
	item = heap[1]; // heap[0]이 아니고 heap[1]이 root node이다.
					/* use last element in heap to adjust heap */
	temp = heap[(*current_size_ptr)--];
	parent = 1;
	child = 2;
	while (child <= *current_size_ptr) {
		/* find the larger child of the current parent */
		if ((child < *current_size_ptr) && (heap[child].stud_num < heap[child + 1].stud_num)) child++;
		if (temp.stud_num >= heap[child].stud_num) break;
		/* move to the next lower level */
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}