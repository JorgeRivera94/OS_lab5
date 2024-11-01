#include "cpu_sched_prio.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>  // for setpriority
#include <sys/time.h>
#include <unistd.h>

void CPUBoundTask(int id) {
  printf("Process %d started, pid: %d\n", id, getpid());
  for (int j = 0; j < 30; j++) {
    // CPU-bound work (Edited to run only 30 times)
    for (volatile long i = 0; i < 1000000000; i++);
    printf("Process %d still running, pid: %d\n", id, getpid());
  }
}

void AssignPriorities(int* index, int priorities[3]) {
  printf("Child %d (pid: %d) with priority %d\n", *index + 1, getpid(),
         priorities[*index]);

  printf("The initial priority for child %d is %d\n", *index + 1,
         getpriority(PRIO_PROCESS, getpid()));

  // Set the priority of this process
  if (setpriority(PRIO_PROCESS, getpid(), priorities[*index]) < 0) {
    perror("setpriority");
    exit(1);
  }
}

void CalculateTime(int id, struct timeval ptv, struct timeval ctv) {
  long seconds = ctv.tv_sec - ptv.tv_sec;
  long microseconds = ctv.tv_usec - ptv.tv_usec;

  // Check underflow
  if (microseconds < 0) {
    seconds -= 1;
    microseconds += 1000000;
  }

  printf("Process %d\nSeconds: %ld\nMicroseconds: %ld\n", id, seconds,
         microseconds);
}