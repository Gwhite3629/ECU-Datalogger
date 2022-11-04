#ifndef _CONFIG_H_
#define _CONFIG_H_

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

#endif // _CONFIG_H_