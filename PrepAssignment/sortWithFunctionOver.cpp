#include<bits/stdc++.h>
using namespace std;

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

void SortArray(float arr[], int n,int (*mode)(int)) {  
	int b = 1; 
    while (b) { 
        b = 0; 
        for (size_t i=0; i<n-1; i++) { 
    	      if (mode(arr[i]) > mode(arr[i + 1])) { 
                float temp = arr[i]; 
                arr[i] = arr[i + 1]; 
                arr[i + 1] = temp; 
                b = 1; 
            } 
        } 
    } 
}

void SortArray(char arr[], int n,int (*mode)(int)) {  
	int b = 1; 
    while (b) { 
        b = 0; 
        for (size_t i=0; i<n-1; i++) { 
    	      if (mode(arr[i]) > mode(arr[i + 1])) { 
                char temp = arr[i]; 
                arr[i] = arr[i + 1]; 
                arr[i + 1] = temp; 
                b = 1; 
            } 
        } 
    } 
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		cout << "Usage: ./sortWithFunctionOver size sortmode [0 or 1 or 2]  a[0], a[1] ... a[size-1]" << endl;
		exit(EXIT_FAILURE);
	}
	int size=atoi(argv[1]), sort_mode=atoi(argv[2]);
    if(size <= 0) {    
        cout << "Error : the array size should be > 0 " << endl;
		cout << "Usage: ./sortWithFunctionOver size sortmode [0 or 1 or 2]  a[0], a[1] ... a[size-1]" << endl;
        return(EXIT_FAILURE);
    }
    if(argc!=size+4) {
		cout << "Error : The array size dosen't match the given input array size " << endl;
		cout << "Usage: ./sortWithFunctionOver size sortmode [0 or 1 or 2]  a[0], a[1] ... a[size-1]" << endl;
		return(EXIT_FAILURE);
	}    
    if(sort_mode && sort_mode!=1) {
        cout << "The sort mode should be 1 for ascending and 0 for descending " << endl;
		cout << "Usage: ./sortWithFunctionOver size sortmode [0 or 1 or 2]  a[0], a[1] ... a[size-1]" << endl;
        return(EXIT_FAILURE);
    }
    int (*mode)(int) = sort_mode?(::retain):(::negate);
	int type = atoi(argv[3]);
	switch (type) {
		case 0 : {
			int a[size];
			for(int i=4; i<size+4;i++) {
        		a[i-4] = atoi(argv[i]);
    		}    
    		SortArray(a,size,mode);
    		for(int i=0; i<size;i++) {
	        	cout << a[i] << " ";
	    	}
			cout << endl;
		}
		break;
		case 1 : {
			float a[size];
			for(int i=4; i<size+4;i++) {
        		a[i-4] = atof(argv[i]);
    		}    
    		SortArray(a,size,mode);
    		for(int i=0; i<size;i++) {
	        	cout << setprecision(5) << a[i] << " ";
	    	}
			cout << endl;
		}
		break;
		case 2 : {
			char a[size];
			for(int i=4; i<size+4;i++) {
        		a[i-4] = (*argv[i]);
    		}    
    		SortArray(a,size,mode);
    		for(int i=0; i<size;i++) {
	        	cout << a[i];
	    	}
			cout << endl;
		}
		break;
		default : cout << "Enter something in the range [0,2] !";
	}
    
	return(EXIT_SUCCESS);
}