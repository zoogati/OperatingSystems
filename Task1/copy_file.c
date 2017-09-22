/* 
    Copy File - Written by Socratis Katehis
	CSC 332: Operating Systems
	September 8th, 2017
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

	//Initialize buffer with file size.
	int file_size = lseek(fd, 0, SEEK_END);
	if (file_size < 0) {
		printf("invalid file size.");
		return 1;
	}
	char buffer[file_size];
	
	//Go back to the beginning of the file.
	lseek(fd, 0, SEEK_SET);
	
	//Read data to buffer and write buffer to file.
	int read_bytes = read(fd, buffer, file_size);
	write(dest, buffer, read_bytes);
	
	//Check error in closing files
	int returnval1 = close(fd);
	int returnval2 = close(dest);
	if ( returnval1 < 0 || returnval2 < 0 )
		printf("Error while closing files");
	
	return 0;
}