#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define N 20

struct node
{
    int a[N];
    int n;
};

void *AscendingSort(void *arg)
{
    struct node* A = (struct node*) arg;
    int i,j,temp;

    for(i=0;i<A->n;i++)
    {
        for(j=0;j<A->n-i-1;j++)
        {
            if(A->a[j] > A->a[j+1])
            {
                temp = A->a[j];
                A->a[j] = A->a[j+1];
                A->a[j+1] = temp;
            }
        }
    }
    printf("Thread 1:\nArray sorted in ascending order: ");
    for(i=0;i<A->n;i++)
        printf("%d ",A->a[i]);
    printf("\n");
}

void *DescendingSort(void *arg)
{
    struct node* A = (struct node*) arg;
    int i,j,temp;

    for(i=0;i<A->n;i++)
    {
        for(j=0;j<A->n-i-1;j++)
        {
            if(A->a[j] < A->a[j+1])
            {
                temp = A->a[j];
                A->a[j] = A->a[j+1];
                A->a[j+1] = temp;
            }
        }
    }
    printf("Thread 2:\nArray sorted in descending order: ");
    for(i=0;i<A->n;i++)
        printf("%d ",A->a[i]);
    printf("\n");
}

int main()
{
    pthread_t pth[2];
    struct node *A = (struct node*)malloc(sizeof(struct node));
    int i;

    printf("Enter size of array: ");
    scanf("%d",&A->n);
    printf("Enter %d numbers: ",A->n);
    for(i=0;i<A->n;i++)
        scanf("%d",&A->a[i]);
    
    pthread_create(&pth[0],NULL,AscendingSort,A);
    pthread_join(pth[0],NULL);
    pthread_create(&pth[1],NULL,DescendingSort,A);
    pthread_join(pth[1],NULL);

    return 0;
}