/*
	Author: Ananta Srikar

	Program to dind the largest number of N digits that can be made with a
	given sum of digits S.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char **argv)
{
	// Initial code to get all command line values
	
	if(argc != 3)
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
	int S = input_arr[1];

	if(S > N * 9) // There would be no N digit number whose sum would be S
	{
		printf("-1");
		return 0;
	}

	// End of command line arguments

	// Function prototype
	void find_password(int N, int S);

	find_password(N, S);

	printf("\n");

	return(0);
}

// Function to find the password. Time complexity: O(N)
void find_password(int N, int S)
{
	for(int i = 0; i < N; i++)
	{
		if(S > 9)
		{
			printf("9");
			S -= 9;
		}
		
		else if(S != 0)
		{
			printf("%d", S);
			S = 0;
		}

		else
			printf("0");
	}
}