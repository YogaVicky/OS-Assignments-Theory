#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
int heap[10000];
const int n;
int Colsum(int a[n][n])
{
int count=0;
int countn=0;
for(int i=0;i<n;i++)
    count+=a[i][0];
for(int j=1;j<n;j++)
{
    countn=0;
for(int i=0;i<n;i++)
    countn+=a[i][j];
if(count!=countn)
return -1;
}
return count;
}
int Rowsum(int a[n][n])
{
int count=0;
int countn=0;
for(int i=0;i<n;i++)
    count+=a[0][i];
for(int j=1;j<n;j++)
{
    countn=0;
for(int i=0;i<n;i++)
    countn+=a[j][i];

if(count!=countn)
return -1;
}
return count;
}
int Diagsum(int a[n][n])
{
    int countd1=0,countd2=0;
for(int i=0;i<n;i++)
{
    countd1+=a[i][i];
    countd2+=a[i][n-i-1];
}
if(countd1==countd2)
    return countd1;
else
{
    return -1;
}
}
int nocheck(int a[n][n])
{
for(int i=0;i<n;i++)
    heap[i]=0;
for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
        {
            if(heap[a[i][j]]!=1)
                heap[a[i][j]]=1;
            else
            {
                    return -1;
            }
        }
return 1;
}
int main()
{
pid_t pid1,pid2,pid3;
int sum=0,status,flag=0,x;
printf("Enter the dimension value of the square matrix:\n");
scanf("%d",&n);
int a[n][n];
printf("Enter the array:\n");
for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
        scanf("%d",&a[i][j]);
printf("\nInference-Check:\n");
pid1=vfork();
if(pid1==0)
{
sum=Rowsum(a);
_exit(0);      
}
else
{    
    pid2=vfork();    
    if(pid2==0)
    {
        printf("1.Column Sum :");
        if(Colsum(a)!=sum)
            {
                printf("No\n");
                flag=1;
            }
        else
        {
            printf("Yes\n");
        }
        
        _exit(0);
    }
    pid3=vfork();
    if(pid3==0)
    {
        printf("2.Diagnoal Sum :");
        
        if(Diagsum(a)!=sum)
            {
                printf("No\n");
                flag=1;

            }
        else
        {
            printf("Yes\n");
        }
        _exit(0);
    }
    else
    {
        printf("3.Unique Numbers :");
        if(nocheck(a)==-1)
            {
                printf("No\n");
                flag=1;
            }
        else
        {
            printf("Yes\n");
        }
    }
}
waitpid(-1,&status,0);
if(flag!=1)
    printf("It is a magic square\n");
else
{
    printf("It is not a magic square\n");
}
return 0;
}
