/* 
    Children Processes - Written by Socratis Katehis
	CSC 332: Operating Systems
	September 21st, 2017
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{	
	// Variables for pid values
	int parent_pid = 0, child1_pid = 0, child2_pid = 0, wait_pid = 0;
	
	// Variables for statuses
	int child1_status = 0, child2_status = 0, wait_status = 0;
	
	// Obtain pid of parent process.
	parent_pid = getpid();
	
	// Create first child process.
	child1_status = fork();
	
	// Check for error.
	if (child1_status < 0)
		perror("fork");
		
	if (child1_status == 0)
	{	
		child1_pid = getpid();
		printf("I am child one, my pid is: %d\n",child1_pid);
		return 1;
	}
	
	// Wait for child process.
	else {
		wait_pid = waitpid(child1_pid, &wait_status, 0);
		if (wait_pid < 0)
			perror("waitpid");
	}
	// Create second child process.
	child2_status = fork();

	// Check for error.
	if (child2_status < 0)
		perror("fork");
	
	if (child2_status == 0)
	{
		child2_pid = getpid();
		printf("I am child two, my pid is: %d\n", child2_pid);
		return 1;
	}
	
	// Wait for child process.
	else {
		wait_pid = waitpid(child2_pid, &wait_status, 0);
		if (wait_pid < 0)
			perror("waitpid");
	}
	
	return 0;
}