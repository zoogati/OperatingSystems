/* 
    Process 2: Manipulate Source - Written by Socratis Katehis
	CSC 332: Operating Systems
	October 9th, 2017
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main()
{
	int fd = 0, dest1 = 0, dest2 = 0;
	
	fd = open("source.txt", O_RDONLY);
	if (fd < 0) {
		printf("Error opening source file");
		return -1;
	}
	
	dest1 = open("destination1.txt", O_WRONLY);
	if (dest1 < 0) {
		printf("Error opening destination1 file");
		return -1;
	}
	
	dest2 = open("destination2.txt", O_WRONLY);
	if (dest2 < 0) {
		printf("Error opening destination2 file");
		return -1;
	}
	
	int buffer_size1 = 100, buffer_size2 = 50;
	char buffer1[buffer_size1], buffer2[buffer_size2];
	
	int seek = 0;
	
	while ((seek = read(fd, buffer1, buffer_size1)) != 0) {
		
		for (int i = 0; i < buffer_size1; i++) {
			if (buffer1[i] == '1')
				buffer1[i] = 'A';
			}
		seek = write(dest1, buffer1, seek);

		seek = read(fd, buffer2, buffer_size2);
		if (seek == 0)
			break;
		for (int i = 0; i < buffer_size2; i++) {
			if (buffer2[i] == '2')
				buffer2[i] = 'B';
		}
		seek = write(dest2, buffer2, seek);
	}
	
	int return1 = close(fd);
	if (return1 < 0) {
		printf("Error closing source file");
		return -2;
	}
	
	int return2 = close(dest1);
	if (return2 < 0) {
		printf("Error closing destination1 file");
		return -2;
	}
	
	int return3 = close(dest2);
	if (return3 < 0) {
		printf("Error closing destination2 file");
		return -2;
	}
	
	return 0;
}