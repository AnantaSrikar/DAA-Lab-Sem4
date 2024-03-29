/*
	Program to sort a set of student records by considering a specified field (Hall Ticket
	Number, Name, or Team Number) by using Merge Sort and Quick Sort techniques.

	Author: Ananta Srikar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Doubly linked list
struct student
{
	char *ht_no;
	char *name;
	int team_no;

	struct student *next;
	struct student *prev;
};

typedef struct student student;

int main(int argc, char **argv)
{
	// Initial code to get all command line values

	if(argc != 3)
	{
		printf("Wrong number of arguments. Please go through README.md");
		return -1;
	}

	for(int i = 1; i <= 2; i++)
	{
		for(int j = 0; j < strlen(argv[i]); j++)
			if(!isdigit(argv[i][j]))
			{
				printf("Invalid arguments! Please go through README.md"); // Enter only numbers!
				return -1;
			}
	}

	int sort_meth = atoi(argv[1]);
	int field = atoi(argv[2]);

	if(!(sort_meth == 1 || sort_meth == 2) || !(field >= 1 && field <= 3))
	{
		printf("Invalid numbers entered. Please go through README.md");
		return -1;
	}

	// End of command line arguments


	// Function prototypes
	student *getLinkedList(FILE*);

	student *mergeSort(student*, int);
	void quickSort(student*, int);
	
	void writeToFile(FILE*, student*);

	// File I/O
	FILE *inFPtr = NULL, *outFPtr;
	
	inFPtr = fopen("DAALab_input1.txt", "r");
	outFPtr = fopen("DAALab_output1.txt", "w");

	if(inFPtr == NULL)
	{
		fprintf(stderr, "File 'DAALab_input1.txt' doesn't exist, exiting...");
		return -1;
	}
	// End of file I/O

	// Making a linked list from the file
	student *root = getLinkedList(inFPtr);
	fclose(inFPtr);

	// switch to sort according to user input
	switch(sort_meth)
	{
	case 1:
			root = mergeSort(root, field);
			break;

	case 2:
			quickSort(root, field);
			break;

	default:
			printf("Something bad happened :(\n");
	}

	// Write the sorted list into file
	writeToFile(outFPtr, root);
	fclose(outFPtr);

	return(0);
}


// Function to get a linked list from the contents of the input file
student *getLinkedList(FILE *inFPtr)
{
	student *head = NULL, *temp, *new_student;

	char str[15];
	int cnt = 0;

	while(!feof(inFPtr))
	{
		switch(cnt % 3)
		{
			case 0:
				new_student = (student*)malloc(sizeof(student));
				new_student -> ht_no = (char*)(malloc(sizeof(char) * 10));

				fscanf(inFPtr, "%s ", new_student -> ht_no);

				break;
			
			case 1:
				fscanf(inFPtr, "%s ", str);
				new_student -> name = (char*)malloc(sizeof(char) * strlen(str));
				strcpy(new_student -> name, str);

				break;
			
			case 2:
				fscanf(inFPtr, "%d", &(new_student -> team_no));

				// Adding the new node to the linked list

				if(head == NULL)
				{
					head = new_student;
					head -> prev = NULL;
				}

				else
				{
					temp -> next = new_student;
					new_student -> prev = temp;
				}

				temp = new_student;
				temp -> next = NULL;
		}
		cnt++;
	}

	return head;
}

// Function to swap the values inside the node efficiently
void swapNodes(student *node_1, student *node_2)
{
	if(node_1 == node_2)
		return;
	
	char *temp_ht_no = node_1 -> ht_no, *temp_name = node_1 -> name;
	int temp_team_no = node_1 -> team_no;

	node_1 -> ht_no = node_2 -> ht_no;
	node_1 -> name = node_2 -> name;
	node_1 -> team_no = node_2 -> team_no;

	node_2 -> ht_no = temp_ht_no;
	node_2 -> name = temp_name;
	node_2 -> team_no = temp_team_no;
}

// Helper functions for merge sort

// Split a doubly linked list (DLL) into 2 DLLs of half sizes
student *split(student *root)
{ 
	student *fast = root, *slow = root;

	while (fast -> next && fast -> next -> next)
	{
		fast = fast -> next -> next;
		slow = slow -> next;
	} 

	student *temp = slow -> next;
	slow -> next = NULL;

	return temp;
}

// Merge Routing for mergeSort
student *mergeRoutine(student *left, student *right, int field)
{ 
	// If left linked list is empty 
	if (left == NULL)
		return right;

	// If right linked list is empty 
	if (right == NULL)
		return left;

	int isSmol = 0;

	switch (field)
	{
		case 1:
				if(strcmp(left -> ht_no, right -> ht_no) < 0)
					isSmol = 1;
				break;

		case 2:
				if(strcmp(left -> name, right -> name) < 0)
					isSmol = 1;
				break;
		case 3:
				if((left -> team_no) < (right -> team_no))
					isSmol = 1;
				break;
		
		default:
			break;
	}

	// Pick the smaller value 
	if (isSmol)
	{ 
		left -> next = mergeRoutine(left -> next, right, field);
		left -> next -> prev = left;
		left -> prev = NULL;
		return left;
	}

	else
	{ 
		right -> next = mergeRoutine(left, right -> next, field);
		right -> next -> prev = right;
		right -> prev = NULL;
		return right;
	}
}

student *mergeSort(student *root, int field)
{
	if(root == NULL || root -> next == NULL)
		return root;
		
	student *right = split(root);

	// Recurring for left and right halves
	root = mergeSort(root, field);
	right = mergeSort(right, field);

	// Merge the two sorted halves
	return mergeRoutine(root, right, field);
}

// Helper functions for Quick Sort

// A utility function to find last node of the linked list
student *lastNode(student *root)
{
	while (root && root -> next)
		root = root -> next;
	return root;
}

/*
	Considers the last element as pivot, places the pivot element at its correct
	position in sorted dll, and places all smaller (smaller than pivot) to left
	of pivot and all greater elements to right of pivot.
*/
student* partition(student *front, student *last, int field)
{
	// set pivot as last element

	int swap = 0;
	student *pivot = last;
	student *temp_1 = front, *temp_2 = front -> prev;
	
	while(temp_1 != last)
	{
		switch (field)
		{
			case 1:
					if(strcmp(temp_1 -> ht_no, pivot -> ht_no) < 0)
						swap = 1;
					else
						swap = 0;
					break;

			case 2:
					if(strcmp(temp_1 -> name, pivot -> name) < 0)
						swap = 1;
					else
						swap = 0;
					break;
			case 3:
					if((temp_1 -> team_no) < (pivot -> team_no))
						swap = 1;
					else
						swap = 0;
					break;
		}

		if (swap)
		{
			if(temp_2 == NULL)
				temp_2 = front;
			else
				temp_2 = temp_2 -> next;

			swapNodes(temp_2, temp_1);
		}

		temp_1 = temp_1 -> next;
	}

	if(temp_2 == NULL)
		temp_2 = front;
	else
		temp_2 = temp_2 -> next;
	
	swapNodes(temp_2, last);
	return temp_2;
}

/* A recursive implementation of quicksort for linked list */
void recQuickSort(student *front, student *last, int field)
{
	if (last != NULL && front != last && front != last -> next)
	{
		student *part = partition(front, last, field);
		recQuickSort(front, part -> prev, field);
		recQuickSort(part -> next, last, field);
	}
}

// The main function to sort a linked list.
void quickSort(student *head, int field)
{
	// Call the recursive QuickSort
	recQuickSort(head, lastNode(head), field);
}

// Function to write the linked list into the output file
void writeToFile(FILE *outFPtr, student *root)
{
	fprintf(outFPtr, "HT_NO NAME TEAM_NO\n");
	
	student *temp = root;

	while(temp != NULL)
	{
		fprintf(outFPtr, "%s %s %d\n", temp -> ht_no, temp -> name, temp -> team_no);
		
		temp = temp -> next;
	}
}