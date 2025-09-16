/*
============================================================================
Name : 3.c
Author : Shreyas Gangurde
Description : 3. Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 10th September 2025
============================================================================
*/
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  struct rlimit old_lim, lim, new_lim;

  if (getrlimit(RLIMIT_NOFILE, &old_lim) == 0)
    printf("INITIAL SYSTEM LIMITS ON NUMBER OF OPEN FILES \nsoft limit= %ld\n"
           "hard limit= %ld \n",
           old_lim.rlim_cur, old_lim.rlim_max);

  lim.rlim_cur = 3;
  lim.rlim_max = 1024;

  setrlimit(RLIMIT_NOFILE, &lim);

  getrlimit(RLIMIT_NOFILE, &new_lim);

  printf("SYSTEM LIMITS AFTER MODIFICATIONS ON NUMBER OF OPEN FILES \nsoft limit= %ld\n"
         "hard limit= %ld \n",
         new_lim.rlim_cur, new_lim.rlim_max);

  if (open("foo.txt", O_WRONLY | O_CREAT, 0) == -1)
    fprintf(stderr, "ERROR :: %s\n", strerror(errno));

  return 0;
}

/* OUTPUT
============================================================================
INITIAL SYSTEM LIMITS ON NUMBER OF OPEN FILES
soft limit= 1024
hard limit= 1048576
SYSTEM LIMITS AFTER MODIFICATIONS ON NUMBER OF OPEN FILES
soft limit= 3
hard limit= 1024
ERROR :: Too many open files

============================================================================
*/