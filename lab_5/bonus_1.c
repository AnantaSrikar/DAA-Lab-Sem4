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

	if(size != argc - 3)
	{
		printf("Enter valid number of arguments!");
		return -1;
	}

	int ith_ele = input_arr[1];

	if(ith_ele > size || ith_ele < 1)
	{
		printf("Invalid ith element entered!");
		return -1;
	}

	int arr[size];

	for(int i = 2; i < size + 2; i++)
		arr[i - 2] = input_arr[i];

	// End of command line arguments

	int ithSmallest(int [], int, int, int);

	int ith_smol = ithSmallest(arr, 0, size - 1, ith_ele);

	printf("ith smallest element: %d\n", ith_smol);

	return(0);
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int arr[], int l, int r)
{
	int x = arr[r], i = l;
	
	for (int j = l; j <= r - 1; j++)
		if(arr[j] <= x)
		{
			swap(&arr[i], &arr[j]);
			i++;
		}
	
	swap(&arr[i], &arr[r]);
	return i;
}

int ithSmallest(int arr[], int left, int right, int i)
{
	if(left == right)
		return arr[left];

	int pos = partition(arr, left, right);

	if (pos - left == i - 1)
		return arr[pos];
	
	// If position is more, recur for left subarray
	if(pos - left > i - 1)
		return ithSmallest(arr, left, pos - 1, i);

	// Else recur for right subarray
	return ithSmallest(arr, pos + 1, right, i - pos + left - 1);
}