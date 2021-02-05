/*
	Program to sort a set of student records by considering a specified field (Hall Ticket
	Number, Name, or Team Number) by using Selection Sort and Insertion Sort techniques.

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
	student *getMin_team_no(student*);

	void selSort(student*, int);
	void insSort(student*, int);
	
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
			selSort(root, field);
			break;

	case 2:
			insSort(root, field);
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
	char *temp_ht_no = node_1 -> ht_no, *temp_name = node_1 -> name;
	int temp_team_no = node_1 -> team_no;

	node_1 -> ht_no = node_2 -> ht_no;
	node_1 -> name = node_2 -> name;
	node_1 -> team_no = node_2 -> team_no;

	node_2 -> ht_no = temp_ht_no;
	node_2 -> name = temp_name;
	node_2 -> team_no = temp_team_no;
}

// Function to get the address of the node having the minimum value wrt a field
student* getMinStudent(student* start, int field)
{
	student *min_student, *temp;

	min_student = temp = start;

	while(temp != NULL)
	{
		switch(field)
		{
		case 1:
				if(strcmp(temp -> ht_no, min_student -> ht_no) < 0)
					min_student = temp;
				break;

		case 2:
				if(strcmp(temp -> name, min_student -> name) < 0)
					min_student = temp;
				break;

		case 3:
				if((temp -> team_no) < (min_student -> team_no))
					min_student = temp;
				break;
		
		default:
				printf("Something bad happened!!\n");
		}

		temp = temp -> next;
	}

	return min_student;
}

/*
	Following is the mapping done for fields for both the sorting methods
	1 - Hall Ticket number
	2 - Name
	3 - Team number
*/

// Selection sort for all three fields
void selSort(student* root, int field)
{
	student *temp = root;

	while(temp != NULL)
	{
		if(temp -> next != NULL)
			swap(temp, getMinStudent(temp, field));
		
		temp = temp -> next;
	}
}

// Instertion sort for all three fields
void insSort(student *root, int field)
{
	if(root == NULL || root -> next == NULL)
		return;

	student *temp_1 = root -> next;

	while(temp_1 != NULL)
	{
		student *temp_2 = root;

		switch(field)
		{
			case 1:
			{
				char *search_val = temp_1 -> ht_no;
				int found = 0;


				while(temp_2 != temp_1)
				{
					if(strcmp(temp_1 -> ht_no, temp_2 -> ht_no) < 0 && found == 0)
					{
						search_val = temp_2 -> ht_no;
						temp_2 -> ht_no = temp_1 -> ht_no;
						found = 1;
						temp_2 = temp_2 -> next;
					}
					
					else
					{
						if(found == 1)
						{
							char *temp = search_val;
							search_val = temp_2 -> ht_no;
							temp_2 -> ht_no = temp;
						}

						temp_2 = temp_2 -> next;
					}
				}
				temp_2 -> ht_no = search_val;
				temp_1 = temp_1 -> next;

				break;
			}

			case 2:
			{
				char *search_val = temp_1 -> name;
				int found = 0;


				while(temp_2 != temp_1)
				{
					if(strcmp(temp_1 -> name, temp_2 -> name) < 0 && found == 0)
					{
						search_val = temp_2 -> name;
						temp_2 -> name = temp_1 -> name;
						found = 1;
						temp_2 = temp_2 -> next;
					}
					
					else
					{
						if(found == 1)
						{
							char *temp = search_val;
							search_val = temp_2 -> name;
							temp_2 -> name = temp;
						}

						temp_2 = temp_2 -> next;
					}
				}
				temp_2 -> name = search_val;
				temp_1 = temp_1 -> next;

				break;
			}

			case 3:
			{
				int search_val = temp_1 -> team_no;
				int found = 0;


				while(temp_2 != temp_1)
				{
					if(temp_2 -> team_no > temp_1 -> team_no && found == 0)
					{
						search_val = temp_2 -> team_no;
						temp_2 -> team_no = temp_1 -> team_no;
						found = 1;
						temp_2 = temp_2 -> next;
					}
					
					else
					{
						if(found == 1)
						{
							int temp = search_val;
							search_val = temp_2 -> team_no;
							temp_2 -> team_no = temp;
						}

						temp_2 = temp_2 -> next;
					}
				}
				temp_2 -> team_no = search_val;
				temp_1 = temp_1 -> next;

				break;
			}
			
			default:
				break;
		}
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