#include <stdio.h>

void convert(int value) {
	printf("%d = 0%03o = 0x%02x\n", value, value, value);
}

int main() {
	convert(10);
}
