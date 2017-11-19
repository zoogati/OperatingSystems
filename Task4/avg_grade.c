/* 
    Average Grade Calculator - Written by Socratis Katehis
	CSC 332: Operating Systems
	October 25th, 2017
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main (int argc, char *argv[]) {
	
	//Number of students, always 10.
	int students = 10;
	
	//Stores current HW from array.
	int input;
	
	//Thread statuses
	int manager = 0, worker = 0;
	
	//Loop iterators for creating children.
	int row = 0, column = 0, total = 0;
	
	if (argc < 4) {
		printf("Incorrect Usage! Should be filepath, number of chapters, number of homeworks.");
		return 1;
	}
	
	char file_name[strlen(argv[1])];
	strcpy(file_name, argv[1]);
	int chapters = atoi(argv[2]);			// Must be at least 1.
	int hw_per_chapter = atoi(argv[3]);		// Must be at least 1.
	
	// Calculate total number of children to be created.
	int total_hw = chapters * hw_per_chapter;

	// Allocate memory.
	int *grades[students];
	for (int i = 0; i < students; i++) 
	{
		grades[i] = (int *) malloc(total_hw * sizeof(int));
		
	} 
	
	// Extract data from input file.
	FILE *input_file = fopen(file_name, "r");
	for (int i = 0; i < students; i++) {
     	for (int j = 0; (j < total_hw) && ( (fscanf(input_file, "%d", &input)) ) > 0 ; j++) {
			grades[i][j] = input;
			}
		}
	fclose(input_file);
	
	// Loops for creating children and calculating averages.
	for (int i = 0; i < chapters; i++) {
		manager = fork();
		if (manager < 0) {
			perror("Manager fork");
			return 1;
		}
		else if (manager == 0) {
			for (int j = 0; j < hw_per_chapter; j++) {
				worker = fork();
				if (worker < 0) {
					perror("Worker fork");
					return 1;
				}
				else if (worker == 0) {
					column += j;
					
					for (row = 0; row < 10; row++) {
						total += grades[row][column];
					}
					printf("Chapter %d - HW %d: %0.2f\n", (i+1), (j+1), total/10.0);
					return 1;
				}
			}
		return 1;
		}
		column += hw_per_chapter;
	}
	
	return 0;
}
