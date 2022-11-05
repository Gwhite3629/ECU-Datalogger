#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "sensors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static inline int
cmp(const void *va, const void *vb)
{
	const struct sensor *a = (struct sensor *)va;
	const struct sensor *b = (struct sensor *)vb;
	return (int)(a->hash - b->hash);
}

static inline void
init_table(void) {
	qsort(&SENSORS, TABLESIZE, sizeof(struct sensor), &cmp);
}

static inline struct sensor
lookup(char *name)
{
	struct sensor zero = {
		"None",
		0,
		0,
		0,
		0,
		0
	};
	int key = (int)(hash(name) % (INT_MAX));
	struct sensor table = {"None",key,0,0,0,0};
	struct sensor *r = bsearch(&table, &SENSORS, TABLESIZE, sizeof(struct sensor), &cmp);
	return r ? *r : zero;
}

static inline struct sensor
table_lookup(char *name, struct sensor *user_table, int size)
{
	struct sensor zero = {
		"None",
		0,
		0,
		0,
		0,
		0
	};
	int key = (int)(hash(name) % (INT_MAX));
	struct sensor table = {"None",key,0,0,0,0};
	struct sensor *r = bsearch(&table, user_table, size, sizeof(struct sensor), &cmp);
	return r ? *r : zero;
}

static inline void
print(struct sensor *user_table, size_t size)
{
	for (size_t i = 0; i < size; i++) {
        printf("Table[%I64d]\n\tID: %s\n\tHash: %d\n\tPID: 0x%02X\n\tTime: %d\n\tWidth: %d\n\tPoll: %f\n\n", \
        i, user_table[i].ID, user_table[i].hash, user_table[i].PID, user_table[i].time, user_table[i].width, \
		user_table[i].poll);
    }
}

int search(FILE* fd, fpos_t* prof_start, fpos_t* prof_end, const char *locator);

int read_config(struct sensor **user_table, size_t *size, char *conf_name);

#endif // _CONFIG_H_