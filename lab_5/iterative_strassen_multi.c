/*
	Author: Ananta Srikar

	TODO:
		- Add comments
		- fix RAM usage
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/time.h>

struct matrix_pt
{
	int x_start;
	int x_end;
	int y_start;
	int y_end;
};

typedef struct matrix_pt matrix_pt;

int main(int argc, char **argv)
{
	// vars to store timestamps to calculate exectuion time
	struct timeval start, end_init, end_exec;

	// Seeding the random number generator
	// NOTE: seed it only ONCE in the code
	srand(0);

	// Function prototypes
	int **get_rand_array(int);
	int **get_zero_array(int);
	void strassen_matrix_multi(int**, int**, int**, matrix_pt*, matrix_pt*);
	void writeToFile(FILE*, int**, int**, int**, int);

	// File handling
	FILE *outFPtr = fopen("DAALab_output1.txt", "w");
	
	// fixed size of matrices
	const int size = 1024;

	// Getting start time for initialisation
	gettimeofday(&start, NULL);

	// Initializing two arrays of order 1024x1024 with random values
	int **A = get_rand_array(size);
	int **B = get_rand_array(size);
	int **C = get_zero_array(size);

	matrix_pt *A_pts = (matrix_pt*)malloc(sizeof(matrix_pt));
	matrix_pt *B_pts = (matrix_pt*)malloc(sizeof(matrix_pt));
	matrix_pt *C_pts = (matrix_pt*)malloc(sizeof(matrix_pt));

	A_pts -> x_start = A_pts -> y_start = B_pts -> x_start = B_pts -> y_start = C_pts -> x_start = C_pts -> y_start = 0;
	A_pts -> x_end = A_pts -> y_end = B_pts -> x_end = B_pts -> y_end = C_pts -> x_end = C_pts -> y_end = size;
	
	// End of initialisation time
	gettimeofday(&end_init, NULL);

	strassen_matrix_multi(A, B, C, A_pts, B_pts);

	// Time after executing the block matrix multiplication
	gettimeofday(&end_exec, NULL);

	// Calulating times for initialisation and execution
	float init_time = ((end_init.tv_sec * 1000000 + end_init.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	float exec_time = ((end_exec.tv_sec * 1000000 + end_exec.tv_usec) - (end_init.tv_sec * 1000000 + end_init.tv_usec));

	init_time /= 1000000;
	exec_time /= 1000000;

	// Writing all the matrices to the output file
	// writeToFile(outFPtr, A, B, C, size);

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

matrix_pt **split(matrix_pt *pt)
{
	matrix_pt **split = (matrix_pt**)malloc(4 * sizeof(matrix_pt));

	for(int i = 0; i < 4; i++)
		split[i] = (matrix_pt*)malloc(sizeof(matrix_pt));

	split[0] -> x_start = pt -> x_start;
	split[0] -> x_end = pt -> x_end / 2;
	split[0] -> y_start = pt -> y_start;
	split[0] -> y_end = pt -> y_end / 2;

	split[1] -> x_start = pt -> x_end / 2 + 1;
	split[1] -> x_end = pt -> x_end;
	split[1] -> y_start = pt -> y_start;
	split[1] -> y_end = pt -> y_end / 2;

	split[2] -> x_start = pt -> x_start;
	split[2] -> x_end = pt -> x_end / 2;
	split[2] -> y_start = pt -> y_start / 2 + 1;
	split[2] -> y_end = pt -> y_end;

	split[3] -> x_start = pt -> x_end / 2 + 1;
	split[3] -> x_end = pt -> x_end;
	split[3] -> y_start = pt -> y_end / 2 + 1;
	split[3] -> y_end = pt -> y_end;

	return split;
}

void add_matrices(int **A, int **B, int **C, matrix_pt *A_pts, matrix_pt *B_pts)
{
	int size = A_pts -> x_end - A_pts -> x_start;
	
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			C[i][j] = A[i + A_pts -> x_start][j + A_pts -> y_start] + B[i + B_pts -> x_start][j + B_pts -> y_start];
}

void subs_matrices(int **A, int **B, int **C, matrix_pt *A_pts, matrix_pt *B_pts)
{
	int size = A_pts -> x_end - A_pts -> x_start;
	
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			C[i][j] = A[i + A_pts -> x_start][j + A_pts -> y_start] - B[i + B_pts -> x_start][j + B_pts -> y_start];
}

void free_matrix(int **X, int size)
{
	for(int i = 0; i < size; i++)
		free(X[i]);
		
	free(X);
}

void free_split(int ***X, int size)
{
	for(int i = 0; i < 4; i++)
		free_matrix(X[i], size);
}

void strassen_matrix_multi(int **A, int **B, int **C, matrix_pt *A_pts, matrix_pt *B_pts)
{
	int size = A_pts -> x_end - A_pts -> x_start;
	
	int new_size = size / 2;

	matrix_pt **split_A = split(A_pts);
	matrix_pt **split_B = split(B_pts);

	int s1[new_size], s2[new_size], s3[new_size], s4[new_size], s5[new_size], s6[new_size], s7[new_size], s8[new_size], s9[new_size], s10[new_size];

	add_matrices(A, A, s1, split_A[0], split_A[3]);
	add_matrices(A, A, s2, split_B[0], split_B[3]);
	add_matrices(A, A, s3, split_A[2], split_A[3]);
	subs_matrices(B, B, s4, split_B[1], split_B[3]);
	subs_matrices(B, B, s5, split_B[2], split_B[0]);
	add_matrices(A, A, s6, split_A[0], split_A[1]);
	subs_matrices(A, A, s7, split_A[2], split_A[0]);
	add_matrices(B, B, s8, split_B[]);
	subs_matrices(A, A, s9);
	add_matrices(B, B, s10);

	

	// strassen_matrix_multi(A, B,)

	printf("%d %d %d %d\n", A_pts -> x_start, A_pts -> x_end, A_pts -> y_start, A_pts -> y_end);
	printf("%d %d %d %d\n", B_pts -> x_start, B_pts -> x_end, B_pts -> y_start, B_pts -> y_end);
}

// Function to write the matrices into the output file
void writeToFile(FILE *outFPtr, int **A, int **B, int **C, int size)
{
	fprintf(outFPtr, "Matrix A: \n");

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			fprintf(outFPtr, "%d ", A[i][j]);

		fprintf(outFPtr, "\n");
	}

	fprintf(outFPtr, "\n\n");

	fprintf(outFPtr, "Matrix B: \n");

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			fprintf(outFPtr, "%d ", B[i][j]);

		fprintf(outFPtr, "\n");
	}

	fprintf(outFPtr, "\n\n");

	fprintf(outFPtr, "Matrix C: \n");

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			fprintf(outFPtr, "%d ", C[i][j]);

		fprintf(outFPtr, "\n");
	}
}