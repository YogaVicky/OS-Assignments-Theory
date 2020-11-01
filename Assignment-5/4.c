#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#define BUFFERSIZE 25
void reverse(char *x, int begin, int end)
{
char c;
if (begin >= end)
    return;
//swapping first and last of the given string
c = *(x + begin);
*(x + begin) = *(x + end);
*(x + end) = c;
reverse(x, ++begin, --end); // recuresive call to revese the string
}
int palindrome(char *str, int begin, int end)
{
char c;
if (begin >= end)
    return 1;
if (*(str + begin) != *(str + end))
    return 0;

palindrome(str, ++begin, --end);
}
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
    strcpy(writemsg, "abba");
    printf("In parent write pipe 1 : %s\n", writemsg);
    write(pipe1fd[1], writemsg, strlen(writemsg) + 1);
    read(pipe2fd[0], readmsg, BUFFERSIZE);
    printf("In parent read pipe 2:%s\n", readmsg);
    if (palindrome(readmsg, 0, strlen(readmsg) - 1) == 1)
        printf("The reversed string %s is a palindrome\n", readmsg);
    else{
        printf("The reversed string %s is a not palindrome", readmsg);
        printf("\n");    
    }
}
if (pid == 0) //child
{

    close(pipe1fd[1]); //close unwanted pipe 1 write
    close(pipe2fd[0]); //close unwanted pipe 2 read
    read(pipe1fd[0], readmsg, BUFFERSIZE);
    printf("In child read 1:%s\n", readmsg);
    reverse(readmsg, 0, strlen(readmsg) - 1); //reverse function for string
    strcpy(writemsg, readmsg);
    printf("In child write 2: %s\n", writemsg);
    write(pipe2fd[1], writemsg, strlen(writemsg) + 1);
}
return 0;
}
