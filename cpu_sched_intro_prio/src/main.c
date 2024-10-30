#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>  // for setpriority
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_CHILDREN 3

void cpu_bound_task(int id) {
  printf("Process %d started, pid: %d\n", id, getpid());
  for (int j = 0; j < 30; j++) {
    // CPU-bound work (Edited to run only 30 times)
    for (volatile long i = 0; i < 1000000000; i++);
    printf("Process %d still running, pid: %d\n", id, getpid());
  }
}

int main() {
  pid_t pids[NUM_CHILDREN];
  int priorities[NUM_CHILDREN] = {
      -10, 0, 20};  // Priorities: higher value means lower priority

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

      printf("Child %d (pid: %d) with priority %d\n", i + 1, getpid(),
             priorities[i]);

      printf("The initial priority is %d\n",
             getpriority(PRIO_PROCESS, getpid()));

      // Set the priority of this process
      if (setpriority(PRIO_PROCESS, getpid(), priorities[i]) < 0) {
        perror("setpriority");
        exit(1);
      }

      // Start the CPU-bound task
      cpu_bound_task(i + 1);

      // To print time delta
      gettimeofday(&ctv, NULL);

      int id = i + 1;
      printf("Process %d Seconds: %lf\n", id,
             (ctv.tv_sec - tv.tv_sec) + (ctv.tv_usec - tv.tv_usec) / 1e9);

      exit(0);  // Shouldn't reach here
    }
  }

  // Parent process: wait for all child processes
  for (int i = 0; i < NUM_CHILDREN; i++) {
    wait(NULL);  // Waiting for child processes (will block)
  }

  return 0;
}
