#include <stdio.h>      /* puts, printf */
#include <time.h>       /* time_t, struct tm, time, localtime */

int main ()
{
  time_t rawtime;
  struct tm * timeinfo;
  FILE * fp;
  FILE * fr;
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
 sleep(5);
}

  return 0;
}
