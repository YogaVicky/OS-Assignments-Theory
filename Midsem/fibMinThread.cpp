#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<pthread.h>


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
void *fib(void *arg) //void *arg
{ 

	struct node* temp=(struct node*)arg;
	int x=temp->key;
	int start=temp->start;
	int n=temp->end;
	int *arr=temp->arr;
	temp->status=-1;
	
	
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
        if(arr[i]==x)
        {
        temp->status=i;
        break;
        }
    } 
  
    /* comparing the last element with x */
    if(fibMMm1 && arr[offset+1]==x) 
    temp->status= offset+1; 
  
    /*element not found. return -1 */
   pthread_exit(NULL);
} 


void* bs(void *arg){
    struct node* temp=(struct node*)arg;
    temp->status=-1;
    while(temp->start<=temp->end){
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

void swap(int *p,int *q){
    int temp=*p;
    *p=*q;
    *q=temp;
}

void bubblesort(int a[],int ch,int start ,int end){
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

void process3(int arr[],int n,int key1,int key2){
    clock_t t1,t2;
    pthread_t pth[4];
    struct node *temp=(struct node* )malloc(4*sizeof(struct node));
    temp[0].arr=arr;
    temp[0].start=0;
    temp[0].end=n/4-1;
    temp[0].key=key1;

    temp[1].arr=arr;
    temp[1].start=n/4;
    temp[1].end=n/2;
    temp[1].key=key1;

    temp[2].arr=arr;
    temp[2].start=n/2;
    temp[2].end=n/4+n/2-1;
    temp[2].key=key2;

    temp[3].arr=arr;
    temp[3].start=n/2+n/4;
    temp[3].end=n;
    temp[3].key=key2;

    t1=clock();
                
    for(int i=0;i<4;i++)
        pthread_create(&pth[i],NULL,bs,&temp[i]);


    for(int i=0;i<4;i++)
        pthread_join(pth[i],NULL);


    t2=clock();

    printf("Binary Search:%lf\n",(t2-t1)/(double)CLOCKS_PER_SEC);

    for(int i=0;i<4;i++){
        if(temp[i].status!=-1)
            printf("Key found at %d half\n",i+1);
        else
        printf("Key not found at %d half\n",i+1);
    }

}
void process4(int arr[],int n,int key1,int key2){
    clock_t t1,t2;
    pthread_t pth[4];

    struct node *temp=(struct node* )malloc(4*sizeof(struct node));
    temp[0].arr=arr;
    temp[0].start=0;
    temp[0].end=n/4;
    temp[0].key=key1;

    temp[1].arr=arr;
    temp[1].start=n/4;
    temp[1].end=n/2;
    temp[1].key=key1;

    temp[2].arr=arr;
    temp[2].start=n/2;
    temp[2].end=n/4+n/2;
    temp[2].key=key2;

    temp[3].arr=arr;
    temp[3].start=n/2+n/4;
    temp[3].end=n;
    temp[3].key=key2;

    t1=clock();
                
    for(int i=0;i<4;i++)
        pthread_create(&pth[i],NULL,fib,&temp[i]);


    for(int i=0;i<4;i++)
        pthread_join(pth[i],NULL);


    t2=clock();

    printf("Fibonacci:%lf\n",(t2-t1)/(double)CLOCKS_PER_SEC);

    for(int i=0;i<4;i++){
        if(temp[i].status!=-1)
            printf("Key found at %d half\n",i+1);
        else
        printf("Key not found at %d half\n",i+1);
    }
}

int main(int argc,char* argv[])
{

    srand(time(0));
    int n = (rand() % 20 + 1) * 2;
    printf("n: %d\n", n);
    int arr[n];
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100 + 1;
    printf("Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int key1,key2;
    printf("Enter key1 and key2 to be searched:\n");
    scanf("%d %d",&key1,&key2);

    bubblesort(arr,1,0,n/4);
    bubblesort(arr,1,n/4,n/2);
    bubblesort(arr,1,n/2,(n/2+n/4));
    bubblesort(arr,1,(n/2+n/4),n);
    printf("Elements after Sorting:\n");
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);
    printf("\n");
	process3(arr,n,key1,key2);
	process4(arr,n,key1,key2);

    return 0;
}
