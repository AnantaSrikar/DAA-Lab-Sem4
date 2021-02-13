# Lab_2

Consists of two files:
1. `opt_sort.c`: Program that uses Merge Sort and Quick Sort techniques to sort a set of
student records by considering a specified field (Hall Ticket
Number, Name, or Team Number).

2. `ord_sort.c`: Program that uses Merge Sort and Quick Sort techniques to sort a set of
student records by considering all the fields in a specific order(Team Number, Hall Ticket Number, and Name).

## Explanation

### 1. `opt_sort.c`
#### Input and Execution
After compiling the code with `gcc`, the code accepts command line arguments, as below:

`./a.out <sorting_method> <field>`

`sorting_method` can take either `1` or `2`, which maps as below:
1. Merge sort
2. Quick sort

`field` can take three values, which maps as below:
1. Hall-ticket number
2. Name
3. Team number

For example, if you want to sort according to the names using Merge sort, the command would be

`./a.out 1 2`

The input is taken from the file `DAALab_input1.txt` (in the same working directory), as mentioned in the problem statement.

#### Output
The output (sorted student list) is generated as the contents of the file `DAALab_output1.txt`, in the same working directory.

#### Logic
Used doubly linked list datastructure for storing the values of the students' list. Used pointers almost everywhere to have the most efficient usage of memory.

The structure `student` used for generating the list has the following contents:
- `char *ht_no`:Character pointer to store Hallticket number as a string.
- `char *name`: Character pointer to store name as a string.
- `int team_no`: Integer to store the team number.
- `struct student *next`: structure pointer to link the next element.
- `struct student *prev`: structure pointer to link the previous element.


Created and used multiple functions, below are few of the most important ones. 
- `student *getLinkedList(FILE*)`: returns a doubly linked list from a given file pointer.
- `student *mergeSort(student*, int)`: Sorts the linked list with the given field (1, 2 and 3) as mentioned above using `Merge sort` algorithm.
- `student *split(student*)`: Returns the mid element of the doubly linked list. Used in `mergeSort()`
- `student *mergeRoutine(student*, student*, int)`: Merge routine used in the `mergeSort()` and itself.
- `void quickSort(student*, int)`: Sorts the linked list with the given field (1, 2 and 3) as mentioned above using `Quick sort` algorithm.
- `void recQuickSort(student*, student*, int)`: The recursive implementation of the Quick Sort algoritm. Used in `quickSort()`.
- `student* partition(student*, student*, int)`: partitions the doubly linked list around the pivot element, which is the last element in our case. Used in `recQuickSort()`.
- `void writeToFile(FILE*, student*)`: Writes the linked list to the output file in the format `roll_no name team_no`.


### 2. `ord_sort.c`
#### Input and Execution
After compiling the code with `gcc`, the code accepts command line arguments, as below:

`./a.out <sorting_method>`

`sorting_method` can take either `1` or `2`, which maps as below:
1. Merge sort
2. Quick sort

The input is taken from the file `DAALab_input1.txt` (in the same working directory), as mentioned in the problem statement.

#### Output
The output (sorted student list) is generated as the contents of the file `DAALab_output1.txt`, in the same working directory.

#### Logic
Reused majority of the code and logic from `opt_sort.c`, therefore, most of the explanation is the same. However, there are significant changes made to solve the problem:
- For `Merge Sort:`The `mergeRoutine()` first checks if the regular sorting algorithm is fine as per the field 'team number'. If the team numbers are the same, it then checks for the difference in the field 'hall ticket number'. If the previous two fields are the same, it then checks the 'name' field and swaps the nodes accordingly.
- For `Quick Sort`: Similar changes were made in `partition()` to account for the sorting to be done, considering the order of the field as mentioned initially.

Then finally, the sorted linked list is written into the output file `DAALab output1.txt`, as mentioned in the problem statement.