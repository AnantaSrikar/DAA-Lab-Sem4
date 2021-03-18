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

	int arr_1[size], arr_2[size];

	for(int i = 1; i <= size; i++)
		arr_1[i - 1] = input_arr[i];

	for(int i = size + 1; i <= size * 2; i++)
		arr_2[i - size - 1] = input_arr[i];

	// End of command line arguments

	// Function prototypes
	int getMedian(int [], int [], int);

	int median = getMedian(arr_1, arr_2, size);

	printf("Median = %d\n", median);

	return(0);
}

/* This function returns median of ar1[] and ar2[].
Assumptions in this function:
Both ar1[] and ar2[] are sorted arrays
Both have n elements */
int getMedian(int ar1[], int ar2[], int n)
{
	int i = 0; /* Current index of i/p array ar1[] */
	int j = 0; /* Current index of i/p array ar2[] */
	
	int m1 = -1, m2 = -1;

	/* Since there are 2n elements, median will be average
	of elements at index n-1 and n in the array obtained after
	merging ar1 and ar2 */
	for(int count = 0; count <= n; count++)
	{
		/*Below is to handle case where all elements of ar1[] are
		smaller than smallest(or first) element of ar2[]*/
		if (i == n)
		{
			m1 = m2;
			m2 = ar2[0];
			break;
		}

		/*Below is to handle case where all elements of ar2[] are
		smaller than smallest(or first) element of ar1[]*/
		else if (j == n)
		{
			m1 = m2;
			m2 = ar1[0];
			break;
		}
		/* equals sign because if two 
			arrays have some common elements */
		if (ar1[i] <= ar2[j])
		{
			m1 = m2; /* Store the prev median */
			m2 = ar1[i];
			i++;
		}
		else
		{
			m1 = m2; /* Store the prev median */
			m2 = ar2[j];
			j++;
		}
	}

	return (m1 + m2)/2;
}