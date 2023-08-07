#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define LINE_MAX 1024

void *thread_run(void *data) {
	while (true) {
		printf("feed me input!\n");
		sleep(1);
	}

	return NULL;
}

int main(void) {
	pthread_t thread;
	pthread_create(&thread, NULL, thread_run, NULL);

	char line[LINE_MAX];
	fgets(line, LINE_MAX, stdin);

	while (line != NULL) {
		printf("you entered: %s", line);
		fgets(line, LINE_MAX, stdin);
	}

	pthread_cancel(thread);
}
