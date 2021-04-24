/*
	Author: Ananta Srikar

	Given a value N, if we want to make change for N rupees, and we have
	infinite supply of each of Coins(i.e., { C1 , C2 , .. , Cm }), the program finds
	many ways can we make the change.

	Time Complexity: O(N * num_of_coins)
	Space Complexity: O(N)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char **argv)
{
	// Initial code to get all command line values

	if(argc < 3)
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

	int N = input_arr[0];
	int S[argc - 2];

	for(int i = 1; i < argc - 1; i++)
		S[i - 1] = input_arr[i];

	// End of command line arguments
	
	int findWaysCoinChange(int, int[], int);

	printf("Number of ways: %d\n", findWaysCoinChange(N, S, argc - 2));

	return(0);
}

// Main function
int findWaysCoinChange(int N, int S[], int size)
{
	int table[N + 1];

	for(int i = 0; i < N + 1; i++)
		table[i] = 0;

	// If given value is 0
	table[0] = 1;

	for(int i = 0; i < size; i++)
		for(int j = S[i]; j <= N; j++)
			table[j] += table[j - S[i]];

	return table[N];
}