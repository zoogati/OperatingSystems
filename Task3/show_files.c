/* 
    Show Files - Written by Socratis Katehis
	CSC 332: Operating Systems
	October 9th, 2017
*/
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int child_status = 0;
	
	child_status = fork();
	wait();
	
	if (child_status < 0) {
		perror("fork");
	}
	
	else if (child_status == 0) {
		printf("Child PID is: %d\n", getpid());
		char *args[] = {"-a","-l", NULL};
		execvp("ls",args);
		perror("execvp");
	}
	
	return 0;
}