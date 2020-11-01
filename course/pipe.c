#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
int main(){
	char writemsg[25]="Greetings";
	char readmsg[25];
	int fd[2];
	pid_t pid;
	pipe(fd);
	pid = fork();
	if(pid<0){
		printf("Fork Failed\n");
		return 0;
	}
	if(pid>0){
		close(fd[0]);
		write(fd[1],writemsg,strlen(writemsg)+1);
		close(fd[1]);
	}
	else{
		close(fd[1]);
		read(fd[0],readmsg,25);
		printf("Read %s\n", readmsg);
		close(fd[0]);
	}
	return 0;
}