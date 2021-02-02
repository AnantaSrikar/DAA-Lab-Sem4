/*
	Program to sort a set of student records by considering a specified field (Hall Ticket
	Number, Name, or Team Number) by using Selection Sort and Insertion Sort techniques.

	Author: Ananta Srikar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	student *getLinkedList(FILE*);
	FILE *inFPtr = NULL;
	
	inFPtr = fopen("DAALab_Input1.txt", "r");

	if(inFPtr == NULL)
	{
		fprintf(stderr, "File 'DAALab_Input1.txt' doesn't exist, exiting...");
		return -1;
	}

	student *root = getLinkedList(inFPtr);
	fclose(inFPtr);

	student *temp = root;

	while (temp != NULL)
	{
		printf("Person: '%s' '%s' %d\n", temp -> ht_no, temp -> name, temp -> team_no);
		temp = temp -> next;
	}

	return(0);
}

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