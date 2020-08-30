#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 1024

int negate(int a) {    
    return(-1*a);
}

int retain(int a) {
    return(a);
}

void SortArray(int arr[], int n,int (*mode)(int)) {  
	int b = 1; 
    while (b) { 
        b = 0; 
        for (size_t i=0; i<n-1; i++) { 
    	      if (mode(arr[i]) > mode(arr[i + 1])) { 
                int temp = arr[i]; 
                arr[i] = arr[i + 1]; 
                arr[i + 1] = temp; 
                b = 1; 
            } 
        } 
    } 
}

int main(int argc, char *argv[]) {
	if (argv[1] == "--help") {
		printf("\nUsage: ./sortWithC size sortmode a[0], a[1] ... a[size-1]\n");
		exit(EXIT_FAILURE);
	}
	int size=atoi(argv[1]), sort_mode=atoi(argv[2]), a[size];
    if(size <= 0) {    
        printf("Error : the array size should be > 0 \n");
        return(EXIT_FAILURE);
    }
    if(argc!=size+3) {
		printf("Error : The array size dosen't match the given input array size (Array size mismatch)\n");
		return(EXIT_FAILURE);
	}    
    if(sort_mode && sort_mode!=1) {
        printf("The sort mode should be 1 for ascending and 0 for descending \n");
        return(EXIT_FAILURE);
    }
    int (*mode)(int) = sort_mode?(retain):(negate);
    for(int i=3; i<size+3;i++) {
        a[i-3] = atoi(argv[i]);
		
    }    
    SortArray(a,size,mode);
    for(int i=0; i<size;i++) {
        printf("%d ",a[i]);
    }
	printf("\n");
	exit(EXIT_SUCCESS);
}