#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_STUDENT 6900
#define BLOCK_SIZE 60
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SWAP(x,y,t) ( (t) = (x), (x) = (y), (y) = (t))
#define ORIGIN 6900
#define TEMP 300
typedef struct {
	int id;
	char name[40];
	char address[100];
} element;


typedef struct {
	element value;
	int run;
} heap;

heap tree[8];
int array_temp[300];
int block_top[4]; // 현재 block의 top
element block1[60], block2[60], block3[60], block4[60];
int size_of_last_run;

void selectionSort(int a[], int n);
void initializeBlock(int run[]);
void setTree();
void initializeTree(int index);
int number_of_elements_of_NextRun(int current_step, int current_total_number_of_runs, int size_of_last_run);
void first_position_of_current_set(FILE *file, int number_of_completed_sets);
void set_starting_position_of_run(FILE *run, int current_step, int run_number);
void merge_run(FILE *temp1, FILE *temp2, int current_step, int number_of_runs);

int main()
{
	int i, j, k;
	element random[6900];
	int num_of_run = 0;
	int step = 1;

	FILE *test;
	FILE *sort1, *sort2;


	srand(time(NULL));
	test = fopen("test.dat", "wb+");


	for (i = 0; i < 6900; i++)
	{

		random[i].id = rand();
		sprintf(random[i].name, "name%d", random[i].id);
		sprintf(random[i].address, "address%d", random[i].id);
	}
	fwrite(random, sizeof(element), 6900, test);

	sort1 = fopen("sort1.dat", "wb+");

	rewind(test);
	for (i = 0; i < ORIGIN / TEMP; i++)
	{
		fread(array_temp, sizeof(element), TEMP, test);
		selectionSort(array_temp, TEMP);
		fwrite(array_temp, sizeof(element), TEMP, sort1);
		num_of_run++;
	}

	sort2 = fopen("sort2.dat", "wb+");

	size_of_last_run = number_of_elements_of_NextRun(step, num_of_run, 1);

	while (num_of_run != 1)
	{
		if (step % 2 == 1)
		{
			merge_run(sort1, sort2, step++, num_of_run);

			fclose(sort1);
			remove("sort1.dat");

			sort1 = fopen("sort1.dat", "wb+");

			if (num_of_run % 4 == 0)
				num_of_run = num_of_run / 4;
			else
				num_of_run = num_of_run / 4 + 1;

		}

		else
		{
			merge_run(sort2, sort1, step++, num_of_run);

			fclose(sort2);
			remove("sort2.dat");

			sort2 = fopen("sort2.dat", "wb+");

			if (num_of_run % 4 == 0)
				num_of_run = num_of_run / 4;
			else
				num_of_run = num_of_run / 4 + 1;
		}

	}


	return 0;
}

void selectionSort(element a[], int n)
{
	int i, j, min;
	element temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (a[j].id < a[min].id) min = j;
		if (min != i)
			SWAP(a[i], a[min], temp);
	}
}


void initializeBlock(element block[])
{
	int i;

	for (i = 0; i < 30; i++)
		block[i].id = -1;
}



void setTree()
{
	int i, j;


	for (j = 2; j != 0; j /= 2)
	{
		for (i = j; i < j * 2; i++)
		{
			//둘 다 -1
			if (tree[2 * i].value.id == -1 && tree[2 * i + 1].value.id == -1)
				tree[i].value.id = -1;

			// 하나만 -1
			else if (tree[2 * i].value.id == -1)
			{
				tree[i].value = tree[2 * i + 1].value;
				tree[i].run = tree[2 * i + 1].run;
			}
			// 하나만 -1
			else if (tree[2 * i + 1].value.id == -1)
			{
				tree[i].value = tree[2 * i].value;
				tree[i].run = tree[2 * i].run;
			}

			//둘 다 -1이 아닐 때
			else if (tree[2 * i].value.id != -1 && tree[2 * i + 1].value.id != -1)
			{
				tree[i].value = (tree[2 * i].value.id <= tree[2 * i + 1].value.id) ? tree[2 * i].value : tree[2 * i + 1].value;
				tree[i].run = (tree[2 * i].value.id <= tree[2 * i + 1].value.id) ? tree[2 * i].run : tree[2 * i + 1].run;
			}
		}
	}

}

