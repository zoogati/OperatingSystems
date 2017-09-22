/* 
    Display Content - Written by Socratis Katehis
	CSC 332: Operating Systems
	September 3rd, 2017
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

//This function checks for file access errors.
int check_access(char* file)
{
	access(file, F_OK);
	if (errno == ENOENT) {
		printf("%s doesn't exist\n", file);
		return -1;
		}
	else if (errno == EACCES) {
		printf("%s is not accessible\n", file);
		return -1;
		}
		
	int returnval = access(file, R_OK);
	if (returnval < 0) {
		perror("access");
		return returnval;
	}
	
	returnval = access(file, W_OK);
	if (returnval < 0) {
		perror("access");
		return returnval;
	}
	
	return 0;
}

void read_file(char* file)
{
	// Open file and check for error.
	int fd = open(file, O_RDONLY);
	if (fd < 0) {
		printf("\nopen() failed with error [%s]\n", strerror(errno));
	}
	
	//Initialize buffer with file size.
	int file_size = lseek(fd, 0, SEEK_END);
	if (file_size < 0) {
		printf("invalid file size.");
		return;
	}
	char buffer[file_size];
	
	// Go back to the beginning of the file.
	lseek(fd, 0, SEEK_SET);
	
	int read_bytes = read(fd, buffer, file_size-1);
	write(1, buffer, read_bytes);
	
	return;
}

int main(int argc, char* argv[]) 
{
	char* filepath = argv[1];
	
	int check = check_access(filepath);
	if(check > -1)
		read_file(filepath);
	else printf("Operation Failed!");
	
	return 0;
};
