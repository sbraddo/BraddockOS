/* for refernce: https://www.geeksforgeeks.org/making-linux-shell-c/ ,
 https://www.tutorialspoint.com/cprogramming/switch_statement_in_c.htm ,
 https://www.programiz.com/c-programming/library-function/string.h/strcmp*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

void inputEOF (int x);
void printDir ();

char prompt[] = ">>> ";
char delimiters[] = " \t\r\n";
extern char **environ;
char *getcwd(char *buf, size_t size);
pid_t pid;
bool inBackground = false;
int i; 

void alarmhandler(int signum)
{ //signal handler
  if (pid == -1){
      kill(pid, SIGINT);
  }
}

int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
    char cwd[MAX_COMMAND_LINE_LEN];
  
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    int status;
    int pos;
    char *name;
    char *val;
    char *token;

    signal(SIGALRM, alarmhandler);
    	
    while (true) {
      
        do{ 
            // Print the shell prompt.
            printf("%s", prompt);
            fflush(stdout);

            // Read input from stdin and store it in command_line. If there's an
            // error, exit immediately. (If you want to learn more about this line,
            // you can Google "man fgets")
        
            if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
                fprintf(stderr, "fgets error");
                exit(0);
            }
 
        }while(command_line[0] == 0x0A);  // while just ENTER pressed

      
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            // inputEOF(0);
            return 0;
        }

        // TODO:
        // 
        
	    // 0. Modify the prompt to print the current working directory
		// if(stdin == getcwd()){
        //     printf();
        // }
			
        // 1. Tokenize the command line input (split it on whitespace)
        token = strtok(command_line, delimiters);
        pos = 0;

        while (token != NULL){
            arguments[pos] = token;
            pos ++;
            token = strtok(NULL, delimiters);
        }


      
        // 2. Implement Built-In Commands
        int cmdInput = 0;
        int numCmds = 6;
        char* Commands[numCmds];
        Commands[0] = "cd";
        Commands[1] = "echo";
        Commands[2] = "env";
        Commands[3] = "exit";
        Commands[4] = "pwd";
        Commands[5] = "setenv";

        for (i = 0; i < numCmds; i++){
            if(strcmp(arguments[0], Commands[i]) == 0){
                cmdInput = i + 1;
    
            }
        }
      
        switch(cmdInput){
            case 1:
                if (arguments[1] == NULL){
                    chdir(getenv("HOME"));
                }
                else{
                    chdir(arguments[1]);
                }
                break;
            case 2:
                for (i =0; i < pos -1; i++){
                    if (arguments[i][0] == "$"){
                        printf("%s\n", getenv(&arguments[i][1]));
                    }
                    else{
                        printf("%s\n", arguments[i]);
                    }
                }
                break;
            case 3:
                printf("%s\n", getenv(arguments[1]));
                break;
            case 4: 
                printf("GOODBYE \n");
                exit(status);
            case 5:
                printf("%s\n", getcwd(cwd, sizeof(cwd)));
                break;
            case 6:
                name = strtok(arguments[1], "=");
                val = strtok(NULL, "=");
                setenv(name, val, 1);
                break;
            default:
            //child process 
            alarm(10);
            pid = fork();
            if (pid < 0){
                printf("ERROR CREATING CHILD PROCESS\n");
                exit(status);
            }
            else if (pid == 0){
                if (execvp(arguments[0], arguments) == 1){
                    printf("NOT EXECUTABLE\n");
                }
            }
            else if (pid > 0){
                if (inBackground == true){
                    pid = wait(NULL);
                    inBackground = false;
                }
            }
            break;

        }
        // 3. Create a child process which will execute the command line input

  
        // 4. The parent process should wait for the child to complete unless its a background process
      
      
        // Hints (put these into Google):
        // man fork
        // man execvp
        // man wait
        // man strtok
        // man environ
        // man signals
        
        // Extra Credit
        // man dup2
        // man open
        // man pipes
    }
    // This should never be reached.
    return -1;
}

// void inputEOF (int x){
//     fflush(stdout);
//     fflush(stderr);
//     exit(x);
// }
