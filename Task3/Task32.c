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


pthread_t threadid[N];


/*
* Make N forks, call dummy in every child.
*/

for(int i=0;i<N;i++){

	ret = pthread_create (&threadid[i], NULL, dummy, NULL);

	if(ret<0)	{
	printf("fork failed\n");
	exit(EXIT_FAILURE);

		}	

	//child process
	else if (ret==0)	{ 
		dummy(0);
		exit(EXIT_SUCESS);	
	}	

}

clock_gettime (CLOCK_REALTIME, &stop);

/*
 *TODO: Wait for the forks.	
 *The wait system-call puts the process to sleep and waits for a child-process to end. 
*/
for(int j= 0;j< N;j++)     {
	void *result;
	pthread_join (pid, &result);
}

clock_gettime (CLOCK_REALTIME, &finish);


printf ("%d proc: fork=%d (mics) wait=%d (mics) sum=%d (mics)\n",
N, xelapsed (stop, start),
xelapsed (finish, stop), xelapsed (finish, start);
printf ("per proc: fork=%d (mics) wait=%d (mics) sum=%d (mics)\n",
xelapsed (stop, start)/N,
xelapsed (finish, stop)/N, xelapsed (finish, start)/N;

}


int main(int argc, char*argv) {

int n;

n = atoi(argv[1]);
measure_fork(n);

return 0;

}
