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
	void getHuffmanTree(file_char *, int);

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

	getHuffmanTree(all_char_freqs, char_num);

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


void getHuffmanTree(file_char *all_char_freq, int size)
{
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
	void printCodes(struct MinHeapNode* root, int arr[], int top)
	{

		// Assign 0 to left edge and recur
		if (root -> left)
		{

			arr[top] = 0;
			printCodes(root -> left, arr, top + 1);
		}

		// Assign 1 to right edge and recur
		if (root -> right)
		{

			arr[top] = 1;
			printCodes(root -> right, arr, top + 1);
		}

		// If this is a leaf node, then
		// it contains one of the input
		// characters, print the character
		// and its code from arr[]
		if (isLeaf(root))
		{

			printf("'%c': ", root -> data);
			printArr(arr, top);
		}
	}

	// The main function that builds a
	// Huffman Tree and print codes by traversing
	// the built Huffman Tree
	void HuffmanCodes(char data[], int freq[], int size)
	{

		// TODO: build data array and freq array for conversion
		// Construct Huffman Tree
		struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

		// Print Huffman codes using
		// the Huffman tree built above
		int arr[100], top = 0;

		printCodes(root, arr, top);
	}

	char data[size];
	int freq[size];

	for(int i = 0; i < size; i++)
	{
		data[i] = all_char_freq[i].ch;
		freq[i] = all_char_freq[i].freq;
	}

	HuffmanCodes(data, freq, size);
}