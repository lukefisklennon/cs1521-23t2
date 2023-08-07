#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

void *thread_run(void *data) {
	char *input = (char *) data;

	while (true) {
		printf("%s\n", input);
	}

	return NULL;
}

int main() {
	char *message = "Bye";

	pthread_t thread;
	pthread_create(&thread, NULL, thread_run, message);

	while (true) {
		printf("there!\n");
	}
}
