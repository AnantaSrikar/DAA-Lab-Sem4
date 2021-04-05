/*
	Author: Ananta Srikar

	Program to find the maximum number of meetings that can be accommodated in the meeting
	room when only one meeting can be held in the meeting room at a particular time.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct meeting {
	int start;
	int end;
	int pos;
};

typedef struct meeting meeting;

int main(int argc, char **argv)
{
	// Initial code to get all command line values
	
	if(argc < 2)
	{
		printf("Incorrect number of arguments! Please go through README.md\n");
		return -1;
	}

	int input_arr[argc - 1];

	for(int i = 1; i < argc; i++)
	{
		for(int j = 0; j < strlen(argv[i]); j++)
			if(!isdigit(argv[i][j]) && argv[i][j] != '-')
			{
				printf("Please enter only numbers!\n");
				return -1;
			}

		input_arr[i - 1] = atoi(argv[i]);
	}

	int size = input_arr[0];

	if(size * 2 != argc - 2)
	{
		printf("Enter valid number of arguments!");
		return -1;
	}

	int start_time[size], end_time[size];

	for(int i = 1; i < size + 1; i++)
		start_time[i - 1] = input_arr[i];

	for(int i = size + 1; i < size * 2 + 1; i++)
		end_time[i - size - 1] = input_arr[i];

	// End of command line arguments

	// Function prototypes
	void getMaxMeetings(int[], int[], int);

	getMaxMeetings(start_time, end_time, size);

	return(0);
}

// Function to copy the values of one meeting into another
void copyMeeting(meeting *m1, meeting *m2)
{
	m1 -> start = m2 -> start;
	m1 -> end = m2 -> end;
	m1 -> pos = m2 -> pos;
}

// Using merge sort for guaranteed time complexity O(Nlog(N))
// Merge routine
void merge(meeting all_meetings[], int p, int q, int r)
{

	// Create L ← A[p..q] and M ← A[q+1..r]
	int n1 = q - p + 1;
	int n2 = r - q;

	meeting L[n1], M[n2];

	for (int i = 0; i < n1; i++)
		copyMeeting(&L[i], &all_meetings[p + i]);
	for (int j = 0; j < n2; j++)
		copyMeeting(&M[j], &all_meetings[q + 1 + j]);

	// Maintain current index of sub-arrays and main array
	int i, j, k;
	i = 0;
	j = 0;
	k = p;

	// Until we reach either end of either L or M, pick larger among
	// elements L and M and place them in the correct position at A[p..r]
	while (i < n1 && j < n2)
	{
		if (L[i].end <= M[j].end)
		{
			copyMeeting(&all_meetings[k], &L[i]);
			i++;
		}
		
		else
		{
			copyMeeting(&all_meetings[k], &M[j]);
			j++;
		}
		k++;
	}

	// When we run out of elements in either L or M,
	// pick up the remaining elements and put in A[p..r]
	while (i < n1)
	{
		copyMeeting(&all_meetings[k], &L[i]);
		i++;
		k++;
	}

	while (j < n2)
	{
		copyMeeting(&all_meetings[k], &M[j]);
		j++;
		k++;
	}
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(meeting all_meetings[], int l, int r)
{
	if (l < r)
	{
		// m is the point where the array is divided into two subarrays
		int m = l + (r - l) / 2;

		mergeSort(all_meetings, l, m);
		mergeSort(all_meetings, m + 1, r);

		// Merge the sorted subarrays
		merge(all_meetings, l, m, r);
	}
}

// Function to check if a meeting is in the list of confirmed meetings
int in(int index, int indices[], int size)
{
	for(int i = 0; i < size; i++)
		if(indices[i] == 1 && i == index)
			return 1;

	return 0;
}

// Function to print the max number of meetings (and the meetings) that should be held
void getMaxMeetings(int start_time[], int end_time[], int size)
{
	int confirmed_meeting_index[size], cnt = 1;
	meeting all_meetings[size];

	for (int i = 0; i < size; i++)
	{
		// Starting time of meeting i.
		all_meetings[i].start = start_time[i];
		 
		// Finishing time of meeting i
		all_meetings[i].end = end_time[i];
		 
		// Original position/index of meeting
		all_meetings[i].pos = i;

		// Assigning all values to -1
		confirmed_meeting_index[i] = -1;
	}

	// Sorting all meetings
	mergeSort(all_meetings, 0, size - 1);

	// The first meeting should happen for sure
	confirmed_meeting_index[all_meetings[0].pos] = 1;

	int time_limit = all_meetings[0].end;

	// Check for all meeting whether it
	// can be selected or not.
	for (int i = 0; i < size; i++)
	{
		if (all_meetings[i].start >= time_limit)
		{
			// select this meeting
			confirmed_meeting_index[all_meetings[i].pos] = 1;
			
			// Update time limit.
			time_limit = all_meetings[i].end;

			// Increase the count of the number of meeting that can take place
			cnt++;
		}
	}

	printf("%d\n", cnt);

	// Printing the meetings that should be held
	// printf("Meetings that should be held:\n");

	// for(int i = 0; i < size; i++)
	// 	if(in(all_meetings[i].pos, confirmed_meeting_index, size))
	// 		printf("[%d, %d] ", all_meetings[i].start, all_meetings[i].end);

	printf("\n");
}