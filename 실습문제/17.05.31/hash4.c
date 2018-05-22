#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct add *Pointer;

typedef struct{
	int value;
	char key_name[3];
} bucket;


struct add{
	bucket slot1;
	bucket slot2;
};

typedef struct{
	int ld;
	Pointer addressPointer;
}hash;

int gd = 2, size = 4;
hash *directory;


int char_to_num(char num);
int h(char key[]);
int h_getIndex(char key_input[], int p);
void initializeDR();
void copyDR();
void initialize_OneDR(int index);
void insertDR(char key_input[]);
void printDR();
void searchDR(char input_key[]);
void deleteDR(char input_key[]);

int main()
{
	int i;
	char input_key[3];

	directory = (hash*) malloc(sizeof(hash) * size);
	initializeDR();
	while(1)
	{
		printf("key를 입력하시오 (key = A0 B0 A1 B1 C2 C3 C5 C1 A4 B7 , 종료 <X, 0> : ");
		scanf("%s", input_key);

		if(input_key[0] == 'X' || input_key[0] == 'x')
			break;

		
		insertDR(input_key);


	}
	printf("=================================\n");
	printDR();
	printf("=================================\n");
	while (1)
	{
		printf("찾고싶은 key를 입력하시오 (key = A0~A7 or B0 ~ B7 or C0 ~ C7 , 종료 <X, 0> : ");
		scanf("%s", input_key);
		if (input_key[0] == 'X' || input_key[0] == 'x')
			break;

		searchDR(input_key);

	}

	while (1)
	{
		printf("삭제하고싶은 key를 입력하시오 (key = C3 C5 B1 A1 A4 C2 A0 B0 C1 A4 B7 , 종료 <X, 0> : ");
		scanf("%s", input_key);
		if (input_key[0] == 'X' || input_key[0] == 'x')
			break;

		deleteDR(input_key);
	}
	printDR();

	return 0;
}

int h(char key[])
{
	int key_char = 0x01;
	int key_num = 0x00;
	int count, i, j;

	if(key[0] == 'A')
	{
		key_char = key_char << 5;	
		count = char_to_num(key[1]);

		for(j = 0; j < count; j++)
			key_num += 0x01;

		return key_char + key_num;

	}

	else if(key[0] == 'B')
	{
		key_char = (key_char << 2) + 0x01;
		key_char = key_char << 3;
		count = char_to_num(key[1]);

		for(j = 0; j < count; j++)
			key_num += 0x01;

		return key_char + key_num;
	}

	else if(key[0] == 'C')
	{
		key_char = (key_char << 2) + (0x01 << 1);
		key_char = key_char << 3;
		count = char_to_num(key[1]);

		for(j = 0; j < count; j++)
			key_num += 0x01;

		return key_char + key_num;
	}
}

int char_to_num(char num)
{

	return num - '0';
}

int h_getIndex(char key_input[], int p)
{
	int h_k, count;
	int mask = 0x01;
	
	h_k = h(key_input);

	for(count = 1; count < p; count++)
		mask = (mask << 1) + (0x01);

	return h_k & mask;
}

void insertDR(char key_input[])
{
	int index, i;
	int new_index;
	int new_bucketValue;
	bucket temp[2];

	index = h_getIndex(key_input, gd);

	if(directory[index].addressPointer == directory[index - size/2].addressPointer)
	{
		directory[index].addressPointer = (struct add*)malloc(sizeof(struct add));
		initialize_OneDR(index);
	}

	if(index >= 4 && directory[index].ld ==2)
	{
		directory[index].addressPointer = (struct add*)malloc(sizeof(struct add));
		initialize_OneDR(index);
	}
	//bucket이 비었을 때
	if(directory[index].addressPointer->slot1.value == -1)
	{
		directory[index].addressPointer->slot1.value = h(key_input);
		sprintf(directory[index].addressPointer->slot1.key_name, "%s", key_input);
	}

	//bucket이 하나 찼을 때
	else if(directory[index].addressPointer->slot1.value != -1 && directory[index].addressPointer->slot2.value == -1)
	{
		directory[index].addressPointer->slot2.value = h(key_input);
		sprintf(directory[index].addressPointer->slot2.key_name, "%s", key_input);
	}
	//bucket이 다 찼을 때
	else if(gd == directory[index].ld && directory[index].addressPointer->slot1.value != -1 && directory[index].addressPointer->slot2.value != -1)
	{
		size *= 2;
		gd++;
		directory[index].ld++;
		directory = (hash*)realloc(directory, sizeof(hash) * size);
		copyDR();
		
		sprintf(temp[0].key_name, "%s", directory[index].addressPointer->slot1.key_name);
		temp[0].value = directory[index].addressPointer->slot1.value;

		sprintf(temp[1].key_name, "%s", directory[index].addressPointer->slot2.key_name);
		temp[1].value = directory[index].addressPointer->slot2.value;

		initialize_OneDR(index);


		for(i = 0; i < 2; i++)
		{
			new_index = h_getIndex(temp[i].key_name, gd);
			if(new_index >= size / 2)
			{
				directory[new_index].addressPointer = (struct add*)malloc(sizeof(struct add));
				initialize_OneDR(new_index);
			}
			insertDR(temp[i].key_name);

		}

		insertDR(key_input);


	}
}

