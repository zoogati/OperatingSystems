/* 
    Banking Semaphores - Written by Socratis Katehis
	CSC 332: Operating Systems
	November 12th, 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include<sys/shm.h>
#include "sem.h"

#define CHILD      			0  			/* Return value of child proc from fork call */
#define TRUE       			0  
#define FALSE      			1

FILE *fp1, *fp2, *fp3, *fp4;			/* File Pointers */

//Added default initializations

int* buffer;
int mutex, shmid;
int dad_prcs = 0, child1_prcs = 0, child2_prcs = 0;
int wait_dad = 0, wait_child1 = 0, wait_child2 =0;

main()
{
	int pid;						// Process ID after fork call
	int i;							// Loop index
	int N;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	int bal1, bal2;					// Balance read by processes
	int flag, flag1;				// End of loop variables
	
	//Initialize the file balance to be $100
	fp1 = fopen("balance","w");
	bal1 = 100;
	fprintf(fp1, "%d\n", bal1);
	fclose(fp1);
	
	//Initialize the number of attempts to be 20
	fp4 = fopen("attempt", "w");
	N_Att = 20;
	fprintf(fp4, "%d\n", N_Att);
	fclose(fp4);
	
	// ** ADDED CODE ** //
	
	// Before processes, create shared memory.
	if ((shmid = shmget(1234, 6, IPC_CREAT | 0666)) < 0) {
		perror("shget");
		return -1;
	}
	
	// Allocate the memory.
	if((buffer=(int*)shmat(shmid, (char*)0,0)) == (int*)-1) {
		perror("shmat");
		exit(1);
	}
	
	// Create the semaphore.
	if ((mutex=semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT)) ==  -1) {
		perror("semget");
		exit(1);
	}
	
	// Buffer will hold wait times and PIDs.
	buffer[0] = wait_dad, buffer[1] = wait_child1, buffer[2] = wait_child2;
	buffer[3] = dad_prcs, buffer[4] = child1_prcs, buffer[5] = child2_prcs;

	
	
	//Create child processes that will do the updates
		if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	
	if (pid == CHILD){
	//First Child Process. Dear old dad tries to do some updates.
		dad_prcs = getpid();
		N=5;
		for(i=1;i<=N; i++)
		{
			// ** ADDED CODE ** //
			buffer[3] = dad_prcs;
			P(mutex);
			if (buffer[4] != 0)
				wait_child1 += 1;
			if (buffer[5] != 0)
				wait_child2 += 1;
			
			buffer[1] = wait_child1, buffer[2] = wait_child2;
			
			printf("Dear old dad is trying to do update.\n");
			fp1 = fopen("balance", "r+");
			fscanf(fp1, "%d", &bal2);
			printf("Dear old dad reads balance = %d \n", bal2);
			
			//Dad has to think (0-14 sec) if his son is really worth it
			sleep(rand()%15);
			fseek(fp1,0L,0);
			bal2 += 60;
			printf("Dear old dad writes new balance = %d \n", bal2);
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);

			printf("Dear old dad is done doing update. \n");
			sleep(rand()%5);	/* Go have coffee for 0-4 sec. */
			
			// ** ADDED CODE ** //
			buffer[3] = 0;
			V(mutex);
		}
	}
	
	else
	{
		//Parent Process. Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}
		if (pid == CHILD)
		{
			child1_prcs = getpid();
			printf("First Son's Pid: %d\n",getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while(flag == FALSE) 
			{
				// ** ADDED CODE ** //
				buffer[4] = child1_prcs;
				P(mutex);
				if (buffer[3] != 0)
					wait_dad += 1;
				if (buffer[5] != 0)
					wait_child2 += 1;
				
				buffer[0] = wait_dad; buffer[2] = wait_child2;
				
				
				fp3 = fopen("attempt" , "r+");
				fscanf(fp3, "%d", &N_Att);
				if(N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}
				else
				{
					printf("Poor SON_1 wants to withdraw money.\n");
					fp2 = fopen("balance", "r+");
					fscanf(fp2,"%d", &bal2);
					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
					if (bal2 == 0)
					{
						fclose(fp2);
						fclose(fp3);
					}
					else
					{
						sleep(rand()%5);
						fseek(fp2,0L, 0);
						bal2 -=20;
						printf("Poor SON_1 write new balance: %d \n", bal2);
						fprintf(fp2,"%d\n", bal2);
						fclose(fp2);
						printf("poor SON_1 done doing update.\n");
						fseek(fp3,0L, 0);
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
					}
				}
			}
			buffer[4] = 0;
			V(mutex);
		}
		else
		{
		//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1) 
			{
				//fork failed!
				perror("fork");
				exit(1);
			}
			if (pid == CHILD)
			{
				child2_prcs = getpid();
				printf("Second Son's Pid: %d\n",getpid());
				//Third child process. Second poor son tries to do updates.
				flag1 = FALSE;
				while(flag1 == FALSE) 
				{
					// ** ADDED CODE **//
					buffer[5] = child2_prcs;
					P(mutex);
					if (buffer[3] != 0)
						wait_dad += 1;
					if (buffer[4] != 0)
						wait_child1 += 1;
					
					buffer[0] = wait_dad, buffer[1] = wait_child1;
					fp3 = fopen("attempt" , "r+");
					fscanf(fp3, "%d", &N_Att);
					if(N_Att == 0)
					{
						fclose(fp3);
						flag1 = TRUE;
					}
					else
					{
						printf("Poor SON_2 wants to withdraw money.\n");
						fp2 = fopen("balance", "r+");
						fscanf(fp2,"%d", &bal2);
						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
						if (bal2 == 0)
						{
							fclose(fp2);
							fclose(fp3);
						}
						else
						{
							sleep(rand()%5);
							fseek(fp2,0L, 0);
							bal2 -=20;
							printf("Poor SON_2 write new balance: %d \n", bal2);
							fprintf(fp2,"%d\n", bal2);
							fclose(fp2);

							printf("poor SON_2 done doing update.\n");
							fseek(fp3,0L, 0);
							N_Att -=1;
							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
						}
					}
				}
				buffer[5] = 0;
				V(mutex);
			}
			else
			{
				//Now parent process waits for the child processes to finish
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			}
			exit(0);
		}
		exit(0);
	}
	exit(0);
}




