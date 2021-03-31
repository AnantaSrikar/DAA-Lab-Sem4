/*
	Author: Ananta Srikar

	TODO: Add comments
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char **argv)
{
	// Initial code to get all command line values
	
	if(argc < 2)
	{
		printf("Incorrect number of arguments! Please go through README.md\n");
		return -1;
	}

	int input_arr[argc - 1];

	for(int i = 1; i < argc; i++)
	{
		for(int j = 0; j < strlen(argv[i]); j++)
			if(!isdigit(argv[i][j]) && argv[i][j] != '-')
			{
				printf("Please enter only numbers!\n");
				return -1;
			}

		input_arr[i - 1] = atoi(argv[i]);
	}

	int size = input_arr[0];

	if(size * 2 != argc - 2)
	{
		printf("Enter valid number of arguments!");
		return -1;
	}

	int deadlines[size], profits[size];

	for(int i = 1; i < size + 1; i++)
		deadlines[i - 1] = input_arr[i];

	for(int i = size + 1; i < size * 2 + 1; i++)
		profits[i - size - 1] = input_arr[i];

	// End of command line arguments

	// Function prototypes

	int getMaxDeadline(int[], int);
	int *getProfitVector(int[], int[], int);

	int max_days = getMaxDeadline(deadlines, size);
	int *profit_vector_index = getProfitVector(deadlines, profits, size);

	int solution_vector[size];

	for(int i = 0; i < max_days; i++)
		solution_vector[profit_vector_index[i]] = 1;

	// To prevent junk values
	for(int i = 0; i < size; i++)
		if(solution_vector[i] != 1)
			solution_vector[i] = 0;

	printf("\nThe solution vector to get max profit is:\n[");

	for(int i = 0; i < size; i++)
		if(i == size - 1)
			printf("%d]", solution_vector[i]);
		else
			printf("%d, ", solution_vector[i]);

	printf("\n\nOrder of doing the jobs:\n");

	for(int i = 0; i < max_days; i++)
		if(i == max_days - 1)
			printf("%d", profit_vector_index[i] + 1);
		else
			printf("%d, ", profit_vector_index[i] + 1);

	printf("\n\n");
	
	int net_profit = 0;

	for(int i = 0; i < size; i++)
		if(solution_vector[i] == 1)
			net_profit += profits[i];

	printf("Net profit = %d\n", net_profit);

	return(0);
}

int getMaxDeadline(int deadlines[], int size)
{
	int max = deadlines[0];

	for(int i = 0; i < size; i++)
		if(max < deadlines[i])
			max = deadlines[i];
	
	return max;
}

int getLeastDeadline(int deadlines[], int more_than, int size)
{
	int temp_deadlines[size];

	for(int i = 0; i < size; i++)
		temp_deadlines[i] = deadlines[i];

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size - 1; j++)
			if(temp_deadlines[j] > temp_deadlines[j + 1])
			{
				int temp = temp_deadlines[j];
				temp_deadlines[j] = temp_deadlines[j + 1];
				temp_deadlines[j + 1] = temp;
			}

	for(int i = 0; i < size; i++)
		if(temp_deadlines[i] > more_than)
			return temp_deadlines[i];
}

void getSortedProfitsIndex(int profits[], int profits_sorted[], int size)
{
	// Copyting the profits
	for(int i = 0; i < size; i++)
		profits_sorted[i] = i;

	// Sorting the profits
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size - 1; j++)
			if(profits[profits_sorted[j]] < profits[profits_sorted[j + 1]])
			{
				int temp = profits_sorted[j + 1];
				profits_sorted[j + 1] = profits_sorted[j];
				profits_sorted[j] = temp;
			}
}

int getMaxProfitDeadlineIndex(int deadlines[], int profits_sorted_index[], int deadline, int size)
{
	for(int i = 0; i < size; i++)
		if(deadlines[profits_sorted_index[i]] == deadline)
			return profits_sorted_index[i];
}

int *getProfitVector(int deadlines[], int profits[], int size)
{
	int max_days = getMaxDeadline(deadlines, size);
	int profits_sorted_index[size];

	int *profit_vector_index = (int*)malloc(max_days * sizeof(int));

	getSortedProfitsIndex(profits, profits_sorted_index, size);

	for(int i = 0; i < max_days; i++)
		profit_vector_index[i] =  getMaxProfitDeadlineIndex(deadlines, profits_sorted_index, getLeastDeadline(deadlines, i, size), size);

	return profit_vector_index;
}