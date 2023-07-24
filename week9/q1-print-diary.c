#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIARY_FILE ".diary"

int main(int argc, char *argv[]) {
	// Get the value of the $HOME envrionment variable, which is equivalent to "~" in the shell
	char *home_path = getenv("HOME");
	// Use ".", the current directory, as a fallback
	if (home_path == NULL) {
		home_path = ".";
	}

	// Calculate the amount of memory needed (size of $HOME + size of "/" + size of "./diary" + null terminator)
	int path_length = strlen(home_path) + strlen(DIARY_FILE) + 2;
	// Allocate the memory for the final pathname
	char *diary_path = malloc(path_length);
	// Put the paths together and output it to that new memory
	snprintf(diary_path, path_length, "%s/%s", home_path, DIARY_FILE);

	// Open the file and print an error message if needed
	FILE *diary_file = fopen(diary_path, "r");
	if (diary_file == NULL) {
		perror(diary_path);
		return EXIT_FAILURE;
	}

	// Loop through the file and print out each character
	int c;
	while ((c = fgetc(diary_file)) != EOF) {
		fputc(c, stdout);
	}

	// Close the file once done
	fclose(diary_file);
	// Free our memory once done
	free(diary_path);

	return EXIT_SUCCESS;
}
