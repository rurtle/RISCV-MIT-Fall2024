#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(char *path, char *filename)
{
	int fd;
	// struct dirent de;
	struct stat st;

	if ((fd = open(path, O_RDONLY)) < 0) {
		fprintf(2, "find: cannot open %s\n", path);
		return;
	}

	if (fstat(fd, &st) < 0) {
		fprintf(2, "find: cannot stat %s\n", path);
		close(fd);
		return;
	}

	switch(st.type) {
		case T_DEVICE:
		case T_FILE:
			// printf("%d %d %d %d\n", fmtname(path), st.type, st.ino, (int) st.size);
			printf("%d %d %d\n", st.type, st.ino, (int) st.size);
			break;
		case T_DIR:
			printf("find: recurse through directory %s\n", path);
			break;
	}
	close(fd);
}

int
main(int argc, char *argv[])
{
	printf("Inside find utility...\n");
	if(argc != 3){
		fprintf(2, "Usage: find <directory> <filename to find>...\n");
		exit(1);
	}

	// Assuming we've received the correct set of arguments
	find(argv[1], argv[2]);

	// Graceful exit
	exit(0);
}
