/*
	Program to search in a set of student records by considering a specified field (Hall Ticket
	Number, Name, or Team Number) by using binary search techniques.

	Author: Ananta Srikar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Singly linked list
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

	for(int j = 0; j < strlen(argv[1]); j++)
		if(!isdigit(argv[1][j]))
		{
			printf("Invalid arguments! Please go through README.md"); // Enter only numbers!
			return -1;
		}
	
	int field = atoi(argv[1]);

	if(!(field >= 1 && field <= 3))
	{
		printf("Invalid numbers entered. Please go through README.md");
		return -1;
	}

	if(field == 3)
	{
		for(int j = 0; j < strlen(argv[2]); j++)
			if(!isdigit(argv[2][j]))
			{
				printf("Enter a number for searching wrt team numebr"); // Enter only numbers!
				return -1;
			}
	}

	// End of command line arguments


	// Function prototypes
	student *getLinkedList(FILE*);

	student *binarySearch(student*, int, void*);
	
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

	student *results =  binarySearch(root, field, argv[2]);

	// Write the sorted list into file
	writeToFile(outFPtr, results);
	fclose(outFPtr);

	return(0);
}


// Function to get a doubly linked list from the contents of the input file
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

student *get_mid_node(student *start, student *end)
{
	if(start == NULL)
		return start;
	
	student *slow = start, *fast = start -> next;

	while(fast != end)
	{
		fast = fast -> next;

		if(fast != end)
		{
			slow = slow -> next;
			fast = fast -> next;
		}
	}

	return slow;
}

void copyStudent(student *node_1, student *node_2)
{
	if(node_1 == node_2)
		return;
	
	node_1 -> ht_no = node_2 -> ht_no;
	node_1 -> name = node_2 -> name;
	node_1 -> team_no = node_2 -> team_no;
	node_1 -> next = NULL;
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

void appendNode(student **root, student *node)
{
	student *temp = (student*)malloc(sizeof(student));

	copyStudent(temp, node);

	if(*root == NULL)
		*root = temp;

	else
	{
		student *temp2 = *root;

		while(temp2 != NULL)
		{
			if(temp2 -> next == NULL)
			{
				temp2 -> next = temp;
				break;
			}

			temp2 = temp2 -> next;
		}
	}
}

student *binarySearch(student *root, int field, void *search_data)
{
	if(root == NULL)
		return root;
	
	student *found = NULL, *start = root, *last = NULL;
	quickSort(root, field);
	
	student *temp = root;

	switch(field)
	{
		case 1:
			{
				char *search_ht_no = (char*)search_data;
				
				while (last == NULL || last != start)
				{
					student *mid = get_mid_node(start, last);
					
					if(mid == NULL)
						return NULL;

					if(strcmp(search_ht_no, mid -> ht_no) == 0)
					{
						appendNode(&found, mid);
						return found; //Not checking for another occurence since ht_no is unique
					}
						

					else if(strcmp(search_ht_no, mid -> ht_no) > 0)
						start = mid -> next;

					else
						last = mid;
				}
				
				break;
			}

		case 2:
			{
				char *search_name = (char*)search_data;

				while (last == NULL || last != start)
				{
					student *mid = get_mid_node(start, last);
					
					if(mid == NULL)
						return NULL;

					if(strcmp(search_name, mid -> name) == 0)
					{
						appendNode(&found, mid);

						// Checking for otehr occurences
						if(strcmp(search_name ,mid -> prev -> name) == 0)
							appendNode(&found, mid -> prev);
						
						if(strcmp(search_name ,mid -> next -> name) == 0)
							appendNode(&found, mid -> next);
						return found; 
					}
						

					else if(strcmp(search_name, mid -> name) > 0)
						start = mid -> next;

					else
						last = mid;
				}

				break;
			}

		case 3:
			{
				int search_team_no = atoi(search_data);

				while (last == NULL || last != start)
				{
					student *mid = get_mid_node(start, last);
					
					if(mid == NULL)
						return NULL;

					if(search_team_no == mid -> team_no)
					{
						appendNode(&found, mid);

						// Checking for otehr occurences
						if(search_team_no == mid -> prev -> team_no)
							appendNode(&found, mid -> prev);
						
						if(search_team_no == mid -> next -> team_no)
							appendNode(&found, mid -> next);
						return found; 
					}
						

					else if(search_team_no > mid -> team_no)
						start = mid -> next;

					else
						last = mid;
				}

				break;
			}
	}
	return found;
}


// Function to write the linked list into the output file
void writeToFile(FILE *outFPtr, student *root)
{
	if(root == NULL)
	{
		fprintf(outFPtr, "No results found!");
		return;
	}
	
	int count = 0;
	student *temp = root;

	while(temp != NULL)
	{
		count++;
		temp = temp -> next;
	}

	if(count == 1)
		fprintf(outFPtr, "Found 1 result:\n");
	else
		fprintf(outFPtr, "Found %d results:\n", count);

	temp = root;

	while(temp != NULL)
	{
		fprintf(outFPtr, "%s %s %d\n", temp -> ht_no, temp -> name, temp -> team_no);
		
		temp = temp -> next;
	}
}