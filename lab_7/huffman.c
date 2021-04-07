/*
	Author: Ananta Srikar

	TODO: - Get the huffman tree node
			write encoded bit string to file
			implement decoding
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
	file_char *getCharFreq(FILE*, int*);

	printf("File: %s\n", argv[1]);

	FILE *inFPtr = NULL, *outFPtr;

	inFPtr = fopen(argv[1], "r");
	// outFPtr = fopen("compressed.bin", "wb");

	if(inFPtr == NULL)
	{
		printf("Failed to open %s, does the file exist?\n", argv[1]);
		return -1;
	}

	int char_num;
	file_char *all_char_freqs = getCharFreq(inFPtr, &char_num);

	printf("char_num = %d\n", char_num);

	fclose(inFPtr);

	return(0);
}

file_char *getCharFreq(FILE *inFPtr, int *char_num)
{
	// Temporary linked list to hold the frequecies of all the words in a given file
	struct char_freq
	{
		char ch;
		int freq;
		struct char_freq *next;
	};

	typedef struct char_freq char_freq;

	char_freq *temp, *root = NULL;
	int char_cnt = 0;

	// Function to check if a given character is already in the linked list
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

	// Function to append a character to the linked list
	void append(char ch, char_freq *root)
	{
		char_freq *temp = root;

		while(temp != NULL)
		{
			if(temp -> next == NULL)
			{
				temp -> next = (char_freq*)malloc(sizeof(char_freq));

				temp -> next -> ch = ch;
				temp -> next -> freq = 1;
				temp -> next -> next = NULL;

				break;
			}
			
			temp = temp -> next;
		}
	}

	// Function to increase the frequency count of a character in the linked list
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

	void swap_nodes(char_freq *n1, char_freq *n2)
	{
		char temp_ch = n1 -> ch;
		int temp_char_freq = n1 -> freq;

		n1 -> ch = n2 -> ch;
		n1 -> freq = n2 -> freq;

		n2 -> ch = temp_ch;
		n2 -> freq = temp_char_freq;
	}

	// Function to sort character frequency in increasing order
	void sort_list(char_freq *root)
	{
		char_freq *temp1 = root, *temp2 = root;
		
		while(temp1 != NULL)
		{
			temp2 = root;

			while(temp2 != NULL)
			{
				if(temp2 -> next != NULL && temp2 -> freq > temp2 -> next -> freq)
					swap_nodes(temp2, temp2 -> next);
				
				temp2 = temp2 -> next;
			}
			temp1 = temp1 -> next;
		}
	}

	// Iterating through all the characters in the file
	while(!feof(inFPtr))
	{
		char ch;
		fscanf(inFPtr, "%c", &ch);

		// if the scanned character isn't in the liked list
		if(!in(ch, root))
		{
			if(root == NULL)
			{
				root = (char_freq*)malloc(sizeof(char_freq));
				root -> freq = 1;
				root -> next = NULL;
			}
			
			else
				append(ch, root);

			char_cnt++;
		}

		else
			add_count(ch, root);
	}

	// Sorting the list
	sort_list(root);

	// Saving the value of the number of unique chars
	*char_num = char_cnt;

	temp = root;

	// TODO: do we need to sort them based on frequency, for building the binary tree?

	file_char *file_char_root = (file_char*)malloc(char_cnt * sizeof(file_char));

	// Copying all the frequencies into a array, since its easier to use :) (not the most efficient way but ok ¯\_(ツ)_/¯)
	for(int i = 0; i < char_cnt; i++, temp = temp -> next)
	{
		file_char_root[i].ch = temp -> ch;
		file_char_root[i].freq = temp -> freq;
	}

	for(int i = 0; i < char_cnt; i++)
		printf("'%c': %d\n", file_char_root[i].ch, file_char_root[i].freq);

	return file_char_root;
}