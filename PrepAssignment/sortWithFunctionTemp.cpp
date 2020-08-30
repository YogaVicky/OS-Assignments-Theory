#include<bits/stdc++.h>
using namespace std;

int neg(int a) {    
    return(-1*a);
}

int ret(int a) {
    return(a);
}

template <class T>
void sortArray(T arr[], int n, int (*mode)(int)) {
	int b = 1; 
    while (b) { 
        b = 0; 
        for (size_t i=0; i<n-1; i++) { 
    	      if (mode(arr[i]) > mode(arr[i + 1])) { 
                T temp = arr[i]; 
                arr[i] = arr[i + 1]; 
                arr[i + 1] = temp; 
                b = 1; 
            } 
        } 
    } 
}

template <class T> 
void printArray(T a[], int n) { 
	for (size_t i = 0; i < n; ++i)  
        cout << a[i] << " ";     
    cout << endl; 
} 

int main(int argc, char* argv[]) {
	if (argc == 1) {
		cout << "\nUsage: ./sortWithFunctionTemp size sortmode [0 or 1 or 2]  a[0], a[1] ... a[size-1]\n" ;
		exit(EXIT_FAILURE);
	}
	int size=atoi(argv[1]), sort_mode=atoi(argv[2]), a[size];
    if(size <= 0) {
        cout << "Error : the size of the array should be > 0 \n";
		cout << "\nUsage: ./sortWithFunctionTemp size sortmode [0 or 1 or 2]  a[0], a[1] ... a[size-1]\n" ;
        return(EXIT_FAILURE);
    }
    if(argc != size+4) {
		cout << "Error : The size of the array dosen't match the given input array size \n";
		cout << "\nUsage: ./sortWithFunctionTemp size sortmode [0 or 1 or 2]  a[0], a[1] ... a[size-1]\n" ;
		return(EXIT_FAILURE);
	}    
    if(sort_mode and sort_mode!=1) {
        cout << "The sort mode should be 1 for ascending and 0 for descending \n";
		cout << "\nUsage: ./sortWithFunctionTemp size sortmode [0 or 1 or 2]  a[0], a[1] ... a[size-1]\n" ;
        return(EXIT_FAILURE);
    }
    int (*mode)(int) = sort_mode?(::ret):(::neg);
    int type = atoi(argv[3]);
	switch (type) {
		case 0 : {
			int a[size];
			for(int i=4; i<size+4;i++) a[i-4] = atoi(argv[i]);
			sortArray(a,size,mode);
			printArray(a,size);
		}
		break;
		case 1 : {
			float a[size];
			for(int i=4; i<size+4;i++) a[i-4] = atof(argv[i]);
			sortArray(a,size,mode);
			printArray(a,size);
		}
		break;
		case 2 : {
			char a[size];
			for(int i=4; i<size+4;i++) a[i-4] = (*argv[i]);
			sortArray(a,size,mode);
			printArray(a,size);
		}
		break;
		default : cout << "Enter something in the range [0,2] !";
	}
	return(EXIT_SUCCESS);
}