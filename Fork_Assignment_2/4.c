#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
    pid_t pid;
    int n;
    printf("Enter value of n: ");
    scanf("%d",&n);
    pid = vfork();
    if(pid == 0){
        int i,i0,i1,i2;
        i0 = 0;
        i1 = 1;
        printf("Child process:\n");
        printf("Fibonacci series upto %d terms: ",n);
        if(n == 0)
            printf("No terms in series\n");
        else if(n == 1)
            printf("%d\n",i0);
        else{
            printf("%d %d ",i0,i1);
            for(i=3;i<=n;i++){
                i2 = i0+i1;
                printf("%d ",i2);
                i0 = i1;
                i1 = i2;
            }
            printf("\n");
        }
        exit(0);
    }
    else if(pid > 0){
        int i,j,np=0;
        printf("Parent process:\n");
        printf("Prime series upto %d: ",n);
        if(n < 2)
            printf("No terms in series\n");
        else if(n >= 2){
            for(i=2;i<n;i++){
                np = 0;
                for(j=2;j<i;j++){
                    if(i%j == 0){
                        np = 1;
                        break;
                    }
                }
                if(np == 0)
                    printf("%d ",j);
            }
            printf("\n");
        }
    }
    return 0;
}