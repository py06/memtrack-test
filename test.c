#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <math.h>

void *alloc_ptr = NULL;
void *mmap_ptr = NULL;
char mmap_filename[256];
int mmap_len = 0;
int mmap_fd = 0;

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

int test_mmap()
{
	int addr = 0;
	int pagesize = sysconf(_SC_PAGE_SIZE);

	printf("filename =");
	scanf("%s", &mmap_filename);
	printf("len =");
	scanf("%d", &mmap_len);


	printf("pagesize=%d\n", pagesize);
	printf("mmaplen=%d ceil=%d\n", mmap_len,
	       (int)ceil((float)mmap_len / (float)pagesize) * pagesize);
	mmap_len = (int)ceil((float)mmap_len / (float)pagesize) * pagesize;

	mmap_fd = open(mmap_filename, O_RDONLY);
	if (mmap_fd == -1) {
		perror("open");
		return -ENOENT;
	}

	mmap_ptr = mmap(NULL, mmap_len, PROT_READ, MAP_PRIVATE, mmap_fd, 0);
	if (mmap_ptr == MAP_FAILED) {
		perror("mmap");
		return -ENOMEM;
	}
	return 0;
}

int test_munmap()
{
	munmap(mmap_ptr, mmap_len);
	close(mmap_fd);
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
		case 3:
			test_mmap();
			break;
		case 4:
			test_munmap();
			break;
		default:
			break;
		}
	}
}
