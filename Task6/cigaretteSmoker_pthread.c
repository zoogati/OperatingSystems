/* 
    Cigarette-Smoker Problem - Written by Socratis Katehis
	CSC 332: Operating Systems
	November 28th, 2017
*/

#include<stdio.h>
#include<sys/types.h>
#include<pthread.h>

// The condition for the mutex. Really simple.
int table_used = 0;

// Character array for names and int array for table.
int table[2];
char *item[] = { "tobacco", "paper", "matches" };

// The mutex that will lock/unlock threads.
pthread_mutex_t mutex;

void *agent_process()
{
	// Initialize with no items.
	int item_1 = 0;
    int item_2 = 0;
	
    while (1) {
		
		// Lock for this process.
	    pthread_mutex_lock(&mutex);
		
		// Check the condition.
        if (!table_used) {
			
			// Take two random.
            item_1 = rand() % 3;
            item_2 = rand() % 3;
			
            if (item_1 != item_2) {
				
				// Set items on the table.
                table[0] = item_1;
                table[1] = item_2;
                printf ("Agent placed %s and %s on the table.\n", item[item_1], item[item_2]);
			    sleep(1);
				
				// Condition is changed.
                table_used = 1;
				
			}
		}

		// Unlock thread for smokers	
		pthread_mutex_unlock(&mutex);
   }
}

void *smoker_process(int i) {
	
   while (1) {
	   
	    // Lock for this process.
	    pthread_mutex_lock(&mutex);
		
		// Check the condition.
        if (table_used) {
			
			// Check who is up to smoke.
            if (table[0] != i && table[1] != i ) {
				
		        if (i == 0) {
				    printf ("Smoker with tobacco starts smoking.\n");
				    sleep(1);
				}
	            else if (i == 1) {
                    printf ( "Smoker with paper starts smoking.\n");
			        sleep(1);
				}
                else if (i == 2) {
			        printf ( "Smoker with matches starts smoking.\n" );
		            sleep(1);
				}
				
				// Condition is changed.
				table_used = 0;
			}
		}
	
		// Unlock the thread for the agent.
		pthread_mutex_lock(&mutex);
    }
}

int main() {
	
   pthread_t agent, smokers[3];
   
   int smoke_material[] = {0, 1, 2};
   
   // Create threads for our smokers and agent.
   pthread_create(&agent, NULL, agent_process, NULL);
   
   for (int i = 0; i < 3; i++)
   {
	   pthread_create(&smokers[i], NULL, smoker_process, smoke_material[i]);
   }
   
   // Wait for threads to finish.
   pthread_join(agent, NULL);
   
   for (int i = 0; i < 3; i++)
   {
	   pthread_join(&smokers[i], NULL);
   }
   
}
