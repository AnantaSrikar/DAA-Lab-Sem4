# Lab_0

Consists of two files:
1. `simple_file_io.c` - Program to read input from a file and write output into another file.

2. `file_stats.c` - Program to find the number of lines, words and characters in a file.

## Explanation

### 1. `simple_file_io.c`
#### Assumptions
- Input and output files to be `input.txt` and `output.txt` respectively.
- Input file to be in the same directory as the executable.

#### Logic
To be minimalistic, a single while loop is made to iterate through the input file character by character with the help of the `getc()` method. The character is then immediately written to the output file using the `putc()` method.

#### Execution
Standard `gcc` styled execution will work. No command-line arguments are needed.


### 2. `file_stats.c`
#### Assumptions
- Same as that of `simple_file_io.c`
- Lines are marked by a new line, unlike a statement.
- Spaces are not considered as english characters.

#### Logic
The code first finds the number of characters is there in the input file. It then creates an array of characters to find the number of lines, words and characters. This is done as below:

Used three different logic for solving different parts of the problem:
- To identify a new line, simply check for the `'\n'` character.
- For words, if the current array character is an alphabet, it then checks for the next character for the end of a word. All the cases where a word ends were considered, including the end of the file.
- For characters, it was simple. If the current array character wasn't `'\n'` or `' '`, it was considered a character.

#### Execution
Standard `gcc` styled execution will work. No command-line arguments are needed.