[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/x_2bVRnH)
# Assignment 4


As usual, submit your code to GitHub Classroom, and the pdf on Gradescope.

Like last time, to compile code in this assignment properly, run `make` from the assignment's directory. This will output an executable `asmnt4` that requires two integer input parameter. For example, to execute this assignment you could run `./asmnt4 5 10`. 

`5` acts as a seed for the [Mersenne Twister](https://en.wikipedia.org/wiki/Mersenne_Twister) algorithm. The same seed will always generate the same set of random numbers in the same order. This allow us to test your code with our own set of random numbers. You can test your code using different seeds, they will generate different sets of random `int`s. Use the same 15 random numbers in the order in which they are stored in the array to add to your data structures. 
'10' is the number of random values to generate. For 1(a) you can test with '20'. For 1(b) you can try '15'.

**Most of the code you need to edit is in [q1a.c](q1a.c) and [q1b.c](q1b.c). You will also need to add function calls for 1(c) in [main.c](main.c) and specify your struct in [q1.h](q1.h). Make sure that you choose your specification such that it works for both structures (levels=2 and levels=m).**

## Question 1

### a)

- Create a linked list with two levels, one where the pointers work like an ordinary linked list, connecting each node to the next; and one where the pointers connect only the Fibonacci stations.
- Write your functions in [q1a.c](q1a.c).
- Print the list using `print_list()`. The function has been included for you.

### b)

- Rework your linked list to work with m levels. Note that since there is only one header file, your `node` struct must remain the same, the only change should be in your pointers.
- Write your functions in [q1b.c](q1b.c).
- Print the list using `print_list()`. The function has been included for you.

### c)

- Fill in `_1b_delete_node()` in [q1b.c](q1b.c).
- Call the delete functions from [main.c](main.c) and reconstruct the list using the functions from [q1b.c](q1b.c).


## Question 2

### a)

- Create a tree structure the way you did for BST, adding the height and balance functions required for AVL. Look at the header file for what you should fill in.

### b)

- Fill in the function calls for Cth smallest and deletion in [main.c](main.c). Print the tree after every step using the inorder function.

Tip: Check for memory leaks using `valgrind` for most machines and `leaks` for Apple Silicon Macs. Memory leaks = *bad*

**All the best!**