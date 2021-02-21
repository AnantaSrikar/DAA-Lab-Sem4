# Lab_2

Consists of two files:
1. `linear_search.c`: Program that uses linear search techniques to search in a given set of
student records by considering a specified field (Hall Ticket Number, Name, or Team Number).

2. `binary_search.c`: Program that uses binary search techniques to search in a given set of
student records by considering a specified field (Hall Ticket Number, Name, or Team Number).

## Explanation

### 1. `linear_search.c`
#### Input and Execution
After compiling the code with `gcc`, the code accepts command line arguments, as below:

`./a.out <field> <search_data>`

`field` can take three values, which maps as below:
1. Hall-ticket number
2. Name
3. Team number

For example, if you want to search the list using Hall-ticket number, the command would be

`./a.out 1 19XJ1A0507`

The list of students is taken from the file `DAALab_input1.txt` (in the same working directory), as mentioned in the problem statement.

#### Output
The output is generated as the contents of the file `DAALab_output1.txt`, in the same working directory. Will display multiple records if found.

#### Logic
Used singly linked list datastructure for storing the values of the students' list. Used pointers almost everywhere to have the most efficient usage of memory. It will go through all elements, and append the found elements to a new
linked list, and puts the output into the necessary file.

The structure `student` used for generating the list has the following contents:
- `char *ht_no`:Character pointer to store Hallticket number as a string.
- `char *name`: Character pointer to store name as a string.
- `int team_no`: Integer to store the team number.
- `struct student *next`: structure pointer to link the next element.


Created and used multiple functions, below are few of the most important ones. 
- `student *getLinkedList(FILE*)`: returns a doubly	 linked list from a given file pointer.
- `linearSearch(student*, int, void*)`: The main code that implements linear search.
- `void writeToFile(FILE*, student*)`: Writes the linked list to the output file in the format `roll_no name team_no`.


### 2. `binary_search.c`
#### Input and Execution
After compiling the code with `gcc`, the code accepts command line arguments, as below:

`./a.out <field> <search_data>`

`field` can take three values, which maps as below:
1. Hall-ticket number
2. Name
3. Team number

For example, if you want to search the list using Hall-ticket number, the command would be

`./a.out 1 19XJ1A0507`

The list of students is taken from the file `DAALab_input1.txt` (in the same working directory), as mentioned in the problem statement.

#### Output
The output is generated as the contents of the file `DAALab_output1.txt`, in the same working directory. Will display multiple records if found.

#### Logic
Used doubly linked list datastructure for storing the values of the students' list. Used pointers almost everywhere to have the most efficient usage of memory. Sorts the data (using Quick sort for fastest implementation) according to the field that has to be searched. Then uses the binary search algorithm to find atmost 3 nodes.

The structure `student` used for generating the list has the following contents:
- `char *ht_no`:Character pointer to store Hallticket number as a string.
- `char *name`: Character pointer to store name as a string.
- `int team_no`: Integer to store the team number.
- `struct student *next`: structure pointer to link the next element.
- `struct student *prev`: structure pointer to link the previous element.


Created and used multiple functions, below are few of the most important ones. 
- `student *getLinkedList(FILE*)`: returns a doubly	 linked list from a given file pointer.
- `student *split(student*)`: Returns the mid element of the doubly linked list. Used in `mergeSort()`
- `student *mergeRoutine(student*, student*, int)`: Merge routine used in the `mergeSort()` and itself.
- `void quickSort(student*, int)`: Sorts the linked list with the given field (1, 2 and 3) as mentioned above using `Quick sort` algorithm.
- `void recQuickSort(student*, student*, int)`: The recursive implementation of the Quick Sort algoritm. Used in `quickSort()`.
- `binarySearch(student*, int, void*)`: The main code that implements binary search.
- `void writeToFile(FILE*, student*)`: Writes the linked list to the output file in the format `roll_no name team_no`.