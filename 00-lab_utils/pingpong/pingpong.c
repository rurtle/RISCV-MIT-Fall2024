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
			printf("%d: received ping: %d\n", getpid(), x);
			if (write(fds[1], "A", 1) != 1) {
				printf("pingpong: write failed: child\n");
			}
		}

	} else {
		// Inside parent process
		wait(0);
		if (read(fds[0], &x, 1) != 0) {
			printf("pingpong: read failed: parent\n");
		} else {
			printf("%d: received pong: %d\n", getpid(), x);
		}
	}

	// Graceful exit
	exit(0);
}
