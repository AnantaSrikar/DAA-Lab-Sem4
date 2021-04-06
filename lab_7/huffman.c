/*
	Author: Ananta Srikar

	TODO: Add comments
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct file_char
{
	char ch;
	int freq;
};

typedef struct file_char file_char;

int main(int argc, char **argv)
{
	// Initial code to get all command line values
	
	if(argc != 2)
	{
		printf("Incorrect number of arguments! Please go through README.md\n");
		return -1;
	}

	// End of command line arguments

	// Function prototypes
	file_char *getCharFreq(FILE*);

	printf("File: %s\n", argv[1]);

	FILE *inFPtr = NULL, *outFPtr;

	inFPtr = fopen(argv[1], "r");
	// outFPtr = fopen("compressed.bin", "wb");

	if(inFPtr == NULL)
	{
		printf("Failed to open %s, does the file exist?\n", argv[1]);
		return -1;
	}

	getCharFreq(inFPtr);

	fclose(inFPtr);

	return(0);
}

file_char *getCharFreq(FILE *inFPtr)
{
	struct char_freq
	{
		char ch;
		int freq;
		struct char_freq *next;
	};

	typedef struct char_freq char_freq;

	char_freq *temp, *root = NULL;

	int in(char ch, char_freq *root)
	{
		char_freq *temp = root;
		
		while(temp != NULL)
		{
			if(temp -> ch == ch)
				return 1;

			temp = temp -> next;
		}

		return 0;
	}

	void append(char ch, char_freq *root)
	{
		char_freq *temp = root;

		while(temp != NULL)
		{
			if(temp -> next == NULL)
			{
				temp -> next = (char_freq*)malloc(sizeof(char_freq));
				temp -> next -> freq = 1;
			}
			
			temp = temp -> next;
		}
	}

	void add_count(char ch, char_freq *root)
	{
		char_freq *temp = root;

		while(temp != NULL)
		{
			if(temp -> ch == ch)
			{
				temp -> freq += 1;
				break;
			}
			
			temp = temp -> next;
		}
	}

	while(!feof(inFPtr))
	{
		char ch;
		fscanf(inFPtr, "%c", &ch);

		if(!in(ch, root))
			if(root == NULL)
			{
				root = (char_freq*)malloc(sizeof(char_freq));
				root -> freq = 1;
			}
			
			else
				append(ch, root);

		else
			add_count(ch, root);
	}

	temp = root;

	while(temp != NULL)
	{
		printf("Char: %c, freq: %d\n", temp -> ch, temp -> freq);
		temp = temp -> next;
	}


	// void append_char(char_freq)

	return NULL;
}