#include <stdio.h> /* puts, printf */
#include <time.h> /* time_t, struct tm, time, localtime */
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/*before this was extended into task 1.2 everything was in the main..split
them into methods cus it looked/worked cleaner */ 

time_t rawtime;
struct tm * timeinfo;
FILE * fp;
FILE * fr;

#define DAEMON_NAME "vdaemon"

void logTime() {
/*based on task 1.1..*/
while ( 1 ) {
time (&rawtime);
timeinfo = localtime (&rawtime);
fr=fopen("/tmp/test.txt","a");
if(fr==NULL) {
fp=fopen("/tmp/test.txt","w+");
fprintf(fp,"Current local time and date: %s", asctime(timeinfo));
fclose(fp);
			}
else {
fprintf(fr,"Current local time and date: %s", asctime(timeinfo));
fclose(fr);
		}
sleep(5);     //Sleep for 5 seconds

	}
}


int main () {
    /*----------------*/
    /*--Daemon stuff--*/
    /*----------------*/

     pid_t process_id, sid;
     process_id=fork();

 // FORK FAILED.
	if (process_id < 0) { 
		printf("fork failed!\n");
	// Return failure in exit status
	exit(EXIT_FAILURE);
	}

// KILLING PARENT PROCESS.
	if (process_id > 0) {
	printf("process_id of child process %d \n", process_id);
	// return success in exit status
	exit(EXIT_SUCCESS);
 }

//set new session
sid = setsid();
if(sid < 0) { exit(EXIT_FAILURE); }

    chdir("/tmp");

    /*--Main Program--*/
    while(1){ logTime(); }//Run our Process
            
}
