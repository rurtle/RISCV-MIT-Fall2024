#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // int i;

  if(argc < 2){
    fprintf(2, "Usage: sleep <number of ticks>>\n");
    exit(1);
  }

	// Get the command line argument
	// Convert it from string to int
	// Sleep for desired duration

  exit(0);
}
