#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

typedef double element;

typedef struct stackNode 
{			
	element data; 
	struct stackNode *link; 
}stackNode; 

stackNode* top;