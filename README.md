Project Author: Dat Nguyen

Course: Comp Sci 4760

Date: 3/04/2025

GitHub Link: github.com/O-wll/OPSYS4760-PROJECT-2

Description of Project:

This project utilizes a simulated clock and shared memory. oss.c creates shared memory and shares the SimulatedClock struct, worker.c will have access to this shared memory.
oss.c initializes the clock and forks child processes, also known as workers. worker.c prints out the PID, PPID, time on simulated clock, the lifetime of the worker, and how many seconds have passed since worker child was initiated.

User will be able to:
- Control how many total child/workers there are.
- Control how many total child/workers run at once.
- Control how long the child process will last/
- Control the interval of when child processes run.

How to compile, build, and use project:

The project comes with a makefile so ensure that when running this project that the makefile is in it.

Type 'make' and this will generate both the oss exe and user exe along with their object file.

user exe is ONLY for testing if user works, to properly use this program, type './oss -h' for instructions on how to use it.

When done and want to delete, run 'make clean' and the exe and object files will be deleted.

Issues Ran Into:
- Forgetting to create shared memory and getting confused on why I wasn't able to access shared memory.
- Infinite loop as a result of a misplaced if statement.
- Had trouble with using the simulated structure table.
- Couldn't test if alarm logic works, theoretically it should.
- Time constraint
- Forgetting to update my git/github when making commits.
