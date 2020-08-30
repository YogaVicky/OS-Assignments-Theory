#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 2048

int main(int argc, char* argv[])
{
	if (argc == 1) {
		printf("Usage: ./rmWithC file_name\n");
		return(EXIT_FAILURE);
	}
	int srcRmWithC;
	srcRmWithC = open(argv[1], O_RDONLY);
	if (srcRmWithC == -1) {
		printf("Error opening file %s errno = %d\n", argv[1], errno);
		exit(EXIT_FAILURE);
	}
	if(remove(argv[1])) {
		printf("File Removed Succesfully ! \n");
		return(EXIT_SUCCESS);
	}
	else {
		printf("File Not Removed Succesfully !! \n");
		return(EXIT_SUCCESS);
	}
}