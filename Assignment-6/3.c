#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define N 100

struct node
{
    int a[N],beg,end,n,x,f;
};

void *BinarySearch(void *arg)
{
    struct node *t = (struct node *) arg;
    int beg,end,x;

    beg = t->beg;
    end = t->end;
    x = t->x;

    int mid,m;
    while(beg <= end)
	{
		mid = (beg+end)/2;
		if(t->a[mid] == x)
		{
			t->f = 1;
            break;
		}
    	else if(t->a[mid] < x)
			beg = mid+1;
        else
			end = mid-1;
	}
}

int main()
{
    int i,j;
    struct node *A = (struct node*)malloc(sizeof(struct node));
    printf("Enter the size of array: ");
    scanf("%d",&A->n);
    printf("Enter %d numbers: ",A->n);
    for(i=0;i<A->n;i++)
        scanf("%d",&A->a[i]);
    printf("Enter number to search: ");
    scanf("%d",&A->x);
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
    pthread_t pth[2];
    A->f = 0;
    A->beg = 0;
    A->end = A->n/2-1;
    pthread_create(&pth[0],NULL,BinarySearch,A);
    pthread_join(pth[0],NULL);
    A->beg = A->n/2;
    A->end = A->n-1;
    pthread_create(&pth[1],NULL,BinarySearch,A);
    pthread_join(pth[1],NULL);
    if(A->f == 0)
        printf("%d not found in array\n",A->x);
    else
        printf("%d is present in array\n",A->x);

    return 0;
}