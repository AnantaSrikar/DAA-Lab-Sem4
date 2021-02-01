/*
	Program to find the number of lines, words and characters in a file.

	Author: Ananta Srikar
*/

#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *inFPtr = NULL;

	inFPtr = fopen("input.txt", "r");

	if(inFPtr == NULL)
	{
		fprintf(stderr, "File 'input.txt' doesn't exist, exiting...");
		return -1;
	}

	int chars_in_file, num_chars, num_words, num_lines;
	chars_in_file = num_chars = num_words = num_lines = 0;

	char c;

	while((c = fgetc(inFPtr)) != EOF)
		chars_in_file++;

	// If there's atleast one character in the file
	if(chars_in_file > 0)
		num_lines = 1;

	// Resetting pointer to the start of file
	fseek(inFPtr, 0, SEEK_SET);

	char content[chars_in_file];

	for(int i = 0; i < chars_in_file; i++)
		fscanf(inFPtr, "%c", &content[i]);

	for(int i = 0; i < chars_in_file; i++)
	
		if(content[i] == '\n')
			num_lines++;

		else
		{
			// More about this in the README.md
			if(((content[i] >= 'a' && content[i] <= 'z') || (content[i] >= 'A' && content[i] <= 'Z')) && (content[i + 1] == '!' || content[i + 1] == '?' || content[i + 1] == ' ' || content[i + 1] == '.' || content[i + 1] == ',' || content[i + 1] == ';' || content[i + 1] == '\n' || i == chars_in_file - 1))
				num_words++;
			
			if(content[i] != ' ')
				num_chars++;
		}

	printf("\nCharacter count = %d\n", num_chars);
	printf("Word count = %d\n", num_words);
	printf("Line count = %d\n", num_lines);

	return(0);
}