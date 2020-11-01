#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define N 10000000000

struct node
{
    int a[N];
    int n;
};

int power(int x, int n)
{
    int a=1,i;

    for(i=0;i<n;i++)
        a *= x;
    
    return a;
}

void *Powersum(void *arg)
{
    int x,r,m,a;
    int *n = (int*)arg;

    x = *n;
    m=0;
    while(x != 0)
    {
        m++;
        x /= 10;
    }
    x = *n;
    a = 0;
    while(x != 0)
    {
        r = x%10;
        a = a + power(r,m);
        x = x/10;
    }
    if(a==*n)
        printf("%d ",*n);
}

int main()
{
    int n,i;

    printf("Enter range: ");
    scanf("%d",&n);
    pthread_t pth[n];
    
    for(i=0;i<n;i++)
    {
        pthread_create(&pth[i],NULL,Powersum,&i);
        pthread_join(pth[i],NULL);
    }
    return 0;
}