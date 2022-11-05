#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <stdbool.h>

#define TABLESIZE 25

struct sensor {
    char ID[20];
    int hash;
    int PID;
    bool time;
    int width;
    float poll;
};

extern struct sensor SENSORS;

#endif // _SENSORS_H_