/*
	Author: Ananta Srikar

	Given n dice each with m faces, numbered from 1 to m, this program finds the number
	of ways to get sum X (Where X is the summation of values on each face
	when all the dice are thrown).
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char **argv)
{
	// Initial code to get all command line values
	
	if(argc != 4)
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

	int n = input_arr[0];
	int m = input_arr[1];
	int x = input_arr[2];

	// End of command line arguments
	
	int findWaysDice(int, int, int);

	printf("Number of ways: %d\n", findWaysDice(m, n, x));

	return(0);
}

// Main function
int findWaysDice(int m, int n, int x)
{
	// x is too high
	if(m * n <= x)
		return (m * n == x);

	// x is too low
	else if(n >= x)
		return (n == x);
	/*
		Create a table to store results of subproblems.  One extra 
		row and column are used for simpilicity (Number of dice
		is directly used as row index and sum is directly used
		as column index). The entries in 0th row and 0th column
		are never used.
	*/

	int table[n + 1][x + 1];
	
	// Initialisng table contents to 0
	for(int i = 0; i < n + 1; i++)
		for(int j = 0; j < x + 1; j++)
			table[i][j] = 0;
	
	// Table entries for only one dice
	for (int j = 1; j <= m && j <= x; j++)
		table[1][j] = 1;
	
	// Fill rest of the entries in table using recursive relation
	// i: number of dice, j: sum
	for (int i = 2; i <= n; i++)
		for (int j = 1; j <= x; j++)
			for (int k = 1; k <= m && k < j; k++)
				table[i][j] += table[i - 1][j - k];

	return table[n][x];
}