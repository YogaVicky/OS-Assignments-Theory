#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
	int n,i;
	printf("Value of n\n");
	scanf("%d",&n);
	int a[n];
	printf("Enter %d numbers\n",n);
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	pid_t pid;
	pid = vfork();
	if(pid == 0){
		int j,sum1=0;
		for(j=0;j<n;j++){
			if(a[j] % 2 == 0)
				sum1 += a[j];
		}
		printf("Sum of even terms - %d\n",sum1);
		exit(0);
	}
	else if(pid > 0){
		wait(NULL);
		int k,sum2=0;
		for(k=0;k<n;k++){
			if(a[k] % 2 == 1)
				sum2 += a[k];
		}
		printf("Sum of odd terms - %d\n",sum2);
	}
	return 0;
}
