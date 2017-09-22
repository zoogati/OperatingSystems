/* 
    Process Adding - Written by Socratis Katehis
	CSC 332: Operating Systems
	September 21st, 2017
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() 
{
	//parent P 
	int a = 10, b = 25, fq = 0, fr = 0;
 
	fq = fork(); // fork a child - call it Process Q
	
	if (fq == 0) // Child successfully forked 
	{
		a = a + b; 
		printf("a: %d, b: %d, Process Id: %d\n", a, b, getpid()); 
	
		fr = fork(); // fork another child - call it Process R 
		if(fr != 0) 
		{	
			b = b + 20; 
			printf("a: %d, b: %d, Process Id: %d\n", a, b, getpid());	 
		}

		else
		{
			a = (a * b) + 30; 
			printf("a: %d, b: %d, Process Id: %d\n", a, b, getpid()); 
		}
	}

	else 
	{	
		b = a + b - 5;
		printf("a: %d, b: %d, Process Id: %d\n", a, b, getpid()); 
	}
	
	return 0;
	
}