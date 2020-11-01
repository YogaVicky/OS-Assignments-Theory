#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#define BUFFERSIZE 25
int main()
{
   srand(time(0)); // inititig the timer to use it as a seed for the rand() function
   int pipe1fd[2], pipe2fd[2];
   char writemsg[BUFFERSIZE];
   char readmsg[BUFFERSIZE];
   pid_t pid;
   if (pipe(pipe1fd) == -1) //checking the pipe1fd
   {
       fprintf(stderr, "Pipe 1 failed");
       return 1;
   }
   if (pipe(pipe2fd) == -1) //checking the pipe2fd
   {
       fprintf(stderr, "Pipe 2 failed");
       return 1;
   }
   pid = fork();
   if (pid > 0) //parent
   {
       close(pipe1fd[0]); //close unwanted pipe 1 read
       close(pipe2fd[1]); //close unwanted pipe 2 write
       strcpy(writemsg, "Kancheepuram");
       printf("In parent write pipe 1 : %s\n", writemsg);
       write(pipe1fd[1], writemsg, strlen(writemsg) + 1);
       read(pipe2fd[0], readmsg, BUFFERSIZE);
       printf("In parent read pipe 2:%s\n", readmsg);
   }
   if (pid == 0) //child
   {
 
       close(pipe1fd[1]); //close unwanted pipe 1 write
       close(pipe2fd[0]); //close unwanted pipe 2 read
       read(pipe1fd[0], readmsg, BUFFERSIZE);
       printf("In child read 1:%s\n", readmsg);
       int num = (rand() % (strlen(readmsg))) + 1; //to choose a random substring
       int i = 0;
       while (i < num) //substring from 0 to num of the readmsg copied to writemsg
       {
           writemsg[i] = readmsg[i];
           i++;
       }
       writemsg[i] = '\0'; //adding the end character of the string
       printf("In child write 2: %s\n", writemsg);
       write(pipe2fd[1], writemsg, strlen(writemsg) + 1);
   }
   return 0;
}
