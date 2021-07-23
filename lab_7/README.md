# Lab_7

Consists of 2 files
1. `huffman.c`: Program to compress or decompress a given text file using huffman encoding.

2. `sssp.c`: Program to find the shortest path between any two given nodes in a graph.


## Compiling and execution
### 1. `huffman.c`
Run `gcc huffman.c -lm` to compile. To execute run:

`./a.out <file_action> <filename>`

`file_action` should be either `c` (compress) or `d` (de-compress)

`filename` should be the name of the text file you wish to compress or decompress.

For example, if you want to compress `scouter.txt`, the command would be as follows:

`./a.out c scouter.txt`

#### Output
The compressed file would be `<filename>.cmp` along with `<filename.dat>`, filename is the name of input file, without `.txt`.

The decompressed file would be `<filename>-dat.txt`.

### 2. `sssp.c`
Compile normally with `gcc`, and execute with `./a.out`.

You will then be asked to enter the graph, and the nodes between which you want to find the shortest path

Output will be the shortest path that can be taken between the given nodes, if it exists.