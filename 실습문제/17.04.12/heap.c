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
	

	//���ڵ� �Է�

	printf("���� 9���� ���ڵ带 �Է��Ͻÿ�.\n");
	printf("7 ������ 16 ȫ�浿 49 ���� 82 ���� 5 �̼��� 31 ȫ�� 6 ���θ� 2 ������ 10 �޽�\n");
	printf("���ڵ� �Է� : ");
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


	//�� ���
	printf("\nMAX_HEAP ���===\n\n");
	for (i = 0; i < current_size + 1; i++)
		printf("%3d %5s\n", heap[i].stud_num, heap[i].name);
	

	//��Ʈ��� ����
	printf("\n��Ʈ��带 �����մϴ�.===\n\n");
	while (1)
	{
		printf("Root ����� ���ڵ带 �����ұ�� ? (y / n) :");
		scanf_s("%c", &flag, sizeof(char));

		
		
		if (flag == 'y' || flag == 'Y')
		{
			item = pop(&current_size);
			printf("<%d, \'%s\'>\n", item.stud_num, item.name);

			while ((buff = getchar()) != '\n' && buff != EOF); // ���ۺ���
		}
		else if(flag == 'n' || flag == 'N')
			break;

		else
		{
			while ((buff = getchar()) != '\n' && buff != EOF); // ���ۺ���
			continue;
		}
	}

	//�� ���
	printf("MAX_HEAP ���===\n\n");
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
	item = heap[1]; // heap[0]�� �ƴϰ� heap[1]�� root node�̴�.
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