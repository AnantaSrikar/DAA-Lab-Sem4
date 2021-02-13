/*
	Program to sort a set of student records by considering the fields in a specific order (Team Number,
	Hall ticket number and name) by using Selection Sort and Insertion Sort techniques.

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
};

typedef struct student student;

int main(int argc, char **argv)
{
	// Initial code to get all command line values

	if(argc != 2)
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

	int sort_meth = atoi(argv[1]);

	if(!(sort_meth == 1 || sort_meth == 2))
	{
		printf("Invalid numbers entered. Please go through README.md");
		return -1;
	}

	// End of command line arguments


	// Function prototypes
	student *getLinkedList(FILE*);

	void selSort(student*);
	void insSort(student*);
	
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
			selSort(root);
			break;

	case 2:
			insSort(root);
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
	// No need to swap if its the same node
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

// Function that works similar to a '=' operator, except for nodes
void copyStudent(student *node_1, student *node_2)
{
	if(node_1 == node_2)
		return;
	
	node_1 -> ht_no = node_2 -> ht_no;
	node_1 -> name = node_2 -> name;
	node_1 -> team_no = node_2 -> team_no;
}

// Function to get the address of the node having the minimum value
student* getMinStudent(student* start)
{
	student *min_student, *temp;

	min_student = temp = start;

	while (temp != NULL)
	{
		if((temp -> team_no) < (min_student -> team_no))
			min_student = temp;

		else if((temp -> team_no) == (min_student -> team_no) && strcmp(temp -> ht_no, min_student -> ht_no) < 0)
			min_student = temp;

		else if((temp -> team_no) == (min_student -> team_no) && strcmp(temp -> ht_no, min_student -> ht_no) == 0 && strcmp(temp -> name, min_student -> name) == 0)
			min_student = temp;

		temp = temp -> next;
	}

	return min_student;
}

// Selection sort for all three fields
void selSort(student* root)
{
	student *temp = root;

	while(temp != NULL)
	{
		if(temp -> next != NULL)
			swap(temp, getMinStudent(temp));

		temp = temp -> next;
	}
}

// Instertion sort for all three fields
void insSort(student *root)
{
	if(root == NULL || root -> next == NULL)
		return;

	student *search_val_node = (student*)malloc(sizeof(student));
	student *temp_1 = root -> next;

	while(temp_1 != NULL)
	{
		student *temp_2 = root;
		
		copyStudent(search_val_node, temp_1);
		int found = 0;

		while(temp_2 != temp_1)
		{
			if(temp_2 -> team_no > temp_1 -> team_no && found == 0)
			{

				copyStudent(search_val_node, temp_2);						
				copyStudent(temp_2, temp_1);

				found = 1;
				temp_2 = temp_2 -> next;
			}

			else if(temp_2 -> team_no == temp_1 -> team_no && strcmp(temp_1 -> ht_no, temp_2 -> ht_no) < 0 && found == 0)
			{
				copyStudent(search_val_node, temp_2);						
				copyStudent(temp_2, temp_1);

				found = 1;
				temp_2 = temp_2 -> next;
			}

			else if(temp_2 -> team_no == temp_1 -> team_no && strcmp(temp_1 -> ht_no, temp_2 -> ht_no) == 0 && strcmp(temp_1 -> name, temp_2 -> name) < 0 && found == 0)
			{
				copyStudent(search_val_node, temp_2);						
				copyStudent(temp_2, temp_1);

				found = 1;
				temp_2 = temp_2 -> next;
			}
			
			else
			{
				if(found == 1)
					swap(temp_2, search_val_node);

				temp_2 = temp_2 -> next;
			}
		}

		copyStudent(temp_2, search_val_node);
		temp_1 = temp_1 -> next;

	}

	free(search_val_node);
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