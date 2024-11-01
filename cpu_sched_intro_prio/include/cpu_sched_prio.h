#ifndef CPU_SCHED_PRIO_H
#define CPU_SCHED_PRIO_H

// includes

/**
 * @brief Number of child precesses to be created.
 */
#define NUM_CHILDREN 3

// Functions
/**
 * @brief Function that counts to 1,000,000,000 30 times.
 *
 * When the Funtion starts, it prints that it started and the process' process
 * ID. After every iteration, it prints it's process ID and that it is still
 * running.
 * @param id Process ID of the current process.
 */
void cpu_bound_task(int id);

// void

#endif  // CPU_SCHED_PRIO_H