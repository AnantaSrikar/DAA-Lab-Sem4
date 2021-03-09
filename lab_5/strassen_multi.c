/*
	Author: Ananta Srikar

	TODO:
		- Add comments
		- change stdout to outFPtr
		- fix SEGV
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/time.h>

int main(int argc, char **argv)
{
	// vars to store timestamps to calculate exectuion time
	struct timeval start, end_init, end_exec;

	// Function prototypes
	int **get_rand_array(int);
	int **strassen_matrix_multi(int**, int**, int);
	void writeToFile(FILE*, int**, int**, int**, int);

	// File handling
	FILE *outFPtr = fopen("DAALab_output1.txt", "w");
	
	// fixed size of matrices
	const int size = 4;

	// Getting start time for initialisation
	gettimeofday(&start, NULL);

	// Initializing two arrays of order 1024x1024 with random values
	int **A = get_rand_array(size);
	int **B = get_rand_array(size);

	// End of initialisation time
	gettimeofday(&end_init, NULL);

	int **C = strassen_matrix_multi(A, B, size);

	// Time after executing the block matrix multiplication
	gettimeofday(&end_exec, NULL);

	// Calulating times for initialisation and execution
	float init_time = ((end_init.tv_sec * 1000000 + end_init.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	float exec_time = ((end_exec.tv_sec * 1000000 + end_exec.tv_usec) - (end_init.tv_sec * 1000000 + end_init.tv_usec));

	init_time /= 1000000;
	exec_time /= 1000000;

	// Writing all the matrices to the output file
	writeToFile(outFPtr, A, B, C, size);

	printf("\nTime taken to initialise: %fs\n", init_time);
	printf("Time taken to execute: %fs\n\n", exec_time);

	printf("Both the input matrices and their multiplied matrix is stored in 'DAALab_output1.txt'.\n");
	
	return(0);
}

// Function to get matrix with random numbers
int **get_rand_array(int size)
{
	int **arr;

	arr = (int**)malloc(size * sizeof(int*));

	for(int i = 0; i < size; i++)
		arr[i] = (int*)malloc(size * sizeof(int));
	
	// Seeding the random number generator
	srand(0);

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			arr[i][j] = rand() % 10;

	return arr;
}

// Function to get 0 matrix, which can be filled later
int **get_zero_array(int size)
{
	int **arr;

	arr = (int**)malloc(size * sizeof(int*));

	for(int i = 0; i < size; i++)
		arr[i] = (int*)malloc(size * sizeof(int));

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			arr[i][j] = 0;

	return arr;
}

int **add_matrices(int **A, int **B, int size)
{
	int **C = get_zero_array(size);

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			C[i][j] = A[i][j] + B[i][j];

	return C;
}

int **sub_matrices(int **A, int **B, int size)
{
	int **C = get_zero_array(size);

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			C[i][j] = A[i][j] - B[i][j];

	return C;
}

int ***split(int **X, int size)
{
	int ***splits = (int***)malloc(4 * sizeof(int**));

	for(int i = 0; i < 4; i++)
		splits[i] = get_zero_array(size / 2);

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(i < (size / 2) && j < (size / 2))
				splits[0][i][j] = X[i][j];

			else if(i < (size / 2) && j >= (size / 2))
				splits[1][i][j - (size / 2)] = X[i][j];

			else if(i >= (size / 2) && j < (size / 2))
				splits[2][i - (size / 2)][j] = X[i][j];

			else if(i >= (size / 2) && j >= (size / 2))
				splits[3][i - (size / 2)][j - (size / 2)] = X[i][j];

	return splits;
}

// Block matrix multiplication algorithm
int **strassen_matrix_multi(int **A, int **B, int size)
{
	int **C = get_zero_array(size);

	if(size == 1)
	{
		C[0][0] = A[0][0] * B[0][0];
		return C;
	}

	int ***split_A = split(A, size);
	int ***split_B = split(B, size);

	int new_size = size / 2;

	int **p1 = strassen_matrix_multi(split_A[0], sub_matrices(split_B[1], split_B[3], new_size), new_size);
	int **p2 = strassen_matrix_multi(add_matrices(split_A[0], split_A[1], new_size), split_B[3], new_size);
	int **p3 = strassen_matrix_multi(add_matrices(split_A[3], split_A[4], new_size), split_B[0], new_size);
	int **p4 = strassen_matrix_multi(split_A[4], sub_matrices(split_B[3], split_B[0], new_size), new_size);
	int **p5 = strassen_matrix_multi(add_matrices(split_A[0], split_A[4], new_size), add_matrices(split_B[0], split_B[3], new_size), new_size);
	int **p6 = strassen_matrix_multi(sub_matrices(split_A[1], split_A[4], new_size), add_matrices(split_B[3], split_B[3], new_size), new_size);
	int **p7 = strassen_matrix_multi(sub_matrices(split_A[0], split_A[3], new_size), add_matrices(split_B[0], split_B[1], new_size), new_size);

	int **c11 = add_matrices(sub_matrices(add_matrices(p5, p4, new_size), p2, new_size), p6, new_size);
	int **c12 = add_matrices(p1, p2, new_size);
	int **c21 = add_matrices(p3, p4, new_size);
	int **c22 = sub_matrices(sub_matrices(add_matrices(p1, p5, new_size), p3, new_size), p7, new_size);

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(i < new_size && j < new_size)
				C[i][j] = c11[i][j];

			else if(i < new_size && j >= new_size)
				C[i][j] = c12[i][j - new_size];

			else if(i >= new_size && j < new_size)
				C[i][j] = c21[i - new_size][j];

			else if(i >= new_size && j >= new_size)
				C[i][j] = c22[i - new_size][j - new_size];

	return C;
}

// Function to write the matrices into the output file
void writeToFile(FILE *outFPtr, int **A, int **B, int **C, int size)
{
	fprintf(stdout, "Matrix A: \n");

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			fprintf(stdout, "%d ", A[i][j]);

		fprintf(stdout, "\n");
	}

	fprintf(stdout, "\n\n");

	fprintf(stdout, "Matrix B: \n");

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			fprintf(stdout, "%d ", B[i][j]);

		fprintf(stdout, "\n");
	}

	fprintf(stdout, "\n\n");

	fprintf(stdout, "Matrix C: \n");

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			fprintf(stdout, "%d ", C[i][j]);

		fprintf(stdout, "\n");
	}
}