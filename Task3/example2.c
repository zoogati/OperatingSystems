/* 
    Example 1 - Written by Socratis Katehis
	CSC 332: Operating Systems
	October 7th, 2017
*/

#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	execvp ("echo", &argv[0]);
	printf ("EXECVP Failed\n");
	/* The above line will be printed only on error and not otherwise */
}