#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h> // For shared memory
#include <sys/ipc.h> // Also for shared memory, allows worker class to access shared memory

#define SHM_KEY 854038
#define NANO_TO_SEC 1000000000 

// Using a structure for our simulated clock, storing seconds and nanoseconds.
typedef struct SimulatedClock {
        int seconds;
        int nanoseconds;
} SimulatedClock;


// Structure for our PCB table
struct PCB {
	int occupied;
	pid_t pid;
	int startSeconds;
	int startNano;
};
struct PCB processTable[20];

void incrementClock(SimulatedClock *clock);

int main(int argc, char **argv) {
	int shmid = shmget(SHM_KEY, sizeof(SimulatedClock), IPC_CREAT | 0666); // Creating shared memory using shmget. 
    	
	if (shmid == -1) { // If shmid is -1 as a result of shmget failing and returning -1, error message will print.
        	perror("shmget failed");
        	exit(1);
    	}
	
	SimulatedClock *clock = (SimulatedClock *)shmat(shmid, NULL, 0); // Attach shared memory, clock is now a pointer to SimulatedClock structure.
	if (clock == (void *)-1) { // if shmat, the attaching shared memory function, fails, it returns an invalid memory address.
        	perror("shmat failed");
        	exit(1);
    	}

    	// Initialize clock
    	clock->seconds = 0;
    	clock->nanoseconds = 0;

	incrementClock(clock);

   	pid_t pid = fork(); // Forking, creating new child process.
    	
	if (pid < 0) { // If pid fails, return error message.
        	perror("fork failed");
        	exit(1);
    	}
    	else if (pid == 0) { // Child executes worker
        	execl("./worker", "worker", (char *)NULL);
        	perror("execl failed");
        	exit(1);
    	}

	wait(NULL); // Wait function 

	// Detach shared memory
    	if (shmdt(clock) == -1) {
        	perror("shmdt failed");
    	}	

    	// Remove shared memory
    	if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        	perror("shmctl failed");
    	}	
	
	return 0;
}

void incrementClock(SimulatedClock *clock) { // This function simulates the increment of our simulated clock.
	clock->nanoseconds += 100000; // Start increasing in milliseconds

	while (clock->nanoseconds >= NANO_TO_SEC) { // Expect even after reducing nano seconds to have a bit of remaining nano seconds, while ensures that if they build up, that they'll be reduced properly.
		clock->seconds++;
		clock->nanoseconds -= NANO_TO_SEC;	
	}
}
