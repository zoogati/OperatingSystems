/* 
    Cigarette-Smoker Problem - Written by Socratis Katehis
	CSC 332: Operating Systems
	November 28th, 2017
*/

#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include "sem.h"

int main() {
	
	// Five semaphores to be used
	int lock;			
	int tobacco;
	int paper;
	int match;
	int agent;
	
	// Other integers that will be used 
	int rand_number;
	int child;

	// Create semaphores for each.
	if((match=semget(IPC_PRIVATE,1,0666 | IPC_CREAT)) == -1)
	{
	  perror("semget");
	  exit(-1);
	}
	
	if((lock=semget(IPC_PRIVATE,1,0666 | IPC_CREAT)) == -1)
	{
	  perror("semget");
	  exit(-1);
	}

	if((paper=semget(IPC_PRIVATE,1,0666 | IPC_CREAT)) == -1)
	{
	  perror("semget");
	  exit(-1);
	}
	
	if((tobacco=semget(IPC_PRIVATE,1,0666 | IPC_CREAT)) == -1)
	{
	  perror("semget");
	  exit(-1);
	}

	if((agent=semget(IPC_PRIVATE,1,0666 | IPC_CREAT)) == -1)
	{
	  perror("semget");
	  exit(-1);
	}

	sem_create(match,0);
	sem_create(lock,1);
	sem_create(tobacco,0);
	sem_create(paper,0);
	sem_create(agent,0);

	//Create child process for smoker with paper
	if ((child = fork()) == -1) 
	{
		perror("fork");
		exit(-1);
	}
	
	else if (child == 0) {
		while (1) {
			P(paper);
			P(lock);
			printf("Smoker with paper picks up tobacco and match and starts smoking\n");
			sleep(1);
			V(agent);
			V(lock);
		}			
	}
	
	// Create child process for smoker with tobacco
	if ((child = fork()) == -1) 
	{
		perror("fork");
		exit(-1);
	}
	
	else if (child == 0) {
		while (1) {
			P(tobacco);
			P(lock);
			printf("Smoker with tobacco picks up match and paper and starts smoking\n");
			sleep(1);
			V(agent);
			V(lock);
		}
	}
		
	// Create child process for smoker with match
	if ((child = fork()) == -1) 
	{
		perror("fork");
		exit(-1);
	}
	
	else if (child == 0) {
		while (1) {
			P(match);
			P(lock);
			printf("Smoker with match picks up paper and tobacco and starts smoking\n");
			sleep(1);
			V(agent);
			V(lock);
		}			
	}
	
	while(1) {
			
		P(lock);
		rand_number = rand() % 3;
			
		// Pick a smoker randomly
		if (rand_number == 0) {
			printf("Tobacco and paper now on the table\n");
			sleep(1);
			V(match);
		}
		else if (rand_number == 1) {
			printf("Paper and match now on the table\n");
			sleep(1);
			V(tobacco); 
		}
		else if (rand_number == 2) {
			printf("Match and tobacco now on the table\n");
			sleep(1);
			V(paper);
		} 
			
		V(lock);
		P(agent);

	}

	exit(0);

}