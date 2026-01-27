#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	if(argc != 2){
		fprintf(2, "Usage: sleep seconds...\n");
		exit(1);
	}

	// Get the command line argument, convert it from string to int
	// and sleep for desired duration
	sleep(atoi(argv[1]));
	// Graceful exit
	exit(0);
}
