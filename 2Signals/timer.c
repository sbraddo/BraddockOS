/* timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

/*

COPY YOUR SIGNAL.C INTO THIS FILE

UPDATE YOUR MAKEFILE

****/ 

/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

bool sig = true;
int totalAlarms = 0;
// double totalTime;
// clock_t start, end;

void handler(int signum)
{ //signal handler
  if (signum == SIGINT){
    // end = clock();
    // totalTime = ((double)end - start)/CLOCKS_PER_SEC;
    printf("Total Alarms: %d \n", totalAlarms);
    // printf("Total Time in Seconds: %f \n", totalTime);
    exit(0);
  }
  else
    printf("Hello World!\n");
    alarm(1);
    totalAlarms++;
  //exit(1); //exit after printing
  //wait(0);
}

int main(int argc, char * argv[])
{
  // start = clock();
  signal(SIGINT,handler);
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second
  totalAlarms++;
  while(sig){
    sleep(1);
    //totalAlarms++;
    printf("Turning was right!\n");
  } //busy wait for signal to be delivered
  return 0; //never reached
}
