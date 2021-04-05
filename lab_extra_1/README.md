# Lab_4

Consists of 3 files:
1. `meetings.c`: Program to find the maximum number of meetings that can be accommodated in the meeting room when only one meeting can be held in the meeting room at a particular time.

2. `password_finder.c`: Program to find the largest number of N digits that can be made with a given sum of digits S.

3. `stairs.c`: Program to find the numeber of ways a person can climb N stairs, when 1 or 2 stairs are climbed at a time.


## Explanation

### 1. `meetings.c`
#### Input and Execution
After compiling the code with `gcc`, execute as below:

`./a.out <number of meetings> <start times> <end times>`

Eg: `./a.out 8 75250 50074 43659 8931 11273 27545 50879 77924 112960 114515 81825 93424 54316 35533 73383 160252`

#### Output
The output is displayed on the shell window, right after execution.

#### Logic
The list of meetings is first sorted in the increasing order of their end time. Used Merge Sort technique, as it has a sure shot time complexity of Nlog(N), which was needed in the question, and is the most time time consuming part of the program. The first meeting is selected for sure, and the rest of the meetings are selected if the start time of the next meeting is greater than the end time of the previous meeting.

The structure `meeting` used for generating the list has the following contents:
- `int start`: Integer variable to store the starting time of a meeting.
- `int end`: Integer variable to store the ending time of a meeting.
- `int pos`: Integer variable to store the actual position of the meeting between all the meetings.


Created and used multiple functions, below are few of the most important ones. 
- `void merge(meeting all_meetings[], int p, int q, int r)`: Merge routine for the merge sort. Used in `mergeSort()`.
- `void mergeSort(meeting all_meetings[], int l, int r)`: Recursive implementation of merge sort on the array of meetings.
- `void getMaxMeetings(int start_time[], int end_time[], int size)`: Main driver code for the above logic.


### 2. `password_finder.c`
#### Input and Execution
After compiling the code with `gcc`, the code accepts command line arguments, as below:

`./a.out <N> <S>`

Eg: `./a.out 5 12`

#### Output
The output is displayed on the shell window, right after execution.

#### Logic
Just keep subtracting 9 from sum, if the sum of digits is bigger than 9, else print the remaining value, and the rest of the digits would be 0.

Created and used a function (since the logic was simple 😉): `void find_password(int N, int S)`: Executes the above logic, with a time complexity of O(N).



### 3. `stairs.c`
#### Input and Execution
For compiling, run the command

`gcc stairs.c`

After compiling , the executable accepts command line arguments, as below:

`./a.out <number of stairs>`

Eg: `./a.out 10`

#### Output
The output is displayed on the shell window, right after execution.

#### Logic
Upon observation, the number of ways one can climb N stairs was found out the be a slightly modified version of the fibonacci series. Hence the same was implemented.


Created and used one funtion: `int getWaysToClimb(int N)`: returns the (N+1)<sup>th</sup> number of the fibonacci series.