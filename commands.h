#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <stdatomic.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#include "sensors.h"

/* Commands:
 * 
 * SHOW:
 *      Show the currently monitored sensors and their stats.
 * 
 * ADD: <ID> <TIME> <POLL>
 *      Add the sensor with the provided ID.
 * 
 * REMOVE: <ID>
 *      Remove the sensor with the provided ID.
 * 
 * PRINT:
 *      Print the polled sensor values.
 * 
 * 
 */

struct environment {
    struct sensor **user_table;
    bool update;
    bool print;
    bool exit;
    pthread_spinlock_t lock;
    size_t size;
    pthread_cond_t cond;
    pthread_mutex_t cond_lock;
};

void *input(void *arg);

#endif // _COMMANDS_H_