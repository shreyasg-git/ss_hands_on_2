/*
============================================================================
Name : 19c.c
Author : Shreyas Gangurde
Description : 19. Create a FIFO file by
                c. use strace command to find out, which command (mknod or mkfifo) is better.
Date: 23rd September 2025
============================================================================
*/

/*  OUTPUT FOR mkfifo
============================================================================
...
munmap(0x772d28eb9000, 127511)          = 0
mknodat(AT_FDCWD, "myfifo", S_IFIFO|0666) = -1 EEXIST (File exists)
newfstatat(1, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}, AT_EMPTY_PATH) = 0
...
============================================================================
*/

/***  OUTPUT FOR mknod
============================================================================
...
munmap(0x7ae8bb703000, 127511)          = 0
mknodat(AT_FDCWD, "myfifo", S_IFIFO|0666) = -1 EEXIST (File exists)
newfstatat(1, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}, AT_EMPTY_PATH) = 0

...
============================================================================
*/

// WE CAN SEE THAT
// mkfifo is safer and more portable because it explicitly sets FIFO mode and handles errors.
// mknod is lower-level; you must provide correct flags yourself.