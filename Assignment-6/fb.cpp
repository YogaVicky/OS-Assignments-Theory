#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<pthread.h>


char c[100];
char d[100];

struct node
{
int *arr;
int start;
int end;
int key;
int status;
};


int min(int x, int y) { return (x<=y)? x : y; } 
  
/* Returns index of x if present,  else returns -1 */
int fib(int arr[], int x, int n,int start) 
{ 
    /* Initialize fibonacci numbers */
    int fibMMm2 = 0;   // (m-2)'th Fibonacci No. 
    int fibMMm1 = 1;   // (m-1)'th Fibonacci No. 
    int fibM = fibMMm2 + fibMMm1;  // m'th Fibonacci 
  
    /* fibM is going to store the smallest Fibonacci 
       Number greater than or equal to n */
    while (fibM < n) 
    { 
        fibMMm2 = fibMMm1; 
        fibMMm1 = fibM; 
        fibM  = fibMMm2 + fibMMm1; 
    } 
  
    // Marks the eliminated range from front 
    int offset = start-1; 
  
    /* while there are elements to be inspected. Note that 
       we compare arr[fibMm2] with x. When fibM becomes 1, 
       fibMm2 becomes 0 */
    while (fibM > 1) 
    { 
        // Check if fibMm2 is a valid location 
        int i = min(offset+fibMMm2, n-1); 
  
        /* If x is greater than the value at index fibMm2, 
           cut the subarray array from offset to i */
        if (arr[i] < x) 
        { 
            fibM  = fibMMm1; 
            fibMMm1 = fibMMm2; 
            fibMMm2 = fibM - fibMMm1; 
            offset = i; 
        } 
  
        /* If x is greater than the value at index fibMm2, 
           cut the subarray after i+1  */
        else if (arr[i] > x) 
        { 
            fibM  = fibMMm2; 
            fibMMm1 = fibMMm1 - fibMMm2; 
            fibMMm2 = fibM - fibMMm1; 
        } 
  
        /* element found. return index */
        else return i; 
    } 
  
    /* comparing the last element with x */
    if(fibMMm1 && arr[offset+1]==x)return offset+1; 
  
    /*element not found. return -1 */
    return -1; 
} 


void* bs(void *arg)
{
    struct node* temp=(struct node*)arg;
temp->status=-1;
while(temp->start<=temp->end)
{
int mid=temp->start+(temp->end-temp->start)/2;
if(temp->arr[mid]==temp->key)
{temp->status=mid;break;}
else if(temp->arr[mid]<temp->key)
temp->start=mid+1;
else
temp->end=mid-1;
}


pthread_exit(NULL);
}

void swap(int *p,int *q)
{
int temp=*p;
*p=*q;
*q=temp;

}

void bubblesort(int a[],int ch,int start ,int end)
{
int i,j;
for(i=start;i<end-1;i++)
{
for(j=start;j<end-(i-start)-1;j++)
{

int choice=(ch==0)?(a[j]<a[j+1]):(a[j]>a[j+1]);
if(choice==1)
{
swap(&a[j],&a[j+1]);

}
}
}
}



void process3(int arr[],int n,int key1,int key2)
{

pthread_t pth[2];
struct node *temp=(struct node* )malloc(2*sizeof(struct node));
temp[0].arr=arr;
temp[0].start=0;
temp[0].end=n/2-1;
temp[0].key=key1;

temp[1].arr=arr;
temp[1].start=n/2;
temp[1].end=n;
temp[1].key=key2;
pthread_create(&pth[0],NULL,bs,&temp[0]);
pthread_create(&pth[1],NULL,bs,&temp[1]);

pthread_join(pth[0],NULL);
pthread_join(pth[1],NULL);

if(temp[0].status!=-1)
printf("Key found at first half\n");
    else
 printf("Key not found at first half\n");

 if(temp[1].status!=-1)
printf("Key found at second half\n");
    else
 printf("Key not found at second half\n");


}

int main(int argc,char* argv[])
{

clock_t t1,t2;

    if(argc<=2)
    {
        printf("Less Number of Arguments:");
        exit(0);
    }
    else
    {
        int n=atoi(argv[1]);
        int arr[n];
        memset(arr,0,sizeof(arr));
        
        for(int i=0;i<n;i++)
        {
            arr[i]=atoi(argv[i+2]);
        }
           
           int key1,key2;
           printf("Enter key 1 and key2 to be searched:\n");
           scanf("%d %d",&key1,&key2);
           
           
           bubblesort(arr,1,0,n/2);
           bubblesort(arr,1,n/2,n);
           
           
           

            printf("Elements after Sorting:\n");

            for(int i=0;i<n;i++)
                printf("%d ",arr[i]);
            printf("\n");

		t1=clock();
            process3(arr,n,key1,key2);
            	t2=clock();
           
            printf("Binary Search:%lf\n",(t2-t1)/(double)CLOCKS_PER_SEC);
            
            t1=clock();
            printf("At Index:Key=%d ",fib(arr,key1,n/2,0));
            printf("At Index:Key=%d ",fib(arr,key2,n,n/2));
            t2=clock();
            
            printf("Fibonacci search:%lf\n",(t2-t1)/(double)CLOCKS_PER_SEC);
            
        
   
    }
    return 0;
}
