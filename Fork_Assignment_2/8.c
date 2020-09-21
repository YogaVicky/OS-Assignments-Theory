#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int fibbonacci(int a[], int n){
    if(n == 1){
        a[0] = 0;
        return a[0];
    }
    else if(n==2){
        a[1] = 1;
        return a[1];
    }
    else{
        pid_t pid;

        a[n-1] = 0;
        pid = vfork();
        if(pid == 0)
        {
            a[n-1] += fibbonacci(a,n-2);
            exit(0);
        }
        else if(pid > 0)
        {
            a[n-1] += fibbonacci(a,n-1);
        }
        return a[n-1];
    }
}
int main(){
    int n,i;
    printf("Enter number of terms\n");
    scanf("%d",&n);
    int a[n];
    if(n <= 0){
        printf("Fibbonacci series with %d terms is not possible\n",n);
    }
    else{
        fibbonacci(a,n);
        printf("Fibbonacci series with %d terms\n",n);
        for(i=0;i<n;i++)
            printf("%d ",a[i]);
        printf("\n");
    }
    return 0;
}


