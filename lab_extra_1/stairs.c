/*
	Author: Ananta Srikar

	Program to find the numeber of ways a person can climb N stairs,
	when 1 or 2 stairs are climbed at a time.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char **argv)
{
	// Initial code to get all command line values
	
	if(argc != 2)
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

	if(!(N > 0))
	{
		printf("Number of stairs can't be 0 or negative -_-\n");
		return -1;
	}

	// End of command line arguments

	// Function prototype
	int getWaysToClimb(int);

	printf("%d\n", getWaysToClimb(N));

	return(0);
}

// Function to find the number of ways to climb N stairs. Time complexity: O(N)
// If observed closely, the pattern is the fibonacci series :)
int getWaysToClimb(int N)
{
	int a = 1, b = 2, c = 3;

	if(N == 1)
		return a;
	
	else if(N == 2)
		return b;
	
	for(int i = 3; i < N + 1; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}

	return c;
}