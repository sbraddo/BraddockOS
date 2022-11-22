/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

bool sig = false;
int status;
 

void alarmhandler(int signum)
{ //signal handler
  printf("Hello World!\n");
  sig = true;
  alarm(3);
  //exit(1); //exit after printing
  //wait(0);
}

int main(int argc, char * argv[])
{
  signal(SIGALRM, alarmhandler); //register handler to handle SIGALRM
  alarm(3); //Schedule a SIGALRM for 1 second

  while(1) {
      sig = false;
      while(sig == false);
      //sig = false;
      printf("Turning was right!\n");
      //busy wait for signal to be delivered
  }
  return 0; //never reached
}
