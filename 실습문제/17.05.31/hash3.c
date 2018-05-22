#include <stdio.h>

int char_to_num(char num);
int h(char key[]);
int h_getIndex(char key_input[], int p);

int main()
{
	int i, j, p;
	char input_key[3];
	char table[3];


	for(i = 0; i < 24; i++)
	{
		if(i < 8)
		{
			sprintf(table, "A%d", i);
			printf("%s : %d\n", table, h(table));
		}

		else if(8 <= i && i < 16)
		{
			sprintf(table, "B%d", i - 8);
			printf("%s : %d\n", table, h(table));
		}

		else if(16 <= i && i < 24)
		{
			sprintf(table, "C%d", i - 16);
			printf("%s : %d\n", table, h(table));
		}
	}
	
	//printf("=================================\n");
	//printf("<key, p>를 입력하시오 (key = A0~A7 or B0 ~ B7 or C0 ~ C7 , 1 <= p <= 5) : ");
	//scanf("%s", input_key);
	//scanf("%d", &p);

	//printf("h(k, p) = %d\n", h_getIndex(input_key, p));
	printf("=================================\n");

	for(p = 1; p < 6; p++)
	{
		for(i = 0; i < 24; i++)
		{
			if(i < 8)
			{
				sprintf(table, "A%d", i);
				printf("h(%s , %d) = %d\n", table, p, h_getIndex(table, p));
			}

			else if(8 <= i && i < 16)
			{
				sprintf(table, "B%d", i - 8);
				printf("h(%s , %d) = %d\n", table, p, h_getIndex(table, p));
			}

			else if(16 <= i && i < 24)
			{
				sprintf(table, "C%d", i - 16);
				printf("h(%s , %d) = %d\n", table, p, h_getIndex(table, p));
			}
		}

	}

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


