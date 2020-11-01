#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<pthread.h>
#include<iostream>
struct node{
    int *arr;
    int start;
    int end;
    int key;
    int status;
};

int min(int x, int y){ return (x<=y)? x : y; } 
  
void *fib(void *arg){ 

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
    while (fibM < n){ 
        fibMMm2 = fibMMm1; 
        fibMMm1 = fibM; 
        fibM  = fibMMm2 + fibMMm1; 
    }
    // Marks the eliminated range from front 
    int offset = start-1; 
    /* while there are elements to be inspected. Note that 
       we compare arr[fibMm2] with x. When fibM becomes 1, 
       fibMm2 becomes 0 */
    while (fibM > 1){ 
        // Check if fibMm2 is a valid location 
        int i = min(offset+fibMMm2, n-1); 
        /* If x is greater than the value at index fibMm2, 
           cut the subarray array from offset to i */
        if (arr[i] < x){ 
            fibM  = fibMMm1; 
            fibMMm1 = fibMMm2; 
            fibMMm2 = fibM - fibMMm1; 
            offset = i;
            printf("Key %d greater than the min(offset+fibMMm2, n-1) value%d\n",x,arr[i]); 
        } 
        /* If x is greater than the value at index fibMm2, 
           cut the subarray after i+1  */
        else if (arr[i] > x){ 
            fibM  = fibMMm2; 
            fibMMm1 = fibMMm1 - fibMMm2; 
            fibMMm2 = fibM - fibMMm1;
            printf("Key %d lesser than the min(offset+fibMMm2, n-1) value%d\n",x,arr[i]); 
        } 
  
        /* element found. return index */
        if(arr[i]==x){
            printf("Key %d Found\n",x);
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
        if(temp->arr[mid]==temp->key){
            printf("Key %d found!\n",temp->key);
            temp->status=mid;break;
        }
        else if(temp->arr[mid]<temp->key){
            printf("Key %d lesser than the mid value %d\n",temp->key,temp->arr[mid]);
            temp->start=mid+1;
        }
        else{
            printf("Key %d greater than the mid value %d\n",temp->key,temp->arr[mid]);
            temp->end=mid-1;
        }
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
    for(i=start;i<end-1;i++){
        for(j=start;j<end-(i-start)-1;j++){
        int choice=(ch==0)?(a[j]<a[j+1]):(a[j]>a[j+1]);
            if(choice==1){
            swap(&a[j],&a[j+1]);
            }
        }
    }
}

void binarySearch(int arr[],int n,int key1,int key2){
    clock_t t1,t2;
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

    t1=clock();
                
    pthread_create(&pth[0],NULL,bs,&temp[0]);
    pthread_create(&pth[1],NULL,bs,&temp[1]);

    pthread_join(pth[0],NULL);
    pthread_join(pth[1],NULL);

    t2=clock();

    printf("Binary Search:%lf\n",(t2-t1)/(double)CLOCKS_PER_SEC);

    if(temp[0].status!=-1)
        printf("Key1 found at first half\n");
    else
        printf("Key1 not found at first half\n");
    if(temp[1].status!=-1)
        printf("Key2 found at second half\n");
    else
        printf("Key2 not found at second half\n");
     //fib
}
void Fibonacci(int arr[],int n,int key1,int key2){
    clock_t t1,t2;
    pthread_t pth[2];

    struct node *temp=(struct node* )malloc(2*sizeof(struct node));
    temp[0].arr=arr;
    temp[0].start=0;
    temp[0].end=n/2;
    temp[0].key=key1;

    temp[1].arr=arr;
    temp[1].start=n/2;
    temp[1].end=n;
    temp[1].key=key2;

    t1=clock();

    pthread_create(&pth[0],NULL,fib,&temp[0]);
    pthread_create(&pth[1],NULL,fib,&temp[1]);

    pthread_join(pth[0],NULL);
    pthread_join(pth[1],NULL);

    t2=clock();

    printf("Fibonacci search:%lf\n",(t2-t1)/(double)CLOCKS_PER_SEC);

    if(temp[0].status!=-1)
        printf("Key1 found at first half\n");
    else
        printf("Key1 not found at first half\n");
     
    if(temp[1].status!=-1)
        printf("Key2 found at second half\n");
    else
        printf("Key2 not found at second half\n");

}

int main(){
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
    // int n,i;
    // printf("Enter size of array: ");
    // int arr[n];
    // scanf("%d",&n);
    // printf("Enter %d numbers:\n",n);
    // for(i=0;i<n;i++)
    //     scanf("%d",&arr[i]);
    int key1,key2;
    
    printf("Enter key1 and key2 to be searched:\n");
    
    scanf("%d %d",&key1,&key2);
    bubblesort(arr,1,0,n/2);
    bubblesort(arr,1,n/2,n);
    printf("Elements after Sorting:\n");
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);
    printf("\n");
    
    binarySearch(arr,n,key1,key2);
    Fibonacci(arr,n,key1,key2);
      
    return 0;
}
