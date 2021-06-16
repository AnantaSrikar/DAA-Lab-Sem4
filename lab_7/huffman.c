/*
	Author: Ananta Srikar

	TODO: - implement decoding
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

// Structure to store character frequencies
struct file_char
{
	char ch;
	int freq;
};

// A Huffman tree node
struct MinHeapNode
{
	// One of the input characters
	char data;

	// Frequency of the character
	unsigned freq;

	// Left and right child of this node
	struct MinHeapNode *left, *right;
};

struct huff_code
{
	char ch;
	char *code;
};

typedef struct file_char file_char;
typedef struct MinHeapNode MinHeapNode;
typedef struct huff_code huff_code;

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
	int isTxtFile(char[]);
	char *getRootName(char[]);

	file_char *getCharFreq(FILE*, int*);
	huff_code *getHuffmanTree(file_char*, int, MinHeapNode**);

	void compressFile(FILE*, FILE*, FILE*, huff_code*, int);
	void decompressFile(FILE*, FILE*, huff_code*, MinHeapNode*);

	// printf("File: %s\n", argv[1]);
	char cmp_name[strlen(argv[1])], dat_name[strlen(argv[1])];

	strcpy(cmp_name, getRootName(argv[1]));
	strcpy(dat_name, getRootName(argv[1]));
	strcat(cmp_name, ".cmp");
	strcat(dat_name, ".dat");

	// printf("Root name: %s\n", getRootName(argv[1]));
	printf("Cmp: %s\n", cmp_name);
	printf("Dat: %s\n", dat_name);

	FILE *inFPtr = NULL, *outCmpFPtr, *outDatFPtr;

	inFPtr = fopen(argv[1], "r");
	outCmpFPtr = fopen(cmp_name, "wb");
	outDatFPtr = fopen(dat_name, "w");

	// Check if the file is a txt file
	if(!isTxtFile(argv[1]))
	{
		printf("Given file is NOT a text file! Please check and try again.");
		return -1;
	}

	if(inFPtr == NULL)
	{
		printf("Failed to open %s, does the file exist?\n", argv[1]);
		return -1;
	}

	int char_num;
	file_char *all_char_freqs = getCharFreq(inFPtr, &char_num);

	printf("\n\nchar_num = %d\n\n", char_num);

	MinHeapNode *root;

	huff_code *all_codes = getHuffmanTree(all_char_freqs, char_num, &root);

	for(int i = 0; i < char_num; i++)
		printf("'%c' = '%s'\n", all_codes[i].ch, all_codes[i].code);

	compressFile(inFPtr, outCmpFPtr, outDatFPtr, all_codes, char_num);

	fclose(inFPtr);
	fclose(outCmpFPtr);
	fclose(outDatFPtr);

	FILE *comFPtr = NULL, *datFPtr = NULL;

	comFPtr = fopen(cmp_name, "rb");
	datFPtr = fopen(dat_name, "r");

	if(comFPtr == NULL || datFPtr == NULL)
	{
		printf("Unable to open compressed file :(\n");
		return -1;
	}

	decompressFile(comFPtr, datFPtr, all_codes, root);

	fclose(comFPtr);
	fclose(datFPtr);

	return(0);
}

// Function to check if the given file is a text file
int isTxtFile(char file_name[])
{
	char ext[] = ".txt";
	int file_name_length = strlen(file_name);

	for(int i = file_name_length - 4; i < file_name_length; i++)
		if(file_name[i] != ext[i - (file_name_length - 4)])
			return 0;

	return 1;
}

char *getRootName(char file_name[])
{
	char *root_name = (char*)malloc((strlen(file_name)) * sizeof(char));
	
	for(int i = 0; i < strlen(file_name) - 4; i++)
		root_name[i] = file_name[i];

	return root_name;
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
				root -> ch = ch;
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


huff_code *getHuffmanTree(file_char *all_char_freq, int size, MinHeapNode **root)
{
	// A Min Heap: Collection of
	// min-heap (or Huffman tree) nodes
	struct MinHeap
	{
		// Current size of min heap
		unsigned size;

		// capacity of min heap
		unsigned capacity;

		// Array of minheap node pointers
		struct MinHeapNode** array;
	};

	// A utility function allocate a new
	// min heap node with given character
	// and frequency of the character
	struct MinHeapNode* newNode(char data, unsigned freq)
	{
		struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));

		temp -> left = temp -> right = NULL;
		temp -> data = data;
		temp -> freq = freq;

		return temp;
	}

	// A utility function to create
	// a min heap of given capacity
	struct MinHeap* createMinHeap(unsigned capacity)
	{
		struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));

		// current size is 0
		minHeap -> size = 0;

		minHeap -> capacity = capacity;

		minHeap -> array = (struct MinHeapNode**)malloc(minHeap -> capacity * sizeof(struct MinHeapNode*));
		return minHeap;
	}

	// A utility function to
	// swap two min heap nodes
	void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
	{
		struct MinHeapNode* t = *a;
		*a = *b;
		*b = t;
	}

	// The standard minHeapify function.
	void minHeapify(struct MinHeap* minHeap, int idx)
	{
		int smallest = idx;
		int left = 2 * idx + 1;
		int right = 2 * idx + 2;

		if (left < minHeap -> size && minHeap -> array[left] -> freq < minHeap -> array[smallest] -> freq)
			smallest = left;

		if (right < minHeap -> size && minHeap -> array[right] -> freq < minHeap -> array[smallest] -> freq)
			smallest = right;

		if (smallest != idx)
		{
			swapMinHeapNode(&minHeap -> array[smallest], &minHeap -> array[idx]);
			minHeapify(minHeap, smallest);
		}
	}

	// A utility function to check
	// if size of heap is 1 or not
	int isSizeOne(struct MinHeap* minHeap)
	{
		return (minHeap -> size == 1);
	}

	// A standard function to extract
	// minimum value node from heap
	struct MinHeapNode* extractMin(struct MinHeap* minHeap)
	{
		struct MinHeapNode* temp = minHeap -> array[0];
		minHeap -> array[0] = minHeap -> array[minHeap -> size - 1];

		--minHeap -> size;
		minHeapify(minHeap, 0);

		return temp;
	}

	// A utility function to insert
	// a new node to Min Heap
	void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
	{

		++minHeap -> size;
		int i = minHeap -> size - 1;

		while (i && minHeapNode -> freq < minHeap -> array[(i - 1) / 2] -> freq)
		{

			minHeap -> array[i] = minHeap -> array[(i - 1) / 2];
			i = (i - 1) / 2;
		}

		minHeap -> array[i] = minHeapNode;
	}

	// A standard function to build min heap
	void buildMinHeap(struct MinHeap* minHeap)
	{

		int n = minHeap -> size - 1;
		int i;

		for (i = (n - 1) / 2; i >= 0; --i)
			minHeapify(minHeap, i);
	}

	// A utility function to print an array of size n
	void printArr(int arr[], int n)
	{
		int i;
		for (i = 0; i < n; ++i)
			printf("%d", arr[i]);

		printf("\n");
	}

	// Utility function to check if this node is leaf
	int isLeaf(struct MinHeapNode* root)
	{
		return !(root -> left) && !(root -> right);
	}

	// Creates a min heap of capacity
	// equal to size and inserts all character of
	// data[] in min heap. Initially size of
	// min heap is equal to capacity
	struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
	{

		struct MinHeap* minHeap = createMinHeap(size);

		for (int i = 0; i < size; ++i)
			minHeap -> array[i] = newNode(data[i], freq[i]);

		minHeap -> size = size;
		buildMinHeap(minHeap);

		return minHeap;
	}

	// The main function that builds Huffman tree
	struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
	{
		struct MinHeapNode *left, *right, *top;

		// Step 1: Create a min heap of capacity
		// equal to size. Initially, there are
		// modes equal to size.
		struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

		// Iterate while size of heap doesn't become 1
		while (!isSizeOne(minHeap))
		{

			// Step 2: Extract the two minimum
			// freq items from min heap
			left = extractMin(minHeap);
			right = extractMin(minHeap);

			// Step 3: Create a new internal
			// node with frequency equal to the
			// sum of the two nodes frequencies.
			// Make the two extracted node as
			// left and right children of this new node.
			// Add this node to the min heap
			// '$' is a special value for internal nodes, not
			// used
			top = newNode('$', left -> freq + right -> freq);

			top -> left = left;
			top -> right = right;

			insertMinHeap(minHeap, top);
		}

		// Step 4: The remaining node is the
		// root node and the tree is complete.
		return extractMin(minHeap);
	}

	// Prints huffman codes from the root of Huffman Tree.
	// It uses arr[] to store codes
	void printCodes(struct MinHeapNode* root, int arr[], int top, huff_code all_codes[], int size)
	{

		// Assign 0 to left edge and recur
		if (root -> left)
		{

			arr[top] = 0;
			printCodes(root -> left, arr, top + 1, all_codes, size);
		}

		// Assign 1 to right edge and recur
		if (root -> right)
		{

			arr[top] = 1;
			printCodes(root -> right, arr, top + 1, all_codes, size);
		}

		// If this is a leaf node, then
		// it contains one of the input
		// characters, print the character
		// and its code from arr[]
		if (isLeaf(root))
		{
			for(int i = 0; i < size; i++)
				if(all_codes[i].ch == root -> data)
				{
					all_codes[i].code = (char*)malloc(top * sizeof(char));

					for(int j = 0; j < top; j++)
						all_codes[i].code[j] = arr[j] + '0';
				}
		}
	}

	// The main function that builds a
	// Huffman Tree and print codes by traversing
	// the built Huffman Tree
	void HuffmanCodes(char data[], int freq[], int size, huff_code all_codes[])
	{
		// TODO: build data array and freq array for conversion
		// Construct Huffman Tree
		*root = buildHuffmanTree(data, freq, size);

		// Print Huffman codes using
		// the Huffman tree built above
		int arr[100], top = 0;

		printCodes(*root, arr, top, all_codes, size);
	}

	huff_code *all_codes = (huff_code*)malloc(size * sizeof(huff_code));

	char data[size];
	int freq[size];

	for(int i = 0; i < size; i++)
	{
		data[i] = all_char_freq[i].ch;
		freq[i] = all_char_freq[i].freq;
		all_codes[i].ch = all_char_freq[i].ch;
	}

	HuffmanCodes(data, freq, size, all_codes);

	return all_codes;
}

void compressFile(FILE *inFPtr, FILE *outCmpFPtr, FILE* outDatFPtr, huff_code *all_codes, int size)
{
	// Reset the file pointer to the start of the file, to read through it again
	fseek(inFPtr, 0, SEEK_SET);

	int max_code_length = strlen(all_codes[0].code);

	fprintf(outDatFPtr, "%d\n%d", max_code_length, size);

	void resetPrevCode(char prev_code[])
	{
		for(int i = 0; i < max_code_length; i++)
			prev_code[i] = '0';
	}

	char *getCode(char ch)
	{
		for(int i = 0; i < size; i++)
			if(all_codes[i].ch == ch)
				return all_codes[i].code;
	}

	void writeByteToFile(char *code)
	{
		unsigned char ch = 0;

		// printf("Writing '%s'\n", code);

		for(int i = 0; i < 8; i++)
			if(code[i] == '1')
				ch += pow(2, (7 - (i % 8)));

		fwrite(&ch, sizeof(ch), 1, outCmpFPtr);
	}

	int prev_length = 0;
	char prev_code[max_code_length], write_code[8];

	void writeToFile(char *code)
	{
		int code_length = strlen(code);

		// printf("prev_length = %d and code_length = %d\n", prev_length, code_length);

		if(prev_length == 0)
		{
			if(code_length == 8)
				writeByteToFile(code);

			else if(code_length < 8)
			{
				for(int i = 0; i < code_length; i++)
					write_code[i] = code[i];

				prev_length = code_length;
			}
			
			// if code_length > 16 ?
			else if(code_length > 8)
			{
				for(int i = 0; i < ceil(code_length / 8.0); i++)
				{
					// printf("i = %d\n", i);
					if(i != ceil(code_length / 8.0) - 1)
					{
						for(int j = 0; j < 8; j++)
							write_code[j] = code[(i * 8) + j];
						
						writeByteToFile(write_code);
					}

					else
					{
						prev_length = code_length % 8;

						for(int j = 0; j < prev_length; j++)
							write_code[j] = code[(code_length / 8) * 8 + j];
					}
				}
			}
		}

		// prev_length > 0
		else
		{
			if(prev_length + code_length == 8)
			{
				for(int i = prev_length + 1; i < 8; i++)
					write_code[i] = code[i];

				writeByteToFile(write_code);
				
				prev_length = 0;
			}

			else if(prev_length + code_length < 8)
			{
				for(int i = prev_length; i < prev_length + code_length; i++)
					write_code[i] = code[i - prev_length];

				prev_length += code_length;
			}

			else if(prev_length + code_length > 8)
			{
				for(int i = prev_length; i < 8; i++)
					write_code[i] = code[i - prev_length];
				
				writeByteToFile(write_code);

				for(int i = 8; i < prev_length + code_length; i++)
				{
						write_code[i - 8] = code[i - prev_length];
				}

				// Check if we need to iterate or not
				if((prev_length + code_length) / 8.0 > 1)
				{
					for(int i = 1; i < ceil((prev_length + code_length) / 8.0); i++)
					{
						if(i != ceil((prev_length + code_length) / 8.0) - 1)
						{
							for(int j = 0; j < 8; j++)
								write_code[j] = code[(i * 8) + j];
							
							writeByteToFile(write_code);
						}

						else
						{
							prev_length = (prev_length + code_length) % 8;

							for(int i = 0; i < prev_length; i++)
								write_code[i] = code[((prev_length + code_length) / 8) * 8 + i];
						}
					}
				}

				else
					prev_length = (prev_length + code_length) - 8;
			}
		}
	}

	// Iterating through all the characters in the file
	while(!feof(inFPtr))
	{
		char ch;
		fscanf(inFPtr, "%c", &ch);

		char *code = getCode(ch);
		writeToFile(code);
		// printf("'%c': '%s'\n", ch, code);
	}
}

// TODO: Finish decompression algorithm
void decompressFile(FILE *inCmpFPtr, FILE *inDatFPtr, huff_code *all_codes, MinHeapNode *root)
{
	unsigned char ch = 0;

	int max_code_length, size;

	fscanf(inDatFPtr, "%d\n%d", &max_code_length, &size);

	printf("max_code_length = %d\nsize = %d\n", max_code_length, size);

	/*
		Implementing manual string checking instead of using strcmp because
		we only need to check first n chars
	*/
	int isEqual(char code_1[], char code_2[], int length)
	{
		for(int i = 0; i < length; i++)
			if(code_1[i] != code_2[i])
				return 0;
		
		// If both the strings are equal
		return 1;
	}

	int getIndexOfCode(char code[], int length)
	{
		for(int i = 0; i < size; i++)
		{
			if(strlen(all_codes[i].code) != length)
				continue;
			
			else if(isEqual(all_codes[i].code, code, length))
				return i; // This will break the loop as well so dw :)
		}

		// No decoded character found
		return -1;
	}


	int isLeaf(struct MinHeapNode* root)
	{
		return !(root -> left) && !(root -> right);
	}

	char printCodes(struct MinHeapNode* root, char code[], int i, int *end_index)
	{
		if (isLeaf(root))
		{
			*end_index = i;
			return root -> data;
		}

		// Assign 0 to left edge and recur
		if (root -> left && code[i] == '0')
			return printCodes(root -> left, code, i + 1, end_index);

		// Assign 1 to right edge and recur
		if (root -> right && code[i] == '1')
			return printCodes(root -> right, code, i + 1, end_index);
	}

	char cur_code[8], prev_code[8], big_str[16], decode[max_code_length];
	int end_index = 0, prev_length = 0;

	while(!feof(inCmpFPtr))
	{
		fread(&ch, sizeof(ch), 1, inCmpFPtr);

		for(int i = 7; i >= 0; i--)
			cur_code[7 - i] = ((ch >> i) & 1) + '0';

		if(prev_length == 0)
		{
			for(int i = 0; i < 8; i++)
			{
				decode[i] = cur_code[i];
				
				// int index = -1;
				int index = getIndexOfCode(decode, i);

				if(index == -1)
					continue;

				else
				{
					printf("Got index = %d\n", index);
					// printf("Got char: %s\n", all_codes[index].ch);
					prev_length = i;
				}
			}
		}

		else
		{
			// DO more things here :)
		}

		// getCharFromCode(prev_code);
		// inOrder(root);
		// char op_char = printCodes(root, cur_code, 0, &end_index);

		// printf("'%c' : '%d'\n", op_char, end_index);
	}
}