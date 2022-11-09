#include "config.h"
#include "commands.h"
#include "utils.h"

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

struct running_data {
    struct sensor sens;
    FILE *data;
    unsigned int mult;
};

pthread_spinlock_t SPI_LOCK;

time_t thread_start_time;

int gcd(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}

static void *sens_thread(void *arg)
{
    struct sensor *input = (struct sensor *)arg;
    unsigned long tdiff = 0; // Time that data processing took in microseconds
    struct timespec start;
    struct timespec end;
    unsigned long delay = 0;
    int ret = SUCCESS;
    FILE *file = NULL;
    uint8_t *s_data = NULL;
    pthread_cleanup_push((void *)fclose, file);
    // Construct header

    // Get delay in microseconds
    delay = (unsigned long)((1.0/((float)input->poll))*1000000.0f);

    // Open file, replace with VIN code
    file = fopen(input->ID, "wb");

    MEM(s_data, input->width, uint8_t);

    while (1) {
        // Acquire start time
        clock_gettime(CLOCK_REALTIME, &start);
        pthread_spin_lock(&SPI_LOCK);
        // IOCTL to send
        // IOCTL to receive
        pthread_spin_unlock(&SPI_LOCK);
        // Write data to file, use start time which is well aligned
        if (input->time) {
            fwrite(&(start.tv_sec), sizeof(time_t), 1, file);
            fwrite(s_data, sizeof(uint8_t), input->width, file);
        } else {
            fwrite(s_data, sizeof(uint8_t), input->width, file);
        }

        // Acquire end time
        clock_gettime(CLOCK_REALTIME, &end);
        tdiff = (end.tv_nsec - start.tv_nsec) * 1000; // Get tdiff in microseconds
        // Delay in microseconds
        usleep((delay > tdiff) ? (delay - tdiff) : 1);
    }

exit:
    pthread_cleanup_pop(1);
    pthread_exit(&ret);
    return NULL;
}

int main(void)
{
    int ret = SUCCESS;
    char conf[20] = "DEFAULT";
    struct sensor *user_table = NULL;
    struct environment *env = NULL;
    pthread_t thr;
    pthread_t *sens_thr = NULL;

    init_table();

    MEM(env, 1, struct environment);

    env->user_table = &user_table;
    env->update = 0;
    env->print = 0;
    env->exit = 0;
    pthread_spin_init(&env->lock, 0);
    pthread_cond_init(&env->cond, NULL);
    pthread_mutex_init(&env->cond_lock, NULL);
    
    CHECK(read_config(&user_table, &(env->size), conf));

    MEM(sens_thr, env->size, pthread_t);

    HANDLE_ERR(pthread_create(&thr, NULL, &input, &env), "pthread_create");

    // Do nothing
    while(!(env->exit));
    /* * * * * * * * * * * * * * * * * * * * * * * * * * *
     * TODO:
     *      - Construct CAN headers.
     * METHOD 1:
     *      - Dispatch thread for each event
     *      - Alter input loop to set flags, have main thread check values
     *      - Main thread:
     *          - Dispatch input handler
     *          - Dispatch sensor threads
     *          - Manage sensor threads
     *          - Start new thread on event add
     *          - Cancel thread when one is removed
     *          - Wait for signals from user
     *      - Each thread created a binary file. At startup the program requests VIN
     *      - Folder is created for VIN and a trips file is created.
     *      - Trips file contains:
     *          - Trip number
     *          - Trip total time
     *      - VIN folder contains all sensor data, named after the trip and sensor
     * 
     * METHOD 2:
     *      - Find GCD of all thread polling rates
     *      - Create sub-buffers for each valid multiple of the GCD
     *      - Run sensors in sections with their multiples of GCDs with a counter loop.
     *      - Time data collection for more accurate polling rates.
     * 
     * * * * * * * * * * * * * * * * * * * * * * * * * * */


// METHOD 1:

    // Initial thread dispatch
    for (unsigned int i = 0; i < env->size; i++) {
        pthread_create(&sens_thr[i], NULL, &sens_thread, &(*env->user_table)[i]);
    }

    while(!env->exit) {
        while(!env->update & !env->exit) {
            usleep(10000); // Check update every 10ms
        }
        // Main thread has been informed by user input

        // Join threads for data safety
        for (unsigned int i = 0; i < env->size; i++) {
            pthread_join(sens_thr[i], NULL);
        }

        // Send signal to input thread to do memory update
        pthread_cond_signal(&env->cond);

        // Wait for return signal from input thread
        while (env->update) {
            usleep(100);
        }

        // We didn't quit, so update happened
        if (!env->exit) {
            // Dispatch threads again after update
            MEM_(sens_thr, env->size, pthread_t);
            for (unsigned int i = 0; i < env->size; i++) {
                pthread_create(&sens_thr[i], NULL, &sens_thread, &(*env->user_table)[i]);
            }
        }
    }


// METHOD 2:
/*
    while (!env->exit) {
        // Update section
        unsigned int GCD = 0;
        int temp  = 0;
        struct running_data *sensors = NULL;
        MEM(sensors, env->size, struct running_data);

        // Get the GCD
        for (unsigned int i = 0; i < env->size; i++) {
            temp = gcd(temp, (*env->user_table)[i].poll);
        }
        GCD = temp;

        for (unsigned int i = 0; i < env->size; i++) {
            sensors[i].sens = (*env->user_table)[i];
            sensors[i].mult = sensors[i].sens.poll / GCD;
            // Improve this for VIN folder auto-finding
            sensors[i].data = fopen(sensors[i].sens.ID, "wb");
        }

        // Data reading section
        while (!env->update & !env->exit) {

        }
    }
*/

    HANDLE_ERR(pthread_join(thr, NULL), "pthread_join");

exit:
    SFREE(user_table);
    SFREE(env);
    return ret;
}