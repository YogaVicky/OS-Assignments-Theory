#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *prime(void *arg)
{
    int n = *((int*)arg);
    int i,flag=0;

    for(i=2;i<n;i++)
    {
        if(n%i == 0)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0)
        printf("%d ",n);
}

int main(int argc, char *argv[])
{
    int n,i;
    
    if(argc != 2)
    {
        printf("Invalid number of arguments\n");
        return 0;
    }

    n = atoi(argv[1]);
    if(n<=1)
    {
        printf("No prime numbers in the range\n");
        return 0;
    }
    pthread_t pth[n];
    printf("Prime numbers less than %d: ",n);
    
    for(i=2;i<=n;i++)
    {
        pthread_create(&pth[i-2],NULL,prime,&i);
        pthread_join(pth[i-2],NULL);
    }

    return 0;
}