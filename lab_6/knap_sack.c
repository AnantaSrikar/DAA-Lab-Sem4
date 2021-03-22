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

	if(size * 2 != argc - 3)
	{
		printf("Enter valid number of arguments!");
		return -1;
	}

	int M = input_arr[2 * size + 1];
	float weights[size], profits[size];

	for(int i = 1; i < size + 1; i++)
		weights[i - 1] = input_arr[i];

	for(int i = size + 1; i < 2 * size + 1; i++)
		profits[i - size - 1] = input_arr[i];

	// End of command line arguments

	float p_by_w[size];

	for(int i = 0; i < size; i++)
		p_by_w[i] = profits[i] / weights[i];

	for(int i = 0; i < size; i++)
		printf("%f ", p_by_w[i]);

	printf("\n\nM = %d", M);

	int wrapper_ith(float arr[], int, int);

	int ith_smol = wrapper_ith(p_by_w, size, 1);

	printf("1st largest: %d\nThe whole profit vector:\n", ith_smol);

	float *getProfitVector(float[], float[], int, int);

	float *profit_vector = getProfitVector(weights, profits, size, M);
	
	for(int i = 0; i < size; i++)
		printf("%f ", profit_vector[i]);

	printf("\n");

	return(0);
}

void swap(float* a, float* b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

int partition(float arr[], int l, int r)
{
	float x = arr[r];
	int i = l;
	
	for (int j = l; j <= r - 1; j++)
		if(arr[j] >= x)
		{
			swap(&arr[i], &arr[j]);
			i++;
		}
	
	swap(&arr[i], &arr[r]);
	return i;
}

float find_ith_max(float arr[], int left, int right, int i)
{
	if(left == right)
		return arr[left];

	int pos = partition(arr, left, right);

	if (pos - left == i - 1)
		return arr[pos];
	
	// If position is more, recur for left subarray
	if(pos - left > i - 1)
		return find_ith_max(arr, left, pos - 1, i);

	// Else recur for right subarray
	return find_ith_max(arr, pos + 1, right, i - pos + left - 1);
}

int wrapper_ith(float arr[], int size, int ith)
{
	// Copying the array into a temporary array, since it will be modified

	float *temp_arr = (float*)malloc(size * sizeof(float));

	for(int i =0; i < size; i++)
		temp_arr[i] = arr[i];

	float ith_min = find_ith_max(temp_arr, 0, size - 1, ith);

	int index;

	for(int i = 0; i < size; i++)
		if(ith_min == arr[i])
		{
			index = i;
			break;
		}

	free(temp_arr);

	return index;
}

float *getProfitVector(float weights[], float profits[], int size, int M)
{
	float p_by_w[size];

	for(int i = 0; i < size; i++)
		p_by_w[i] = profits[i] / weights[i];

	float *profit_vector = (float*)malloc(size * sizeof(float));
	if(size == 1)
	{
		if(weights[0] > M)
			profit_vector[0] = M / weights[0];

		else
			profit_vector[0] = 1;
	}

	else
	{
		float remaining = M;

		for(int i = 0; i < size; i++)
		{
			if(remaining == 0)
				break;

			int index = wrapper_ith(p_by_w, size, i + 1);

			printf("Got index: %d\n", index);

			if(weights[index] > remaining)
			{
				profit_vector[index] = remaining / weights[index];
				break;
			}

			else
			{
				profit_vector[index] = 1;
				remaining -= weights[index];
			}
		}
	}

	return profit_vector;
}