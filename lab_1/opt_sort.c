/*
	Program to sort a set of student records by considering a specified field (Hall Ticket
	Number, Name, or Team Number) by using Selection Sort and Insertion Sort techniques.

	Author: Ananta Srikar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Singly linked list
struct student
{
	char *ht_no;
	char *name;
	int team_no;

	struct student *next;
};

typedef struct student student;

int main()
{
	// Function prototypes
	student *getLinkedList(FILE*);
	student *getMin_team_no(student*);
	void selSort_team_no(student*);
	void swap(student*, student*);
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

	// Da sorting. TODO: change to command line args
	selSort_team_no(root);

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
					head = new_student;

				else
					temp -> next = new_student;

				temp = new_student;
				temp -> next = NULL;
		}
		cnt++;
	}

	return head;
}

// Function to swap the values inside the node efficiently
void swap(student *node_1, student *node_2)
{
	char *temp_ht_no = node_1 -> ht_no, *temp_name = node_1 -> name;
	int temp_team_no = node_1 -> team_no;

	node_1 -> ht_no = node_2 -> ht_no;
	node_1 -> name = node_2 -> name;
	node_1 -> team_no = node_2 -> team_no;

	node_2 -> ht_no = temp_ht_no;
	node_2 -> name = temp_name;
	node_2 -> team_no = temp_team_no;
}

// Function to get the address of the node having the minimum value
student* getMin_team_no(student* start)
{
	student *min_student, *temp;

	min_student = temp = start;

	while(temp != NULL)
	{
		if((temp -> team_no) < (min_student -> team_no))
			min_student = temp;

		temp = temp -> next;
	}

	return min_student;
}

// Selection sort based on based on team number
void selSort_team_no(student* root)
{
	student *temp = root, *hulu;

	while(temp != NULL)
	{
		if(temp -> next != NULL)
			swap(temp, getMin_team_no(temp));
		
		temp = temp -> next;
	}
}

// Function to write the linked list into the output file
void writeToFile(FILE *outFPtr, student *root)
{
	student *temp = root;

	while(temp != NULL)
	{
		fprintf(outFPtr, "%s %s %d\n", temp -> ht_no, temp -> name, temp -> team_no);
		
		temp = temp -> next;
	}
}