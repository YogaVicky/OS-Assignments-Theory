#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
	int n,i;
	printf("Enter size of array\n");
	scanf("%d",&n);
	int a[n];
	printf("Enter %d numbers\n",n);
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("\n");
	int j,k,temp;
	pid_t pid;
	pid = vfork();
	if(pid == 0){
		for(j=0;j<n;j++){
			for(k=0;k<n-j-1;k++){
				if(a[k] > a[k+1]){
					temp = a[k];
					a[k] = a[k+1];
					a[k+1] = temp;
				}
			}
		}
		printf("Child\n");
		printf("Sorted array in ascending order\n");
		for(i=0;i<n;i++)
			printf("%d ",a[i]);
		printf("\n");
		exit(0);
	}
	else if(pid > 0){
		for(j=0;j<n;j++){
			for(k=0;k<n-j-1;k++){
				if(a[k] < a[k+1]){
					temp = a[k];
					a[k] = a[k+1];
					a[k+1] = temp;
				}
			}
		}
		printf("Parent\n");
		printf("Sorted array in descending order\n");
		for(i=0;i<n;i++)
			printf("%d ",a[i]);
		printf("\n");
	}
	return 0;
}
