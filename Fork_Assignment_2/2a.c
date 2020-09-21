#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
	int n,i;
	printf("Value of n\n");
	scanf("%d",&n);
	int a[n];
	pid_t pid;
	pid = fork();
	if(pid == 0){
		printf("Odd\n");
		for(i=1;i<=2*n;i+=2)
			printf("%d ",i);
		printf("\n");
		exit(0);
	}
	else if(pid > 0){
		wait(NULL);
		printf("Even\n");
		for(i=0;i<=2*n;i+=2)
			printf("%d ",i);
		printf("\n");
		exit(0);
	}	
	return 0;
}
