#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(char *path, char *filename)
{
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;
	// Check if we can open the path
	if ((fd = open(path, O_RDONLY)) < 0) {
		fprintf(2, "find: cannot open %s\n", path);
		return;
	}
	// Check if we can `stat` it
	if (fstat(fd, &st) < 0) {
		fprintf(2, "find: cannot stat %s\n", path);
		close(fd);
		return;
	}
	// Is it even a directory to begin with?
	if (st.type != T_DIR) {
		fprintf(2, "find: %s is not a directory\n", path);
		close(fd);
		return;
	}
	// Validate path length - is it too long?
	if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
		fprintf(2, "find: path too long\n");
		close(fd);
		return;
	}

	strcpy(buf, path);
	p = buf + strlen(buf);
	*p++ = '/';
	while (read(fd, &de, sizeof(de)) == sizeof(de)) {
		if (de.inum == 0 || !strcmp(de.name, ".") || !strcmp(de.name, ".."))
			continue;
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if (stat(buf, &st) < 0) {
			fprintf(2, "find: cannot stat %s\n", buf);
			continue;
		}
		if (st.type == T_FILE && !strcmp(de.name, filename))
			fprintf(1, "%s\n", buf);
		else if (st.type == T_DIR)
			find(buf, filename);
	}

	close(fd);
}

int
main(int argc, char *argv[])
{
	printf("Inside find utility...\n");

	if(argc < 2 || argc > 3){
		fprintf(2, "Usage: find (path) [file]\n");
		exit(1);
	} else if (argc == 2) {
		find(".", argv[1]);
	} else {
		find(argv[1], argv[2]);
	}


	// Graceful exit
	exit(0);
}
