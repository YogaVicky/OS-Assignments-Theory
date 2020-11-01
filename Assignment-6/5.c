#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define N 100

struct node
{
    int a[N],n;
};

void *mean(void *arg)
{
    struct node *t = (struct node*) arg;
    int sum=0,i;

    for(i=0;i<t->n;i++)
        sum += t->a[i];
    
    float s = sum/1.0;

    printf("Mean = %f\n",s/t->n);
}

void *median(void *arg)
{
    struct node *t = (struct node*) arg;
    float median;

    if(t->n%2 == 0)
    {
        median;
        median = (t->a[t->n/2 - 1] + t->a[t->n/2])/2.0;
    }
    else
        median = t->a[t->n/2];
    
    printf("Median = %f\n",median);
}

void *mode(void *arg)
{
    struct node *t = (struct node*) arg;
    int max=0,c=0,mode,i=0;
    mode = t->a[0];
    c++;

    while(i<t->n)
    {
        while((t->a[i+1] != t->a[i]) && i<t->n)
        {
            c++;
            i++;
        }
        if(c > max)
        {
            max = c;
            mode = t->a[i];
        }
        i++;
        c = 1;
    }
    printf("Mode = %d\n",mode);
}

int main()
{
    struct node *A = (struct node*)malloc(sizeof(struct node));
    int i,j;

    printf("Enter size of array: ");
    scanf("%d",&A->n);

    printf("Enter %d numbers: ",A->n);
    for(i=0;i<A->n;i++)
        scanf("%d",&A->a[i]);
    
    for(i=0;i<A->n;i++)
    {
        for(j=0;j<A->n-i-1;j++)
        {
            if(A->a[j] > A->a[j+1])
            {
                int temp = A->a[j];
                A->a[j] = A->a[j+1];
                A->a[j+1] = temp;
            }
        }
    }

    pthread_t pth[3];

    pthread_create(&pth[0],NULL,mean,A);
    pthread_join(pth[0],NULL);
    pthread_create(&pth[1],NULL,median,A);
    pthread_join(pth[1],NULL);
    pthread_create(&pth[2],NULL,mode,A);
    pthread_join(pth[2],NULL);

    return 0;
}