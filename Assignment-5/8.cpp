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
           
           //sort the halves first

            printf("Elements after Sorting:\n");

            for(int i=0;i<n;i++)
                printf("%d ",arr[i]);
            printf("\n");

            process3(arr,n,key1,key2);
        
   
    }
    return 0;
}
