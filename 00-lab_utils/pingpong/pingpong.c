/**
 * @problem		pingpong
 *
 * @difficulty		easy
 *
 * @description		Write a user-level program that uses xv6 system calls to ''ping-pong'' a byte 
 * 			between two processes over a pair of pipes, one for each direction. The parent
 * 			should send a byte to the child; the child should print "<pid>: received ping",
 * 			where <pid> is its process ID, write the byte on the pipe to the parent, and
 * 			exit; the parent should read the byte from the child, print "<pid>: received
 * 			pong", and exit. Your solution should be in the file user/pingpong.c. 
 *
 * @notes
 * 			1. Add the program to UPROGS in Makefile. 
 * 			2. You'll need to use the pipe, fork, write, read, and getpid system calls.
 * 			3. User programs on xv6 have a limited set of library functions available to
 * 			them. You can see the list in user/user.h; the source (other than for system
 * 			calls) is in user/ulib.c, user/printf.c, and user/umalloc.c.
 *
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	// int fdc[2];
	int fds[2];
	char x;

	// Sanity check
	if (pipe(fds) < 0) {
		printf("pingpong: pipe failed\n");
		exit(1);
	}

	// Parent sending a byte to the child
	if (write(fds[1], "Z", 1) != 1)
		printf("pingpong: pipe write failed at parent - 1\n");


	// const char c = 'w';			// This is the byte I want to send back-and-forth
	int pid = fork();
	if (pid < 0) {
		printf("fork failed\n");
		exit(1);
	} else if (pid == 0) {
		if (read(fds[0], &x, 1) != 1) {
			printf("pingpong: pipe read failed\n");
		} else {
			// printf("%d: received ping: %d\n", getpid(), x);
			printf("%d: received ping\n", getpid());
			// Adding a bit of twist. I'm writing a different byte to the file descriptor
			// and trying to see if I'm able to read it from the parent process.
			// Based on test results, this seem to work predictably. :)
			if (write(fds[1], "A", 1) != 1) {
				printf("pingpong: write failed: child\n");
			}
		}

	} else {
		// Inside parent process
		wait(0);
		if (read(fds[0], &x, 1) != 1) {
			printf("pingpong: read failed: parent\n");
		} else {
			// printf("%d: received pong: %d\n", getpid(), x);
			printf("%d: received pong\n", getpid());
		}
	}

	// Graceful exit
	exit(0);
}