void initializeTree(int index)
{
	switch (index)
	{
	case 1: tree[4].value = block1[block_top[0]++]; break;
	case 2: tree[5].value = block2[block_top[1]++]; break;
	case 3: tree[6].value = block3[block_top[2]++]; break;
	case 4: tree[7].value = block4[block_top[3]++]; break;
	}
}

//다음 step의 마지막 run의 크기
int number_of_elements_of_NextRun(int current_step, int current_total_number_of_runs, int size_of_last_run)
{
	int i;
	int max_size_of_run = 1; // 단위 1만

	for (i = 0; i < current_step - 1; i++)
		max_size_of_run *= 4;

	switch (current_total_number_of_runs % 4)
	{
	case 1: return size_of_last_run;
	case 2: return size_of_last_run + max_size_of_run;
	case 3: return size_of_last_run + 2 * max_size_of_run;
	case 0: return size_of_last_run + 3 * max_size_of_run;
	default: return -1;
	}
}


//현재 set의 첫 번째 run의 위치
void first_position_of_current_set(FILE *file, int number_of_completed_sets)
{
	int i;
	int max_size_of_run = 1;

	fseek(file, sizeof(element) * number_of_completed_sets, SEEK_SET);
}

//각 run의 첫 번째 위치
void set_starting_position_of_run(FILE *run, int run_number)
{
	int i;
	int max_size_of_run = 1;

	fseek(run, sizeof(element) * (run_number - 1), SEEK_CUR);
}


