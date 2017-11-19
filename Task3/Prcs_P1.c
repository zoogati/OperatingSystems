/* 
    Process 1: Create two Files - Written by Socratis Katehis
	CSC 332: Operating Systems
	October 9th, 2017
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd1 = 0, fd2 = 0;
	
	// Create the first file.
	fd1 = creat("destination1.txt", S_IRWXO | S_IRWXU);
	if (fd1 < 0)
		perror("creat");
	
	// Create the second file.
	fd2 = creat("destination2.txt", S_IRWXO | S_IRWXU);
	if (fd2 < 0)
		perror("creat");
	
	return 0;
}