/* 
    Parent Process - Written by Socratis Katehis
	CSC 332: Operating Systems
	October 9th, 2017
*/
#include <stdio.h>
#include <unistd.h>

int main() {
	
	int child1 = 0, child2 = 0;
	
	child1 = fork();
	wait();
	
	if (child1 < 0) 
		perror("fork");
	
	else if (child1 == 0) {
		char *args[] = {NULL};
		execv("./Prcs_P1", args);
		perror("execv");
	}
	
	child2 = fork();
	wait();
	
	if (child2 < 0)
		perror("fork");
	
	else if (child2 == 0) {
		char *args[] = {NULL};
		execv("./Prcs_P2", args);
		perror("execv");
	}
	
	return 0;
}