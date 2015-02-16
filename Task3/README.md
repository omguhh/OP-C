# OP & C
Lab 3 for Operating Systems &amp; Concurrency 

#TODO:

##Problem 1

1.1 Measure the time it takes to create a process in UNIX. Write a C program, that
executes N forks, stores all child ids in an array and after that waits on all processes to
terminate. Make each child process call the dummy function. Please be careful when
measuring time. One of the ways to measure time accurately is by using the rt library.
Consider the following template for your program:

```
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
void * dummy (void * arg)
{
return arg;
}
double xelapsed (struct timespec a, struct timespec b)
{
return (a.tv_sec - b.tv_sec) * 1000000.0
+ (a.tv_nsec - b.tv_nsec) / 1000.0;
}
void measure_fork (unsigned N)
{
struct timespec start, stop, finish;
clock_gettime (CLOCK_REALTIME, &start);
/*
* Make N forks, call dummy in every child.
*/
clock_gettime (CLOCK_REALTIME, &stop);
/*
* Wait for the forks.
*/
clock_gettime (CLOCK_REALTIME, &finish);
printf ("%d proc: fork=%d (mics) wait=%d (mics) sum=%d (mics)\n",
N, xelapsed (stop, start),
xelapsed (finish, stop), xelapsed (finish, start);
printf ("per proc: fork=%d (mics) wait=%d (mics) sum=%d (mics)\n",
xelapsed (stop, start)/N,
xelapsed (finish, stop)/N, xelapsed (finish, start)/N;
}

```
Execute for various N-s: 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 10000. You can find
the above code as well as a makefile in the assignment section of vision. Make sure,
you check the success of fork and wait.
Display your findings in a graph and explain them; in particular the evolution of
time per process as N gets bigger. Less than 200 words should suffice!

1.2 Repeat the experiment from Problem 1.1, but for threads instead of processes. In
order to create a thread, use pthread create:
```
...
pthread_t pid;
int ret = pthread_create (&pid, NULL, dummy, NULL);
...

```
where dummy is a function from the previous problem. A thread-id will be stored in
pid. pthread create returns 0 in case of a successful thread creation.
In order to wait for the thread termination use pthread join:
```
...
void *result;
pthread_join (pid, &result);
...
```
where pid is the id of the thread we are waiting for. When compiling a program, don’t
forget to add -pthread compilation option. Compare the runtimes you measure with
those from Problem 2.1. Create a little graph and describe your findings. How many
threads can you create before the creation fails?

##Problem 2

Consider a simple producer / consumer scenario. We have two producers and two consumers. The two producers independently produce positive numbers from 1 to a pre-specified number N and negative numbers -1 to -N, respectively. These numbers go into a single queue.

We have 2 consumers that independently consume the numbers from the queue
and print to the screen their id (0 or 1) as well as the number they have consumed. Independently
here means that the distribution of produced items to consumers depends
on the scheduling of threads or processes and, therefore, is non-deterministic.

*Implement this by creating 4 processes or threads, one for each producer and one for each consumer.
*Explain your choice between processes and threads!

Hint: In case you choose processes, you may want to look at shm open.

##Steps for running it:

1. Type in gcc -c bintree.c
 
2. Type in gcc -c treetest.c 

3. Type in gcc bintree.o treetest.o -o prog

4. Run it by typing ./prog
