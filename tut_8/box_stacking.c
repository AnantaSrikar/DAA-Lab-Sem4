/*
	Author: Ananta Srikar

	Box stacking problem.

	Time Complexity: O(N ^ 2)
	Space Complexity: O(N)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Box
{
	// Each box has a height, width and depth
	int h;
	int w;
	int d;
};

typedef struct Box Box;

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

	Box boxes[size];

	for(int i = 1; i < argc - 1; i += 3)
	{
		boxes[i / 3].h = input_arr[i];
		boxes[i / 3].w = input_arr[i + 1];
		boxes[i / 3].d = input_arr[i + 2];
	}

	// End of command line arguments

	// Function prototype
	int maxBoxStackHeight(Box[], int);

	printf("Number of ways: %d\n", maxBoxStackHeight(boxes, size));

	return(0);
}

// Returns the minimum of two numbers XD
int min(int x, int y)
{
	return (x < y)? x : y;
}

// Returns the maximum of two numbers XDD
int max (int x, int y)
{
	return (x > y)? x : y;
}

/*
	Following function is needed for library function qsort(). We
	use qsort() to sort boxes in decreasing order of base area.
*/
int compare (const void *a, const void * b)
{
	return((*(Box*)b).d * (*(Box*)b).w) - ((*(Box*)a).d * (*(Box*)a).w);
}

// Returns the height of the tallest stack that can be formed with give type of boxes
int maxBoxStackHeight(Box arr[], int n)
{
	/* Create an array of all rotations of given boxes
	For example, for a box {1, 2, 3}, we consider three
	instances{{1, 2, 3}, {2, 1, 3}, {3, 1, 2}} */
	
	Box rot[3 * n];
	int index = 0;

	for (int i = 0; i < n; i++)
	{
		// Copy the original box
		rot[index].h = arr[i].h;
		rot[index].d = max(arr[i].d, arr[i].w);
		rot[index].w = min(arr[i].d, arr[i].w);
		index++;

		// First rotation of box
		rot[index].h = arr[i].w;
		rot[index].d = max(arr[i].h, arr[i].d);
		rot[index].w = min(arr[i].h, arr[i].d);
		index++;

		// Second rotation of box
		rot[index].h = arr[i].d;
		rot[index].d = max(arr[i].h, arr[i].w);
		rot[index].w = min(arr[i].h, arr[i].w);
		index++;
	}

	// Now the number of boxes is 3n
	n *= 3;
	
	// Sort the array 'rot[]' in non-increasing order of base area
	qsort(rot, n, sizeof(rot[0]), compare);
	
	// The following two lines prints all rotations
	for(int i = 0; i < n; i++)
		printf("%d x %d x %d\n", rot[i].h, rot[i].w, rot[i].d);

	// Initialize msh values for all indexes msh[i] --> Maximum possible Stack Height with box i on top 
	int msh[n];
	for(int i = 0; i < n; i++)
		msh[i] = rot[i].h;

	// Compute optimized msh values in bottom up manner
	for(int i = 1; i < n; i++)
		for(int j = 0; j < i; j++)
			if(rot[i].w < rot[j].w && rot[i].d < rot[j].d && msh[i] < msh[j] + rot[i].h)
				msh[i] = msh[j] + rot[i].h;
	 
	// Pick maximum of all msh values
	int max = msh[0];
	
	for(int i = 0; i < n; i++)
	if(max < msh[i])
		max = msh[i];

	return max;
}