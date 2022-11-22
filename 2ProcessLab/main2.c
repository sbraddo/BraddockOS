#include  <stdio.h>
#include  <stdlib.h> 
#include  <sys/types.h>
#include <time.h>

#define   MAX_COUNT  rand() % 31


void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(int);              /* parent process prototype */

void  main(void)
{
     pid_t  pid;
     int status, i;

    
     // pid2 = fork();

     for(i = 0; i < 2; i++) {
          pid = fork();          
          if (pid == 0) 
               ChildProcess();
          else if (pid < 0)
               printf("Error: Fork less than 0");
     }
    
     for(i = 0; i < 2; i++) {
          pid = wait(&status); //blocking call putting the parent in the waiting state; waiting for the signal, in this case exit(0) in line 32
          ParentProcess(pid);
     } 
    
}

void  ChildProcess(void)
{
     int   i;
     srandom(time(NULL));
     int iterate = rand() % 31;
     int toSleep = rand() % 11;

    //  for (i = 1; i <= MAX_COUNT; i++)
    //       printf("   This line is from child, value = %d\n", i);
    //  printf("   *** Child process is done ***\n");
    // printf("%d\n", iterate);
    for ( i = 0; i <= iterate; i++ ){
      // printf("%d\n", i);
      printf("Child: %d is going to sleep!\n", getpid());
      sleep(toSleep);
      printf("Child Pid: is awake!\nWhere is my Parent?: %d\n", getppid());

    }

    exit(0);
}

void  ParentProcess(int pid)
{
     printf("Child Pid: %d has completed.\n", pid);
    //  for (i = 1; i <= MAX_COUNT; i++){
    //    printf("Child Pid: %d has completed.\n", status);
    //  }
    //       printf("This line is from parent, value = %d\n", i);
    //  printf("*** Parent is done ***\n");
}
