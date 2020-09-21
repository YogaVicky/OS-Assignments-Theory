#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
	int n,i,x;
	int j,k,temp;
	printf("Enter n\n");
	scanf("%d",&n);
	int a[n];
	printf("Enter %d numbers\n",n);
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Number to search\n");
	scanf("%d",&x);
	printf("\n");
	pid_t pid;
	int beg,end,mid,m;
	pid = vfork();
	if(pid == 0){
		for(j=0;j<n/2;j++){
			for(k=0;k<n/2-j-1;k++){
				if(a[k] > a[k+1]){
					temp = a[k];
					a[k] = a[k+1];
					a[k+1] = temp;
				}
			}
		}
		beg = 0;
		end = n/2-1;
		while(beg <= end){
			mid = (beg+end)/2;
			if(a[mid] == x){
                m = mid;
                while((a[m] == x) && (m >= 0)){
                    printf("%d found in index: %d\n",x,m);
                    m--;
                }
                m = mid+1;
                while((a[m] == x) && (m <= n/2-1)){
                    printf("%d found in index: %d\n",x,m);
                    m++;
                }
				break;
			}
			else if(a[mid] < x)
				beg = mid+1;
			else
				end = mid-1;
		}
		exit(0);
	}
	else if(pid > 0){
		wait(NULL);
		for(j=n/2;j<n;j++){
			for(k=n/2;k<n+n/2-j-1;k++){
				if(a[k] > a[k+1]){
					temp = a[k];
					a[k] = a[k+1];
					a[k+1] = temp;
				}
			}
		}
		beg = n/2;
		end = n-1;
		while(beg <= end){
			mid = (beg+end)/2;
			if(a[mid] == x){
				m = mid;
                while((a[m] == x) && (m >= n/2)){
                    printf("%d found in index: %d\n",x,m);
                    m--;
                }
                m = mid+1;
                while((a[m] == x) && (m <= n-1)){
                    printf("%d found in index: %d\n",x,m);
                    m++;
                }
				break;
			}
			else if(a[mid] < x)
				beg = mid+1;
			else
				end = mid-1;
		}
	}
	return 0;
}
