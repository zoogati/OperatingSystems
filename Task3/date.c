/* 
    Date - Written by Socratis Katehis
	CSC 332: Operating Systems
	October 9th, 2017
*/
#include <stdio.h>
#include <unistd.h>

int main() 
{
	int child_status = 0;
	
	// Fork to create child process and make parent wait
	child_status = fork();
	wait();
	
	// Check for error in child process
	if (child_status < 0) {
		perror("fork");
	}
	
	// Print child PID and execute date
	else if (child_status == 0) {
		printf("Child PID is: %d\n", getpid());
		execl("/bin/date", NULL, NULL);
		perror("execl");
	}
	
	return 0;
}