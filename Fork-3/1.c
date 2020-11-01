#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
void orphan()
{
pid_t pid;
pid=fork();

if(pid==0)
{
    sleep(4);
    printf("\nOrphan Child Process Process!!!\n");
    sleep(6);
    _exit(0);
    

}
else
{
    printf("Parent Process has been executed!!!\n");    
}
}
void zombie()
{
pid_t pid;
pid=fork();

if(pid==0)
{
    printf("Zombie Process!!!\n");
    _exit(0);
}
else
{
    sleep(10);
    printf("Parent Process slept for 10 seconds!!!\n");
}
}

int main()
{
printf("Zombie Process\n");
zombie();
printf("\nOrphan Process\n");
orphan();           
return 0;
}
