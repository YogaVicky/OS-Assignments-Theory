#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
	pid_t pid;
	pid = fork();
	int a = 5;
	if(pid>0){
		a++;
		printf("Parent\n");
		printf("%d\n", a);
	}
	else{
		printf("Child\n");
		printf("%d\n", a);
	}
	return 0;
}