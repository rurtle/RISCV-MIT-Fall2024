#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	fprintf(2, "Inside ping-pong...\n");

	// const char c = 'w';			// This is the byte I want to send back-and-forth
	int pid = fork();
	if (pid < 0) {
		printf("fork failed\n");
		exit(1);
	} else if (pid == 0) {
		// Inside child process
		printf("Inside child\n");

	} else {
		// Inside parent process
		wait(0);
		printf("Inside parent\n");
	}

	// Graceful exit
	exit(0);
}
