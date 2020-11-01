#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
	pid_t pid;
	pid = fork();
	if(pid==0)
		execl("/bin/ls","ls","-l",NULL);
	else{
		wait(NULL);
		printf("Parent Process has waited for child to complete\n");
	}
	return 0;
}