void merge_run(FILE *temp1, FILE *temp2, int current_step, int number_of_runs)
{

	FILE* run[4];
	int completed_block[4]; // 각 run의 완료된 block의 수
	char filename[1024];
	int count_new_run;
	element new_run[300];
	int i;
	int completed_set = 0, number_of_runs_last_set;
	int run_cycle, current_run_cycle;
	int block_cycle[4];
	int max_size_run = 3;

	if (current_step % 2 == 1)
		sprintf(filename, "sort1.dat");
	else
		sprintf(filename, "sort2.dat");


	// tree의 run 설정
	for (i = 4; i < 8; i++)
		tree[i].run = i - 3;

	if (number_of_runs % 4 == 0)
		run_cycle = number_of_runs / 4;
	else
		run_cycle = number_of_runs / 4 + 1;


	//현재 step에서 run의 최대 크기
	for (i = 0; i < current_step - 1; i++)
		max_size_run *= 4;

	number_of_runs_last_set = number_of_runs % max_size_run;


	for (current_run_cycle = 0; current_run_cycle < run_cycle; current_run_cycle++)
	{
		count_new_run = 0;
		//run 새로 읽어오기
		for (i = 0; i < 4; ++i)
		{
			run[i] = fopen(filename, "rb");
			first_position_of_current_set(run[i], completed_set);
			set_starting_position_of_run(run[i], i + 1);
			completed_block[i] = 0;
			block_cycle[i] = 0;
		}

		initializeBlock(block1);
		initializeBlock(block2);
		initializeBlock(block3);
		initializeBlock(block4);

		fread(block1, sizeof(element), 60, run[0]);
		fread(block2, sizeof(element), 60, run[1]);
		fread(block3, sizeof(element), 60, run[2]);
		fread(block4, sizeof(element), 60, run[3]);

		tree[4].value = block1[0];
		tree[5].value = block2[0];
		tree[6].value = block3[0];
		tree[7].value = block4[0];


		// 마지막 set가 4개가 아닐떄
		if (number_of_runs_last_set != 0 && current_run_cycle == run_cycle - 1)
		{
			for (i = 0; i < number_of_runs_last_set - 1; i++)
			{
				if (max_size_run % 4 == 0)
					block_cycle[i] = max_size_run / 4;

				else
					block_cycle[i] = max_size_run / 4 + 1;
			}

			//마지막 run의 block cycle
			if (size_of_last_run % 4 == 0)
				block_cycle[i] = size_of_last_run / 4;
			else
				block_cycle[i] = size_of_last_run / 4 + 1;
		}
		// 마지막 set가 4개일 때
		else if (current_run_cycle == run_cycle - 1 && number_of_runs_last_set == 0)
		{
			for (i = 0; i < 3; i++)
			{
				if (max_size_run % 4 == 0)
					block_cycle[i] = max_size_run / 4;
				else
					block_cycle[i] = max_size_run / 4 + 1;
			}

			//마지막 run의 block cycle
			if (size_of_last_run % 4 == 0)
				block_cycle[i] = size_of_last_run / 4;
			else
				block_cycle[i] = size_of_last_run / 4 + 1;

		}

		//마지막 set 전
		else if (current_run_cycle < run_cycle - 1)
		{
			for (i = 0; i < 4; i++)
			{
				if (max_size_run % 4 == 0)
					block_cycle[i] = max_size_run / 4;

				else
					block_cycle[i] = max_size_run / 4 + 1;
			}
		}

		while (1)
		{
			setTree();
			new_run[count_new_run++] = tree[1].value;
			initializeTree(tree[1].run);


			//block1
			if (block_top[0] == 60)
			{
				block_top[0] = 0; completed_block[0]++;
				initializeBlock(block1);

				if (completed_block[0] == block_cycle[0] - 1)
				{
					if (block_cycle[1] == 0)
						fread(block1, sizeof(element), size_of_last_run % 60, run[0]);
					else
						fread(block1, sizeof(element), max_size_run % 60, run[0]);
				}
				else
					fread(block1, sizeof(element), 60, run[0]);
			}

			//block2
			else if (block_top[1] == 60)
			{
				block_top[1] = 0; completed_block[1]++;
				initializeBlock(block2);

				if (completed_block[1] == block_cycle[1] - 1)
				{
					if (block_cycle[2] == 0)
						fread(block2, sizeof(element), size_of_last_run % 60, run[1]);
					else
						fread(block2, sizeof(element), max_size_run % 60, run[1]);
				}

				else
					fread(block2, sizeof(element), 60, run[1]);
			}

			//block3
			else if (block_top[2] == 60)
			{
				block_top[2] = 0; completed_block[2]++;
				initializeBlock(block3);

				if (completed_block[2] == block_cycle[2] - 1)
				{
					if (block_cycle[3] == 0)
						fread(block3, sizeof(element), size_of_last_run % 60, run[2]);
					else
						fread(block3, sizeof(element), max_size_run % 60, run[2]);
				}

				else
					fread(block3, sizeof(element), 60, run[2]);
			}

			//block4
			else if (block_top[3] == 60)
			{
				block_top[3] = 0; completed_block[3]++;
				initializeBlock(block4);

				if (completed_block[3] == block_cycle[3] - 1)
				{
					if (current_run_cycle == run_cycle - 1)
						fread(block4, sizeof(element), size_of_last_run % 60, run[3]);
					else
						fread(block4, sizeof(element), max_size_run % 60, run[3]);
				}
				else
					fread(block4, sizeof(element), 60, run[3]);
			}

			//new Run이 가득차면 temp2에 입력
			if (count_new_run == 300)
			{
				fwrite(new_run, sizeof(element), count_new_run, temp2);
				count_new_run = 0;
			}

			//모든 run의 block이 끝나면 종료
			if (completed_block[0] == block_cycle[0] && completed_block[1] == block_cycle[1] && completed_block[2] == block_cycle[2] && completed_block[3] == block_cycle[3])
				break;

		}//while winner tree

		completed_set++;
	}//run cycle
}