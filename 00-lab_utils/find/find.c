#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	printf("Inside find utility...\n");
	if(argc != 3){
		fprintf(2, "Usage: find <directory> <filename to find>...\n");
		exit(1);
	}

	// Graceful exit
	exit(0);
}
