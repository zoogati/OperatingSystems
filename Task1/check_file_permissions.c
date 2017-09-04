/* 
    Check File Permissions - Written by Socratis Katehis
	CSC 332: Operating Systems
	September 3rd, 2017
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char* argv[]) 
{
	char* filepath = argv[1];
	int returnval;
	
	//Check if file exists
	returnval = access(filepath, F_OK);
	if (returnval == 0) {
		printf("\n %s exists\n", filepath);
	}
	else {
		if (errno == ENOENT) {
			printf("%s doesn't exist\n", filepath);
		}
		else if (errno == EACCES) {
			printf("%s is not accessible\n", filepath);
		}
		return 0;
	}
	
	//TODO: Check read access
	returnval = access(filepath, R_OK);
	if (returnval == 0) {
		printf("%s has read access\n", filepath);
	}
	else if (returnval == -1) {
		printf("%s doesn't have read access, error %d", filepath, errno);
		perror("access");
	}
	
	//TODO: Check write access
	
	returnval = access(filepath, W_OK);
	if (returnval == 0) {
		printf("%s has write access\n", filepath);
	}
	else if (returnval == -1) {
		printf("%s doesn't have write access, error %d", filepath, errno);
		perror("access");
	}
	
	return 0;
}