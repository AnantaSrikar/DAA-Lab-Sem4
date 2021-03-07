# Lab_4

Consists of 4 files and 1 directory:
1. `tree_sort.c`: Program that uses Tree Sort technique to sort a set of student records by considering Hall Ticket Number.

2. `matrix_multi.c`: Program to multiply two square-matrices of order 1024 X 1024 using Block Matrix Multiplications by considering the block sizes: 4, 8, 16, 32, and 64.

3. `multi-threadded_matrix_multi.c`: Program to multiply two square-matrices of order 1024 X 1024 using Block Matrix Multiplications by considering the block sizes: 4, 8, 16, 32, and 64 using multiple threads.

4. `plot.py`: Function to plot the time taken to execute matrix multiplication.

5. `plots/`: Directory with all the graphs with timings.

## Explanation

### 1. `tree_sort.c`
#### Input and Execution
After compiling the code with `gcc`, execute as below:

`./a.out`

The list of students is taken from the file `DAALab_input1.txt` (in the same working directory), as mentioned in the problem statement.

#### Output
The output is generated as the contents of the file `DAALab_output1.txt`, in the same working directory.

#### Logic
Used the tree sort algorithm to sort all the list of sutdents, according to the hall ticket number.

The structure `student` used for generating the list has the following contents:
- `char *ht_no`:Character pointer to store Hallticket number as a string.
- `char *name`: Character pointer to store name as a string.
- `int team_no`: Integer to store the team number.
- `struct student *left`: structure pointer to link the left sub-tree.
- `struct student *right`: structure pointer to link the right sub-tree.


Created and used multiple functions, below are few of the most important ones. 
- `student *treeSort(FILE*);`: returns a binary search tree from a given file pointer.
- `void insertInTree(student**, student*)`: function to insert a new node into an existing tree. Used in `treeSort()`.
- `void inOrderFileWrite(FILE*, student*)`: Writes a binary search tree in the In-Order traversal to the output file in the format `roll_no name team_no`.


### 2. `matrix_multi.c`
#### Input and Execution
After compiling the code with `gcc`, the code accepts command line arguments, as below:

`./a.out <block_size>`

`block_size` can be either 4, 8, 16, 32 or 64, as mentioned in the question

For example, if you want to try to run the block matrix multiplication with block size 16, the command would be

`./a.out 16`

The two matrices of dimensions 1024x1024 contains random numbers from `-9` to `9`.

#### Output
The exection time (in seconds) is displayed on the terminal, whereas the three matrices are stored ass the contents of the file `DAALab_output1.txt`, in the same working directory.

#### Logic
Used the block matrix multiplication algorithm for multiplying two matrices.

Created and used multiple functions, below are few of the most important ones. 
- `void transpose_matrix(int**, int)`: Converts the input matrix into ints transpose.
- `int **get_rand_array(int)`: Returns a matrix of random numbers with dimensions `size x size` .
- `int **get_zero_array(int)`: Returns a zero matrix with dimensions `size x size`. Can be used to fill later.
- `void sub_matrix_multi(int**, int**, int**, int, int, int, int)`: Function that does the actual matrix multi in the smaller block matrix. Used in `block_matrix_multi()`.
- `int **block_matrix_multi(int**, int**, int, int)`: The actual Block matrix multiplication algorithm. Return a matrice with the multiplies matrix.
- `void writeToFile(FILE*, int**, int**, int**, int)`: Function to write the matrices into the output file.

#### Observation
The time for exectuion is around 4.2s for the block size 4, and reduces by about 0.2s every time the block size is doubled. More about it in the `SingleThread-laptop.jpg`.

Also ran the same algorithm on Raspberry Pi, with the time of execution being around 20s. Similar improvements could be noted with the increase in block size. More about it in the `SingleThread-raspi.jpg`.



### 3. `multi-threadded_matrix_multi.c`
#### Input and Execution
For compiling, run the command

`gcc multi-threadded_matrix_multi.c -fopenmp`

After compiling , the executable accepts command line arguments, as below:

`./a.out <block_size>`

`block_size` can be either 4, 8, 16, 32 or 64, as mentioned in the question

For example, if you want to try to run the block matrix multiplication with block size 16, the command would be

`./a.out 16`

The two matrices of dimensions 1024x1024 contains random numbers from `-9` to `9`.

#### Output
The exection time (in seconds) is displayed on the terminal, whereas the three matrices are stored ass the contents of the file `DAALab_output1.txt`, in the same working directory.

#### Logic
Used the block matrix multiplication algorithm for multiplying two matrices. Also used `openMP` for implementing multi-threadding.

Created and used multiple functions, below are few of the most important ones. 
- `void transpose_matrix(int**, int)`: Converts the input matrix into ints transpose.
- `int **get_rand_array(int)`: Returns a matrix of random numbers with dimensions `size x size` .
- `int **get_zero_array(int)`: Returns a zero matrix with dimensions `size x size`. Can be used to fill later.
- `void sub_matrix_multi(int**, int**, int**, int, int, int, int)`: Function that does the actual matrix multi in the smaller block matrix. Used in `block_matrix_multi()`. Uses multi-threadding approach for faster exectuion.
- `int **block_matrix_multi(int**, int**, int, int)`: The actual Block matrix multiplication algorithm. Return a matrice with the multiplies matrix. Uses multi-threadding approach for faster exectuion.
- `void writeToFile(FILE*, int**, int**, int**, int)`: Function to write the matrices into the output file.

#### Observation
The time for exectuion is around 3s for the block size 4, and reduces exponentially every time the block size is doubled. More about it in the `MultiThread-laptop.jpg`. Also note that we get sub one second completion for block sizes greater than or equal to `16`. This approach helps utilize all the resouces of the CPU and also execute much faster than its single thread implementation.

Also ran the same algorithm on Raspberry Pi, with the time of execution being around 13s. The time of execution reduces exponentially with the increase in block size. More about it in the `MultiThread-raspi.jpg`.This approach helps utilize all the resouces of the CPU and also execute much faster than its single thread implementation.

