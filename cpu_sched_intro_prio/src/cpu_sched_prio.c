#include "cpu_sched_prio.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cpu_bound_task(int id) {
  printf("Process %d started, pid: %d\n", id, getpid());
  for (int j = 0; j < 30; j++) {
    // CPU-bound work (Edited to run only 30 times)
    for (volatile long i = 0; i < 1000000000; i++);
    printf("Process %d still running, pid: %d\n", id, getpid());
  }
}