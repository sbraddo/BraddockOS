// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 
    // We use two pipes 
    // First pipe to send input string from parent 
    // Second pipe to send concatenated string from child 
  
    int fd1[2];  // Used to store two ends of first pipe 
    int fd2[2];  // Used to store two ends of second pipe 
    int status;
  
    char fixed_str[] = "howard.edu"; 
    char concat_str[100];
    char concat_str2[100];
    char input_str[100]; 
    char input_str2[100];
    pid_t p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    printf("Enter a string to concatenate: ");
    scanf("%s", input_str);
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
        char concat_str[100];
        close(fd1[0]);  // Close reading end of pipes 
        close(fd2[0]);
  
        // Write input string and close writing end of first 
        // pipe. 
        write(fd1[1], input_str, strlen(input_str)+1); 
        
  
        // Wait for child to send a string 
        // wait(NULL); 
  
        // close(fd1[1]); // Close writing end of pipes 
        wait(&status);
        // close(fd2[1]); 
        read(fd2[0], concat_str2, 100);
        int k = strlen(concat_str2); 
        int i; 
        for (i=0; i<strlen(concat_str2); i++) 
            concat_str2[k++] = concat_str[i];

        concat_str2[k] = '\0';
        // printf("2nd concatenated string: %s\n", strcat(concat_str, input_str2));
        close(fd1[1]);
        close(fd2[0]);
    } 
    // child process 
    else
    { 
        close(fd1[1]);  // Close writing end of first pipes 
        close(fd2[1]); 
      
        // Read a string using first pipe 
        char concat_str[100]; 
        read(fd1[0], concat_str, 100); 
  
        // Concatenate a fixed string with it 
        int k = strlen(concat_str); 
        int i; 
        for (i=0; i<strlen(fixed_str); i++) 
            concat_str[k++] = fixed_str[i]; 
  
        concat_str[k] = '\0';   // string ends with '\0' 
  
        printf("Concatenated string %s\n", concat_str);

        printf("Enter a string to concatenate: ");
        scanf("%s", input_str2);
        write(fd2[1], input_str2, strlen(input_str2) + 1);

        printf("2nd concatenated string: %s\n", strcat(concat_str, input_str2));


        // Close both reading ends 
        close(fd1[0]); 
        close(fd2[1]); 

        // write(fd2[1], concat_str, strlen(concat_str) + 1);
        // close(fd2[1]);

  
        exit(0); 
    } 
} 
