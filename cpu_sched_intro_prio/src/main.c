#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cpu_sched_prio.h"

int main() {
  pid_t pids[NUM_CHILDREN];
  int priorities[NUM_CHILDREN] = {-10, 0, 20};

  // In parent process
  struct timeval tv;
  gettimeofday(&tv, NULL);

  // Create multiple CPU-bound processes with different priorities
  for (int i = 0; i < NUM_CHILDREN; i++) {
    pids[i] = fork();
    if (pids[i] < 0) {
      perror("fork");
      exit(1);
    }

    if (pids[i] == 0) {
      // In child process
      struct timeval ctv;

      AssignPriorities(&i, priorities);

      // Start the CPU-bound task
      CPUBoundTask(i + 1);

      // To print time delta
      gettimeofday(&ctv, NULL);

      // Calculate time delta
      CalculateTime(i + 1, tv, ctv);

      exit(0);
    }
  }

  // Parent process: wait for all child processes
  for (int i = 0; i < NUM_CHILDREN; i++) {
    wait(NULL);  // Waiting for child processes (will block)
  }

  return 0;
}
