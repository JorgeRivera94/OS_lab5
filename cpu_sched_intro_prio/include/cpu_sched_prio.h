#ifndef CPU_SCHED_PRIO_H
#define CPU_SCHED_PRIO_H

#include <stdlib.h>
#include <sys/time.h>

/**
 * @brief Number of child precesses to be created.
 */
#define NUM_CHILDREN 3

/**
 * @brief Function that counts to 1,000,000,000 30 times.
 *
 * When the Funtion starts, it prints that it started and the process' process
 * ID. After every iteration, it prints its process ID and that it is still
 * running.
 * @param id Integer Process ID of the current process.
 */
void CPUBoundTask(int id);

/**
 * @brief Function that assigns priorities to the child processes.
 *
 * Prints the child process' index and process ID with the priority that will be
 * assigned to it. Then prints the initial priority and assigns the new
 * priority.
 * @param index Integer index of the child and priority.
 * @param priorities Integer Array of priorities to be assigned to the child
 * processes.
 */
void AssignPriorities(int* index, int priorities[3]);

/**
 * @brief Function that calculates the time delta from the time just before the
 * parent process creates the child processes to the time when the calling child
 * process finishes.
 *
 * Calculates the difference in seconds and microseconds, then checks for
 * underflow.
 * @param id Integer ID of the child process calling the function.
 * @param ptv Timeval structure of the time before the parent process creates
 * the child processes.
 * @param ctv Timeval structure of the time when the child process completes its
 * execution.
 */
void CalculateTime(int id, struct timeval ptv, struct timeval ctv);

#endif  // CPU_SCHED_PRIO_H