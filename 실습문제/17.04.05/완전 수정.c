#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define MAX_STACK 100
#define FALSE 0
#define TRUE 1

typedef struct node *nodePointer;
typedef struct node{

	int data;
	nodePointer link;
};

nodePointer x = NULL;
int stack[MAX_STACK];


void main(void)
{
	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer current, next, top;
	int i, j, class_anchor, n;
	
	printf("Enter the size (<= %d) ", MAX_SIZE);
	scanf("%d", &n);
	
	for (i = 0; i < n; i++) {
		/* initialize seq and out */
		out[i] = TRUE; seq[i] = NULL;
	}
	/* Phase 1: Input the equivalence pairs: */
	
	while (1) {
		printf("Enter a pair of numbers (-1 -1 to quit): ");
		scanf("%d%d", &i, &j);
		
		if (i < 0) break;
		
		x = (struct node *)malloc(sizeof(x));
		x->data = j;
		x->link = seq[i];
		seq[i] = x;
		

		x = (struct node *)malloc(sizeof(x));
		x->data = i;
		x->link = seq[j];
		seq[j] = x;
	}
	/* Phase 2: output the equivalence classes */
	for (i = 0; i < n; i++) {
		if (out[i]) {
			printf("\nNew class: %5d", i);
			out[i] = FALSE; /* set class to false */
			top = NULL; /*initialize stack*/
			class_anchor = i;
			while (1) { /* find rest of the class */
						/* class_anchor의 list를 처리한다 */
				current = seq[class_anchor];
				while (current) {
					j = current->data;
					if (out[j]) {
						printf("%5d", j);
						out[j] = FALSE;
						/* push node current onto the stack */
						
						next = current->link;
						current->link = top;
						top = current;
						current = next;
						

					}
					else
						current = current->link;	
				}
				if (top == NULL) break;
				class_anchor = top->data;
				top = top->link; /* pop*/
			}
		}
	}
	printf("\n");
}





//#include <stdio.h>
//#include <stdlib.h>
//#define MAX_SIZE 24
//#define MAX_STACK 100
//#define FALSE 0
//#define TRUE 1
//
//typedef struct node *nodePointer;
//typedef struct node{
//
//	int data;
//	nodePointer link;
//};
//
//nodePointer x = NULL;
//int stack[MAX_STACK];
//int top = -1;
//
//
//void push(int value);
//int pop();
//
//void main(void)
//{
//	short int out[MAX_SIZE];
//	nodePointer seq[MAX_SIZE];
//	nodePointer current, next;
//	int i, j, class_anchor, n;
//	
//	printf("Enter the size (<= %d) ", MAX_SIZE);
//	scanf("%d", &n);
//	
//	for (i = 0; i < n; i++) {
//		/* initialize seq and out */
//		out[i] = TRUE; seq[i] = NULL;
//	}
//	/* Phase 1: Input the equivalence pairs: */
//	
//	while (1) {
//		printf("Enter a pair of numbers (-1 -1 to quit): ");
//		scanf("%d%d", &i, &j);
//		
//		if (i < 0) break;
//		
//		x = (struct node *)malloc(sizeof(x));
//		x->data = j;
//		x->link = seq[i];
//		seq[i] = x;
//		
//
//		x = (struct node *)malloc(sizeof(x));
//
//		x->data = i;
//		x->link = seq[j];
//		seq[j] = x;
//	}
//	/* Phase 2: output the equivalence classes */
//	for (i = 0; i < n; i++) {
//		if (out[i]) {
//			printf("\nNew class: %5d", i);
//			out[i] = FALSE; /* set class to false */
//			top = -1; /*initialize stack*/
//			class_anchor = i;
//			while (1) { /* find rest of the class */
//						/* class_anchor의 list를 처리한다 */
//				current = seq[class_anchor];
//				while (current) {
//					j = current->data;
//					if (out[j]) {
//						printf("%5d", j);
//						out[j] = FALSE;
//						/* push node current onto the stack */
//						
//						/*next = current->link;
//						current->link = top;
//						top = current;
//						current = next;*/
//						
//						push(current->data);
//						current = current->link;
//						
//
//					}
//					else
//						current = current->link;
//				}
//				if (top == -1) break;
//				class_anchor = pop();
//				//class_anchor = top->data;
//				//top = top->link; /* pop*/
//			}
//		}
//	}
//
//	printf("\n");
//
//}


void push(int value) 
{
	++top;
	stack[top] = value; 
}

int pop()
{ 
	return stack[top--]; 
}