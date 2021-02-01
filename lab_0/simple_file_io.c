/*
	Program to read input from a file and write output into another file

	Author: Ananta Srikar
*/

#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *inFPtr = NULL, *outFPtr;
	
	inFPtr = fopen("input.txt", "r");
	outFPtr = fopen("output.txt", "w");

	if(inFPtr == NULL)
	{
		fprintf(stderr, "File  'input.txt' doesn't exist, exiting...");
		return -1;
	}

	char c;

	// Copying the contents of input file into the output file
	while((c = fgetc(inFPtr)) != EOF)
		putc(c, outFPtr);

	fclose(inFPtr);
	
	return(0);
}