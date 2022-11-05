#include <stdio.h>

static inline unsigned long
hash(char *name)
{
	unsigned long val = 5381;
	int c;
	while ((c = *name++)) {
		val = ((val << 5) + val) + c;
	}
	return val;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Give string argument\n");
        return -1;
    }

    int result = (int)(hash(argv[1]) % (__INT_MAX__));

    printf("Hash: %d\n", result);

    return 0;
}