#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 2048

int main(int argc, char* argv[])
{
	int srcCopyWithC, destCopyWithC, temp, temp2;
	char *buff[MAX_BUFFER_SIZE];
	if (argc == 1) {
		printf("Usage: ./copyWithC source_file destination_file\n");
		return(EXIT_FAILURE);
	}
	srcCopyWithC = open(argv[1], O_RDONLY);
	if (srcCopyWithC == -1) {
		printf("Error opening file %s errno = %d\n", argv[1], errno);
		printf("Usage: ./copyWithC source_file destination_file\n");
		return(EXIT_FAILURE);
	}
	destCopyWithC = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (destCopyWithC == -1) {
		printf("Error opening file %s errno = %d\n", argv[2], errno);
		printf("Usage: ./copyWithC source_file destination_file\n");
		return(EXIT_FAILURE);
	}
	while ((temp = read(srcCopyWithC, buff, MAX_BUFFER_SIZE)) > 0) {
		if (write(destCopyWithC, buff, temp) != temp)
			printf("\nError in writing data to %s\n", argv[2]);
		// printf("Usage: ./copywithc source_file destination_file\n");
		return(EXIT_FAILURE);
	}
	if (temp == -1)
		printf("Error in reading data from %s\n", argv[1]);
	if (close(srcCopyWithC) == -1)
		printf("Error in closing file %s\n", argv[1]);
	if (close(destCopyWithC) == -1)
		printf("Error in closing file %s\n", argv[2]);
	return(EXIT_SUCCESS);
}

#pragma GCC diagnostic pop