/* 
    Open File - Written by Socratis Katehis
	CSC 332: Operating Systems
	September 3rd, 2017
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	int fd;
	if (2 != argc) {
		printf("\nUsage: \n");
		return 1;
	}
	errno = 0;
	/*  RDONLY - Open only to read.
		WRONLY - Open only to write.
		RDWR - Open to both read and write.
		CREAT - Create file if non-existent, OR this.
	*/
	fd = open(argv[1], O_RDWR | O_CREAT);
	
	if(fd == -1) {
		printf("\nopen() failed with error [%s]\n", strerror(errno));
		return 1;
	}
	else printf("\nopen() successful\n");
	// Open succeeded in rw mode.
	return 0;
}