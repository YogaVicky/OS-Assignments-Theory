#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#define BUFFERSIZE 25
int main()
{
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
       char str1[50] = "IIITDM ";
       read(pipe2fd[0], readmsg, BUFFERSIZE);
       printf("In parent read pipe 2:%s\n", readmsg);
       strcat(str1, readmsg); //string catenation
       printf("In parent write pipe 1 : %s\n", str1);
       write(pipe1fd[1], str1, strlen(str1) + 1);
   }
   if (pid == 0) //child
   {
       close(pipe1fd[1]); //close unwanted pipe 1 write
       close(pipe2fd[0]); //close unwanted pipe 2 read
       char str2[50];
       strcpy(str2, "Kancheepuram");
       printf("in child write 2: %s\n", str2);
       write(pipe2fd[1], str2, strlen(str2) + 1);
       read(pipe1fd[0], readmsg, BUFFERSIZE);
       printf("In child read 1:%s\n", readmsg);
   }
   return 0;
}
