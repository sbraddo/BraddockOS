/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

bool sig = true;
int status;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  alarm(1);
  //exit(1); //exit after printing
  //wait(0);
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second
  while(sig){
    sleep(1);
    printf("Turning was right!\n");
  } //busy wait for signal to be delivered
  return 0; //never reached
}
