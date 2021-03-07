/*
	Program to sort a set of student records by their Hall Ticket numbers using Tree Sort techniques.

	Author: Ananta Srikar
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Binary tree
struct student
{
	char *ht_no;
	char *name;
	int team_no;

	struct student *left;
	struct student *right;
};

typedef struct student student;

int main(int argc, char **argv)
{
	// Function prototypes
	student *treeSort(FILE*);
	void inOrderFileWrite(FILE*, student*);

	// File I/O
	FILE *inFPtr = NULL, *outFPtr;
	
	inFPtr = fopen("DAALab_input1.txt", "r");
	outFPtr = fopen("DAALab_output1.txt", "w");

	// Checking for the existence of the input file
	if(inFPtr == NULL)
	{
		fprintf(stderr, "File 'DAALab_input1.txt' doesn't exist, exiting...");
		return -1;
	}
	// End of file I/O

	// Creating the binary search tree
	student *bin_search_tree = treeSort(inFPtr);

	// Writing the in-order traversal of the created tree to the file
	inOrderFileWrite(outFPtr, bin_search_tree);

	return(0);
}

// Helper function for get getBinarySortTree
void insertInTree(student **root, student *cur_node)
{
	if((*root) == NULL)
		(*root) = cur_node;

	else
	{
		if(strcmp(cur_node -> ht_no, (*root) -> ht_no) < 0)
			insertInTree(&((*root) -> left), cur_node);
		
		else
			insertInTree(&((*root) -> right), cur_node);
	}
}

// Function that returns a binary search tree
student *treeSort(FILE *inFPtr)
{
	student *head = NULL, *temp, *new_student;

	char str[15];

	while(!feof(inFPtr))
	{
		// Making a new node
		new_student = (student*)malloc(sizeof(student));
		new_student -> ht_no = (char*)(malloc(sizeof(char) * 10));

		fscanf(inFPtr, "%s %s %d", new_student -> ht_no, str, &(new_student -> team_no));

		new_student -> name = (char*)malloc(sizeof(char) * strlen(str));
		strcpy(new_student -> name, str);

		insertInTree(&head, new_student);
	}

	return head;
}

// Function to write the sorted binary tree to a file
void inOrderFileWrite(FILE *outFPtr, student *node)
{
	if(node == NULL)
		return;
	
	inOrderFileWrite(outFPtr, node -> left);
	
	fprintf(outFPtr, "%s %s %d\n", node -> ht_no, node -> name, node -> team_no);

	inOrderFileWrite(outFPtr, node -> right);
}