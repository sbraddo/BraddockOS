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
#include <time.h>

bool sig = false;
int totalAlarms = 0;
double totalTime;
clock_t start, end;

void sigAlarmHandler(int signum)
{ //signal handler
  sig = true;
    printf("Hello World!\n");
    alarm(1);
    totalAlarms++;
  
}

void sigIntHandler (int signum){
  end = clock();
  totalTime = ((double)end - start)/CLOCKS_PER_SEC;
  // printf("\n Total Alarms: %d \n", totalAlarms);
  printf("Total Time in Seconds: %f \n", totalTime);
  exit(0);
}

int main(int argc, char * argv[])
{
  start = clock();
  signal(SIGALRM,sigAlarmHandler);
  signal(SIGINT,sigIntHandler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second
  while(1) {
      sig = false;
      while(sig == false);
      //sig = false;
      printf("Turning was right!\n");
  } //busy wait for signal to be delivered
  return 0; //never reached
}
