#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void chmod_if_public_write(char *path);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		// Print an error to standard error if needed
		fprintf(stderr, "Please provide 1 or more arguments");
	}

	// Loop through the arguments and process each one
	int i = 0;
	while (i < argc) {
		chmod_if_public_write(argv[i]);
		i++;
	}

	return EXIT_SUCCESS;
}

void chmod_if_public_write(char *path) {
	// Get the file metadata and put it into our struct
	struct stat stats;
	int result = stat(path, &stats);
	// Check if the function worked and print an error if needed
	if (result != 0) {
		perror(path);
		return;
	}

	// Check if writeable ("W") by others ("OTH") using the provided bit mask
	if (stats.st_mode & S_IWOTH) {
		// Flip that bit to a 0 if needed (negate the mask so that bit becomes 0 and everything else becomes 1)
		mode_t new_mode = stats.st_mode & ~S_IWOTH;
		// Change ("ch") the mode ("mod"), and print an error if needed
		int result = chmod(path, new_mode);
		if (result != 0) {
			perror(path);
			return;
		}
	}
}
