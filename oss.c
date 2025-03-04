#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/shm.h> // For shared memory
#include <sys/ipc.h> // Also for shared memory, allows worker class to access shared memory

// Using a structure for our simulated clock, storing seconds and nanoseconds.
typedef struct SimulatedClock {
	int seconds;
	int nanoseconds;
} SimulatedClock;


int main(int argc, char **argv) {
	SimulatedClock systemClock = {1, 1000000};
	printf("%d\n", systemClock.seconds);
}
