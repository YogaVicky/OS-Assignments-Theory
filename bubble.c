#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void bubbleSort(int array[], int size)
{
	for (int step = 0; step < size - 1; ++step)
	{
		for (int i = 0; i < size - step - 1; ++i)
		{
			if (array[i] > array[i + 1])
			{
				int temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}
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

	// Initialize Pipe
	int f[2]; // Sending from child to parent
	if (pipe(f) == -1)
	{
		perror("Pipe Error: \n");
		return 1;
	}

	// Fork the processes
	pid_t pid;
	pid = fork();

	if (pid > 0)
	{
		printf("starting of parent\n");

		// Sorting odd indexes
		int oddIndexArr[n / 2];
		for (int i = 0; i < n / 2; i++)
			oddIndexArr[i] = arr[2 * i + 1];

		bubbleSort(oddIndexArr, n / 2);

		// No need to use write end of pipe, so close it
		close(f[1]);

		// Wait for child's data
		wait(NULL);

		int evenIndexArr[n / 2];
		read(f[0], evenIndexArr, sizeof(evenIndexArr));

		// Combining the two arrays
		int com[n];
		for (int i = 0; i < n; i++)
		{
			if (i % 2 != 0)
				com[i] = oddIndexArr[(i - 1) / 2];
			else
				com[i] = evenIndexArr[i / 2];
		}

		// Printing the result
		printf("result\n");
		for (int i = 0; i < n; i++)
			printf("%d ", com[i]);
		printf("\n");

		printf("end of parent\n");
	}
	else if (pid == 0)
	{
		printf("start of child\n");

		// Sorting even indexes
		int evenIndexArr[n / 2];
		for (int i = 0; i < n / 2; i++)
			evenIndexArr[i] = arr[2 * i];

		bubbleSort(evenIndexArr, n / 2);

		// No need to use read end of pipe, so close it
		close(f[0]);

		write(f[1], evenIndexArr, sizeof(evenIndexArr));

		// sleep(5);
		printf("end of child\n");
	}
	else
		perror("Fork Error: \n");

	return 0;
}