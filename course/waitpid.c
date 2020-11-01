#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
	pid_t childpid;
	childpid = fork();
	if(childpid==0){
		printf("Inside Child\n");
	}
	else if(childpid<0){
		printf("Error\n");
	}
	else{
		printf("Inside Parent\n");
		int returnStatus;
		printf("%d\n",childpid);
		waitpid(childpid,&returnStatus,0);
		printf("%d\n",childpid);
		printf("%d\n",returnStatus);
		if(returnStatus!=-1)
			printf("Child terminated normally\n");
		else
			printf("Child terminated with error\n");
	}
	return 0;
}