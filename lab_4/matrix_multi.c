/*
	Author: Ananta Srikar
*/

#include<stdio.h>
#include<stdlib.h>

int main()
{
	// Function prototypes
	int **get_rand_array(int);
	int **matrix_multi(int**, int**, int, int);
	int **normal_matrix_multi(int**, int**, int);

	// const int size = 1024;
	const int size = 4;

	int **A = get_rand_array(size);
	int **B = get_rand_array(size);

	// int **C = normal_matrix_multi(A, B, size);

	int **C = matrix_multi(A, B, size, 2);
	int **D = normal_matrix_multi(A, B, size);

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			printf("%d ", A[i][j]);

		printf("\n");
	}

	printf("\n");

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			printf("%d ", B[i][j]);

		printf("\n");
	}

	printf("\n");


	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			printf("%d ", C[i][j]);

		printf("\n");
	}

	printf("\n");
	
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			printf("%d ", D[i][j]);

		printf("\n");
	}
	
	return(0);
}

void transpose_matrix(int **X, int size)
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < i; j++)
		{
			int temp = X[i][j];
			X[i][j] = X[j][i];
			X[j][i] = temp;
		}
}

int **get_rand_array(int size)
{
	int **arr;

	arr = (int**)malloc(size * sizeof(int*));

	for(int i = 0; i < size; i++)
		arr[i] = (int*)malloc(size * sizeof(int));
	// Seeding the random number generator
	// srand(0);

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			arr[i][j] = (i + j) % 5; // % 5 will make sure the numbers are in range after multiplying
			// arr[i][j] = rand();

	return arr;
}

int **get_zero_array(int size)
{
	int **arr;

	arr = (int**)malloc(size * sizeof(int*));

	for(int i = 0; i < size; i++)
		arr[i] = (int*)malloc(size * sizeof(int));
	// Seeding the random number generator
	// srand(0);

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			arr[i][j] = 0;

	return arr;
}

int **normal_matrix_multi(int **A, int **B, int size)
{
	int **C = get_zero_array(size);

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			for(int k = 0; k < size; k++)
			{
				C[i][j] += A[i][k] * B[j][k];
			}
	}

	return C;
}

void normal_matrix_multi1(int **A, int **B, int **C, int i_start, int j_start, int blk_size)
{
	for(int i = 0; i < i_start + blk_size; i++)
	{
		for(int j = 0; j < j_start + blk_size; j++)
			for(int k = 0; k < i_start + blk_size; k++)
			{
				C[i][j] += A[i][k] * B[j][k];
			}
	}
}

int **matrix_multi(int **A, int **B, int size, int blk_size)
{
	int **C = get_zero_array(size);

	for(int i = 0; i < size; i += blk_size)
	{
		for(int j = 0; j < size; j += blk_size)
		{
			normal_matrix_multi1(A, B, C, i, j, blk_size);
		}
	}

	return C;
}