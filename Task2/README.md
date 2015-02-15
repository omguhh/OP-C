# OP & C
Lab 2 for Operating Systems &amp; Concurrency 

#TODO:


##Problem 2

2.1 Familiarise yourself with the execve-family of system calls. Write a C program that
takes its arguments and passes them on to the shell operation ps.

2.2 Can you modify the solution of 2.1 so that the C program prints to the terminal how
many processes would be printed if ps would be called with the given arguments? A
call <your executable> -a should have the same eect as ps -a | wc.

##Problem 3

Consider a variant of the puzzle presented in the lecture: assume that you have 3
threads, each of which runs the following code:
```
for( int i=0; i<3; i++) {
x = x+1;
}
``` 
x is assumed to be a globally shared variable which initially has the value 0 whereas i
is thread-local.

1. Describe a schedule which results in the final value of x being minimal.

2. Describe a schedule which results in the final value of x being maximal.

>In a schedule where each thread has to wait for the previous to finish writing, the maximal value is 9. (It's _sequential_) 

> | Thread 1    | Thread 2    | Thread 3    |
> |-------------|-------------|-------------|
> | Read x = 0  | Wait        | Wait        |
> | Process     | Wait        | Wait        |
> | Write x = 3 | Wait        | Wait        |
> |             | Read x = 3  | Wait        |
> |             | Process     | Wait        |
> |             | Write x = 6 | Wait        |
> |             |             | Read x = 6  |
> |             |             | Process     | 
> |             |             | Write x = 9 |

##Steps for running it:

1. Type in gcc -c bintree.c
 
2. Type in gcc -c treetest.c 

3. Type in gcc bintree.o treetest.o -o prog

4. Run it by typing ./prog
