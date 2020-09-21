#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
    pid_t pid;
    int n;
    printf("Enter range\n");
    scanf("%d",&n);
    int a[n];
    pid = vfork();
    if(pid == 0){
        int i,x,r;
        for(i=0;i<n;i++){
            x = i;
            a[i] = 0;
            while(x != 0){
                r = x%10;
                a[i] = a[i] + (r*r*r);
                x = x/10;
            }
        }
        exit(0);
    }
    else if(pid > 0){
        wait(NULL);
        int i;
        printf("Amstrong numbers in range 0 to %d\n",n);
        for(i=0;i<n;i++){
            if(a[i] == i)
                printf("%d ",i);
        }
        printf("\n");
    }
}