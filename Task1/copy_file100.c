/* 
    Copy File while replacing every 100 bytes - Written by Socratis Katehis
	CSC 332: Operating Systems
	September 9th, 2017
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	int fd, dest;
	//Check error in call.
	if (3 != argc) {
		printf("\nUsage: requires source and destination argument\n");
		return 1;
	}
	errno = 0;
	
	//Check error in opening files.
	fd = open(argv[1], O_RDONLY);
	dest = open(argv[2], O_WRONLY | O_CREAT);
	if (fd < 0 | dest < 0) {
		printf("\nopen() failed with error: [%s]\n", strerror(errno));
	}
	
	int buffer_size = 100;
	char buffer[buffer_size];
	int seek;
	
	// Read 100 bytes and write with manipulations
	while((seek = read(fd, buffer, buffer_size)) != 0) {
		for (int i = 0; i < buffer_size; i++) {
			if (buffer[i] == '1')
				buffer[i] = 'A';
		}
		seek = write(dest, buffer, seek);
		seek = write(dest, "XYZ", 3);
	}
	
	int returnval1 = close(fd);
	int returnval2 = close(dest);
	if (returnval1 < 0 | returnval2 < 0)
		printf("Error while closing flies%n");
	return 0;
}