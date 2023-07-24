#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIARY_FILE ".diary"

int main(int argc, char *argv[]) {
	char *home_path = getenv("HOME");
	if (home_path == NULL) {
		home_path = ".";
	}

	int path_length = strlen(home_path) + strlen(DIARY_FILE) + 2;
	char *diary_path = malloc(path_length);

	snprintf(diary_path, path_length, "%s/%s", home_path, DIARY_FILE);

	FILE *diary_file = fopen(diary_path, "r");
	if (diary_file == NULL) {
		perror(diary_path);
		return EXIT_FAILURE;
	}

	int c;
	while ((c = fgetc(diary_file)) != EOF) {
		fputc(c, stdout);
	}

	fclose(diary_file);
	free(diary_path);

	return EXIT_SUCCESS;
}
