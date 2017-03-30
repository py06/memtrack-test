#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void *alloc_ptr = NULL;

int menu()
{
	int sel = 0;
	printf("1. alloc\n");
	printf("2. free\n");
	printf("3. map\n");
	printf("4. unmap\n");
	scanf("%d", &sel);
	return sel;
}

int test_alloc()
{
	int sz = 0;
	printf("size =");
	scanf("%d", &sz);

	alloc_ptr = malloc(sz);
	if (!alloc_ptr) {
		fprintf(stderr, "Could not allocate %d bytes", sz);
		return -ENOMEM;
	}
	return 0;
}

int test_free()
{
	free(alloc_ptr);
}

int main(int argc, char *argv[])
{
	int c;

	printf("Test tool: pid = %d\n", (int)getpid());
	while(1) {
		switch(c=menu()) {
		case 1:
			test_alloc();
			break;
		case 2:
			test_free();
			break;
		default:
			break;
		}
	}
}
