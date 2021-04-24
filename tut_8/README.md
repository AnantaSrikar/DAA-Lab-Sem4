# Tut_8

Consists of three files:
1. `dice_sum.c`: Given n dice each with m faces, numbered from 1 to m, this program finds the number of ways to get sum X (Where X is the summation of values on each face when all the dice are thrown).

2. `coin_change.c`: Given a value N, if we want to make change for N rupees, and we have infinite supply of each of Coins(i.e., { C1 , C2 , .. , Cm }), the program finds many ways can we make the change.

3. `box_stacking.c`: Program to solve the box stacking problem.

## Explanation

### 1. `dice_sum.c`
#### Input and Execution
After compiling the code with `gcc`, the code accepts command line arguments, as below:

`./a.out <n> <m> <x>`


### 2. `coin_change.c`
#### Input and Execution
After compiling the code with `gcc`, the code accepts command line arguments, as below:

`./a.out <sum_N> <individual_coins>`

Eg: `./a.out 4 1 2 3`. Here, we want a change of 4 with the coins 1, 2 and 3.


### 3. `box_stacking.c`
### Input and Execution
After compiling the code with `gcc`, the code accepts command line arguments, as below:

`./a.out <num_of_boxes> <box1_h> <box1_w> <box1_d> <box2_h> .... <boxn_d>`

Eg: `./a.out 4 4 6 7 1 2 3 4 5 6 10 12 32`