#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

// could just be returning a value
void * dummy (void * arg) { return arg;  }


double xelapsed (struct timespec a, struct timespec b) {
return (a.tv_sec - b.tv_sec) * 1000000.0 + (a.tv_nsec - b.tv_nsec) / 1000.0;
	
	}	

	// whatever you pass will be a positive value

void measure_fork (unsigned N)
{
	// get initial starting time, time it takes to make the forks and time 
	// it takes to make the forks and then the time it takes for them to run the
	// dummy function and terminate

struct timespec start, stop, finish;
clock_gettime (CLOCK_REALTIME, &start);


pid_t process_ids[N];

/*
* Make N forks, call dummy in every child.
*/
int i;

for(i=0;i<N;i++){

	process_ids[i] = fork();

	if(process_ids[i]<0)	{
	printf("fork failed\n");
	exit(0);
		}	
	//child process
	else if (process_ids[i]==0)	{ 
		dummy(0);
		exit(0);	
	}

}

clock_gettime (CLOCK_REALTIME, &stop);

/*
 *TODO: Wait for the forks.	
 *The wait system-call puts the process to sleep and waits for a child-process to end. 
*/
int j;

for(j= 0;j< N;j++)   {         wait(&process_ids[j]);        }

clock_gettime (CLOCK_REALTIME, &finish);


printf ("%d proc: fork=%5.0f (mics) wait=%5.0f (mics) sum=%5.0f (mics)\n",
N, xelapsed (stop, start),
xelapsed (finish, stop), xelapsed (finish, start));
printf ("per proc: fork=%5.0f (mics) wait=%5.0f (mics) sum=%5.0f (mics)\n",
xelapsed (stop, start)/N,
xelapsed (finish, stop)/N, xelapsed (finish, start)/N);

}


int main(int argc, char*argv[]) {

int n;

n = atoi(argv[1]);
measure_fork(n);

return 0;

}
