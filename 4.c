/*
============================================================================
Name : 4.c
Author : Shreyas Gangurde
Description : 4. Write a program to measure how much time is taken to execute
              100 getppid() system calls using the timestamp counter.
Date: 12th September 2025
============================================================================
*/

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// Inline assembly to read Time Stamp Counter
static __inline__ uint64_t rdtsc(void) {
  unsigned int lo, hi;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)hi << 32) | lo;
}

int main() {
  uint64_t start, end;
  int i;

  start = rdtsc();

  for (i = 0; i < 100; i++) {
    getppid();
  }

  end = rdtsc();

  printf("Cycles taken for 100 getppid() calls: %llu\n", (unsigned long long)(end - start));
  printf("Average cycles per call: %llu\n", (unsigned long long)((end - start) / 100));

  return 0;
}

/* OUTPUT
============================================================================
Cycles taken for 100 getppid() calls: 28596
Average cycles per call: 285
============================================================================
*/