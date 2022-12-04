#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

void  ClientProcess(int []);
void  ChildProcess(int []);

int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;
     int i;
    //  int bankAccount;
    //  int turn;
    //  int balance;

     

     ShmID = shmget(IPC_PRIVATE, 2*sizeof(int), IPC_CREAT | 0666);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     printf("Server has received a shared memory of four integers...\n");

     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if (*ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     printf("Server has attached the shared memory...\n");

     ShmPTR[0] = 0; //bankAccount
     ShmPTR[1] = 0; //turn
  
     printf("Server has filled %d %d in shared memory...\n",
            ShmPTR[0], ShmPTR[1]);

     printf("Server is about to fork a child process...\n");
     pid = fork();
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid == 0) {
          for (i = 0; i < 25; i++){
              ChildProcess(ShmPTR);
          }
          
          exit(0);
     }
     else {
       for (i = 0; i < 25; i++){
              ClientProcess(ShmPTR);
          }

     }

     wait(&status);
     printf("Server has detected the completion of its child...\n");
     shmdt((void *) ShmPTR);
     printf("Server has detached its shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Server has removed its shared memory...\n");
     printf("Server exits...\n");
     exit(0);
}

void  ClientProcess(int  SharedMem[])
{
     // printf("   Client process started\n");
     // printf("   Client found %d %d %d %d in shared memory\n",
     //            SharedMem[0], SharedMem[1], SharedMem[2], SharedMem[3]);
     
     // printf("   Client is about to exit\n");
     int account;
     int toSleep; 
     toSleep = rand() % 6;
     sleep(toSleep);
     while (SharedMem[1] != 0);
     account = SharedMem[0];
     
     if (account <= 100){
       int balance = rand() % 100;
         if (balance % 2 == 0){
          // add balance to deposit 
              account += balance;
              printf("Dear old Dad: Deposits $%d / Balance = $%d\n", balance, account);
          }
          else{
              printf("Dear old Dad: Doesn't have any money to give\n");
          } 
     }
     else {
         printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", account); 
     }
     SharedMem[0] = account; //copy account back to bank account 
     SharedMem[1] = 1; 
}

void  ChildProcess(int  SharedMem[]) {
     int balance;
     int toSleep;
     int account;
     toSleep = rand() % 6;
     sleep(toSleep);
     while (SharedMem[1] != 1);
     account = SharedMem[0]; 
     balance = rand() % 50;
     printf("Poor Student needs $%d\n", balance);
     if (balance <= account){
        account -= balance;
        printf("Poor Student: Withdraws $%d / Balance = $%d\n", balance, account);
     }
     else {
       printf("Poor Student: Not Enough Cash ($%d)\n", account);
     }

     SharedMem[0] = account; //copy account back to bankAccount
     SharedMem[1] = 0;
}
