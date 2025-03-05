#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define SHM_KEY 854038

// SimulatedClock structure that will be used as our system clock required in project.
typedef struct SimulatedClock {
	int seconds;
	int nanoseconds;
} SimulatedClock;

int main(int argc, char** argv) {
	
	// Using shmget to get shared memory between oss.c and worker.c 
	int shmid = shmget(SHM_KEY, sizeof(SimulatedClock), 0666);
	
	if (shmid == -1) { // Error handling if shmget fails.
        	perror("shmget failed");
        	exit(1);
    	}

	SimulatedClock *clockSHM = (SimulatedClock *)shmat(shmid, NULL, 0); // clockSHM is a pointer to the shared memory where the SimulatedClock, which was put in the shared memory by oss.c, resides.

	if (clockSHM == (void *)-1) { // Error handling if clockSHM fails.
        	perror("shmat failed");
        	exit(1);
    	}	
	
	printf("Child: Current Time: %d sec %d ns\n", clockSHM->seconds, clockSHM->nanoseconds); // If working, the program will print out the seconds and nano seconds data from 

	if (shmdt(clockSHM) == -1) { // If detachment of shared memory fails, print error message.
        	perror("shmdt failed");
        	exit(1);
    	}

	return 0;
}

