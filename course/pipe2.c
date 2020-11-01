#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
int main(){
	int fd1[2],fd2[2];
	int pid;
	char pipe1writemsg[20]="Hi";
	char pipe2writemsg[20]="Hello";
	char readmsg[20];
	pipe(fd1);
	pipe(fd2);
	pid = fork();
	if(pid>0){
		printf("Parent\n");
		close(fd1[0]);
		close(fd2[1]);
		write(fd1[1],pipe1writemsg,sizeof(pipe1writemsg)+1);
		read(fd2[0],readmsg,sizeof(readmsg));
		printf("%s\n",readmsg);
	}
	else{
		printf("Child\n");
		close(fd1[1]);
		close(fd2[0]);
		read(fd1[0],readmsg,sizeof(readmsg));
		printf("%s\n",readmsg);
		write(fd2[1],pipe2writemsg,sizeof(pipe2writemsg)+1);
	}
	return 0;
}