void initializeDR()
{
	int i;

	for(i = 0; i < 4; i++)
	{
		directory[i].ld = gd;

		directory[i].addressPointer = (struct add*)malloc(sizeof(struct add));

		directory[i].addressPointer->slot1.value = -1;
		directory[i].addressPointer->slot2.value = -1;
		sprintf(directory[i].addressPointer->slot1.key_name, "%s", " ");
		sprintf(directory[i].addressPointer->slot2.key_name, "%s", " ");
	}
}


void initialize_OneDR(int index)
{
	directory[index].ld = gd;
	directory[index].addressPointer->slot1.value = -1;
	sprintf(directory[index].addressPointer->slot1.key_name, "%s", " ");
	directory[index].addressPointer->slot2.value = -1;
	sprintf(directory[index].addressPointer->slot2.key_name, "%s", " ");

}

void copyDR()
{
	int i;

	for(i = size/2; i < size; i++)
		directory[i] = directory[i - size/2];
}

void printDR()
{
	int i;


	for(i = 0; i < size; i++)
		printf("directory[%d] : local depth = %d  bucket(%s, %s)\n", i, directory[i].ld, directory[i].addressPointer->slot1.key_name, directory[i].addressPointer->slot2.key_name);
}

void searchDR(char input_key[])
{
	int index;
	int global_depth;
	int flag = 0;
	
	for (global_depth = 2; global_depth <= gd; global_depth++)
	{
		index = h_getIndex(input_key, global_depth);

		if (global_depth == gd && directory[index].addressPointer->slot1.value == -1 && directory[index].addressPointer->slot2.value == -1)
		{
			printf("%s is not exist.\n", input_key);
			flag = 1;
			break;
		}

		
		if (directory[index].addressPointer->slot1.value == h(input_key))
		{
			printf("directory[%d] : local depth = %d , slot1 <%s, %d>\n", index, directory[index].ld, input_key, h(input_key));
			flag = 1;
			break;
		}
		else if (directory[index].addressPointer->slot2.value == h(input_key))
		{
			printf("directory[%d] : local depth = %d , slot2 <%s, %d>\n", index, directory[index].ld, input_key, h(input_key));
			flag = 1;
			break;
		}
		
	}
	if (flag == 0)
		printf("%s is not exist.\n", input_key);
}

void deleteDR(char input_key[])
{
	int global_depth;
	int index, flag;
	int sibling, i;
	int count = 0;

	
	for (global_depth = 2; global_depth <= gd; global_depth++)
	{
		index = h_getIndex(input_key, global_depth);

		if (global_depth == gd && directory[index].addressPointer->slot1.value == -1 && directory[index].addressPointer->slot2.value == -1)
		{
			printf("%s is not exist.\n", input_key);
			flag = 1;
			break;
		}

		//slot1을 삭제
		if (directory[index].addressPointer->slot1.value == h(input_key))
		{
			
			//slot2를 slot1으로 옮긴 후 slot2 초기화
			directory[index].addressPointer->slot1.value = directory[index].addressPointer->slot2.value;
			sprintf(directory[index].addressPointer->slot1.key_name, "%s", directory[index].addressPointer->slot2.key_name);
			directory[index].addressPointer->slot2.value = -1;
			sprintf(directory[index].addressPointer->slot2.key_name, "%s", " ");
			
			//slot1 삭제후 slot1이 비었을 시
			if (directory[index].addressPointer->slot1.value == -1)
			{
				if (directory[index].ld != 2)
				{
					sibling = 1;
					for (i = 0; i < gd - 1; i++)
						sibling *= 2;

					if (index >= size / 2)
					{
						directory[index] = directory[index - sibling];
						directory[index].ld = directory[index - sibling].ld;
						if (directory[index].ld != 2)
						{
							directory[index].ld--;
							directory[index - sibling].ld--;
						}
						

						for (i = 0; i < size / 2; i++)
						{
							if (directory[i].ld < gd)
								count++;
						}

						if (count == size / 2)
						{
							size /= 2;
							gd--;
							
							for (i = 0; i < size; i++)
							{
								if (directory[i].addressPointer->slot1.value == -1)
									directory[i] = directory[i + sibling];
							}

							directory = (hash *)realloc(directory, sizeof(hash) * size);
						}


					}
					
					else
					{
						directory[index] = directory[index + sibling];
						if (directory[index].ld != 2)
						{
							directory[index].ld--;
							directory[index + sibling].ld--;
						}
						

						for (i = 0; i < size / 2; i++)
						{
							if (directory[i].ld < gd)
								count++;
						}

						if (count == size / 2)
						{
							size /= 2;
							gd--;

							for (i = 0; i < size; i++)
							{
								if (directory[i].addressPointer->slot1.value == -1)
									directory[i] = directory[i + sibling];
							}

							directory = (hash *)realloc(directory, sizeof(hash) * size);
						}
					}

				}

			}


			flag = 1;
			break;
		}

		//slot2를 삭제
		else if (directory[index].addressPointer->slot2.value == h(input_key))
		{
			//slot2 초기화
			directory[index].addressPointer->slot2.value = -1;
			sprintf(directory[index].addressPointer->slot2.key_name, "%s", " ");
			flag = 1;
			break;
		}
	}

	if (flag == 0)
		printf("%s is not exist.\n", input_key);
}
