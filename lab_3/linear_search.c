/*
	Program to search in a set of student records by considering a specified field (Hall Ticket
	Number, Name, or Team Number) by using Linear search techniques.

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

	student *linearSearch(student*, int, void*);
	
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

	student *results = linearSearch(root, field, argv[2]);

	// Write the sorted list into file
	writeToFile(outFPtr, results);
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

void copyStudent(student *node_1, student *node_2)
{
	if(node_1 == node_2)
		return;
	
	node_1 -> ht_no = node_2 -> ht_no;
	node_1 -> name = node_2 -> name;
	node_1 -> team_no = node_2 -> team_no;
	node_1 -> next = NULL;
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

student *linearSearch(student* root, int field, void *search_data)
{
	student *found = NULL, *temp = root;

	switch(field)
	{
		case 1:
			{
				char *search_ht_no = (char*)search_data;

				while(temp != NULL)
				{
					if(strcmp(search_ht_no, temp -> ht_no) == 0)
						appendNode(&found, temp);
					temp = temp -> next;
				}
				break;
			}

		case 2:
			{
				char *search_name = (char*)search_data;

				while(temp != NULL)
				{
					if(strcmp(search_name, temp -> name) == 0)
						appendNode(&found, temp);
					temp = temp -> next;
				}
				break;
			}

		case 3:
			{
				int search_team_no = atoi(search_data);

				while(temp != NULL)
				{
					if(search_team_no == temp -> team_no)
						appendNode(&found, temp);
					temp = temp -> next;
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