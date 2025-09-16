/*
============================================================================
Name : 2.c
Author : Shreyas Gangurde
Description : 2. Write a program to print the system resource limits. Use getrlimit system call.
Date: 10th September 2025
============================================================================
*/
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>

// RLIMIT_CPU - CPU time
// RLIMIT_FSIZE - File size
// RLIMIT_DATA - Data segment
// RLIMIT_STACK - Stack size
// RLIMIT_CORE - Core file size
// RLIMIT_RSS - Resident memory (soft-deprecated in Linux)
// RLIMIT_NOFILE - Open files
// RLIMIT_AS - Virtual memory (Address Space)

// limit value -1 basically means no enforced limit

// soft limit - actual currently actively enforced limit.
// hard limit - ceiling/cap for the value of soft limit.

int main() {

  struct rlimit old_lim;

  if (getrlimit(RLIMIT_NOFILE, &old_lim) == 0)
    printf("SYSTEM LIMITS \nsoft limit= %ld\n"
           "hard limit= %ld \n",
           old_lim.rlim_cur, old_lim.rlim_max);

  return 0;
}
/* OUTPUT
============================================================================
SYSTEM LIMITS
soft limit= 1024
hard limit= 1048576
============================================================================
*/
