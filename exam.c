#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
	int pid; 
	printf("I like OS!\n"); 
	pid = fork();
	if( pid == 0 ){
	 	printf("I like DBMS!\n");
	 	sleep(60);
	 	execlp("./bin1", "bin1", NULL);
		printf("I like DSA!\n"); 
	}
	else if(pid > 0){
		printf("I like HCI!\n");
		execlp("/bin/date", "date", NULL);
		printf("I like Data Analytics!\n"); 
	}
	printf("I Like COE!!! \n");
	return 0; 
}
