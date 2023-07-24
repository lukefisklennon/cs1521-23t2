#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void chmod_if_public_write(char *path);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Please provide 1 or more arguments");
	}

	int i = 0;
	while (i < argc) {
		chmod_if_public_write(argv[i]);
		i++;
	}

	return EXIT_SUCCESS;
}

void chmod_if_public_write(char *path) {
	struct stat stats;
	int result = stat(path, &stats);
	if (result != 0) {
		perror(path);
		return;
	}

	if (stats.st_mode & S_IWOTH) {
		mode_t new_mode = stats.st_mode & ~S_IWOTH;
		int result = chmod(path, new_mode);
		if (result != 0) {
			perror(path);
			return;
		}
	}
}
