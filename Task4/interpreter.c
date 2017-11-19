/* 
    Command Line Interpreter - Written by Socratis Katehis
	CSC 332: Operating Systems
	October 23th, 2017
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
	
	int child_status = 0;
	//Allocated memory for commands (execvp)
	char memory[30];
	char input_str[20];
	char *token;
	char *arg_arr[30];

	//Wait for input and check it quit is typed.
	scanf("%[^\n]s", input_str);
	int x = strcmp("quit", input_str);
	int args = 0;
	
			
	while (x != 0)
	{
		// Tokenize input to split commands and arguments
		token = strtok(input_str, " ");
		
		while (token != NULL) 
		{
			arg_arr[args++] = token;
			token = strtok(NULL, " ");
		}
		
		// Create Child
		child_status = fork();
		
		if (child_status < 0)
		{
			perror("fork");
		}
    			
		else if (child_status == 0) 
		{
			//Execute the command.
			if (execvp(*arg_arr, arg_arr) < 0) 
			{ 
				perror("execvp");
				return 1;
         	}
     	}	
    			 
    	else
		{                         
        	wait(&child_status);
			execvp(argv[0], argv);	
   		}
		
	}		
	
	return 0;	
}	
