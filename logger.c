#include "config.h"
#include "commands.h"
#include "utils.h"
#include "can_helper.h"

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

struct thr_data {
    bool exit;
    struct sensor sens;
};

pthread_spinlock_t SPI_LOCK;

struct timespec thread_start_time;

struct can_info CAN;

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
    struct thr_data *input = (struct thr_data *)arg;
    unsigned long tdiff = 0; // Time that data processing took in microseconds
    struct timespec start;
    struct timespec end;
    unsigned long delay = 0;
    int nbytes = 0;
    int ret = SUCCESS;
    FILE *file = NULL;
    uint8_t *s_data = NULL;
    struct can_frame Rframe;
    struct can_frame Sframe;
    pthread_cleanup_push((void *)fclose, file);
    // Construct header

    // Get delay in microseconds
    delay = (unsigned long)((1.0/((float)input->sens.poll))*1000000.0f);

    // Open file, replace with VIN code
    file = fopen(input->sens.ID, "wb");

    MEM(s_data, input->sens.width, uint8_t);

    Sframe = construct_frame(input->sens);

    while (!input->exit) {
        // Acquire start time
        clock_gettime(CLOCK_REALTIME, &start);
        pthread_spin_lock(&SPI_LOCK);
        // Send query
        nbytes = write(CAN.socket, &Sframe, sizeof(Sframe));
        HANDLE(nbytes != sizeof(Sframe), WRITE_ERR);
        
        // Receive response
        while(1) {
            nbytes = read(CAN.socket, &Rframe, sizeof(Rframe));
            if (nbytes > 0) {
                int i = 0;
                for (i = 0; i < input->sens.width, i++) {
                    s_data[i] = Rframe.data[i];
                }
                break;
            }
        }

        pthread_spin_unlock(&SPI_LOCK);
        // Write data to file, use start time which is well aligned
        
        if (input->sens.time) {
            fwrite(&(start.tv_sec), sizeof(time_t), 1, file);
            fwrite(s_data, sizeof(uint8_t), input->sens.width, file);
        } else {
            fwrite(s_data, sizeof(uint8_t), input->sens.width, file);
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
    struct thr_data *thread_data = NULL;
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
    pthread_spin_init(&SPI_LOCK, 0);
    
    CHECK(read_config(&user_table, &(env->size), conf));

    MEM(sens_thr, env->size, pthread_t);
    MEM(thread_data, env->size, struct thr_data);

    CHECK(init_socket(&CAN));

    HANDLE_ERR(pthread_create(&thr, NULL, &input, &env), "pthread_create");

    // Do nothing
    //while(!(env->exit));
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
        thread_data[i].exit = 0;
        thread_data[i].sens = (*env->user_table)[i];
        pthread_create(&sens_thr[i], NULL, &sens_thread, &thread_data[i]);
    }
    
    clock_gettime(CLOCK_REALTIME, &thread_start_time);

    while(!env->exit) {
        while(!env->update & !env->exit) {
            usleep(10000); // Check update every 10ms
        }
        // Main thread has been informed by user input
        printf("\nMAIN:\n\tGOT EXIT\n\n");

        // Join threads for data safety
        for (unsigned int i = 0; i < env->size; i++) {
            printf("MAIN:\n\tSTOP THREAD: %d\n", i);
            thread_data[i].exit = 1;
        }
        for (unsigned int i = 0; i < env->size; i++) {
            pthread_join(sens_thr[i], NULL);
            printf("MAIN:\n\tTHREAD JOINED: %d\n", i);
        }

        // Send signal to input thread to do memory update
        printf("\nMAIN:\n\tSENT SIGNAL\n\n");
        pthread_cond_signal(&env->cond);

        // Wait for return signal from input thread
        while (env->update) {
            usleep(100);
        }
        printf("\nMAIN:\n\tRECEIVED SIGNAL\n\n");

        // We didn't quit, so update happened
        if (!env->exit) {
            // Dispatch threads again after update
            MEM_(sens_thr, env->size, pthread_t);
            MEM_(thread_data, env->size, struct thr_data);
            for (unsigned int i = 0; i < env->size; i++) {
                thread_data[i].exit = 0;
                thread_data[i].sens = (*env->user_table)[i];
                pthread_create(&sens_thr[i], NULL, &sens_thread, &thread_data[i]);
                printf("START THREAD: %d\n", i);
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
    clean_socket(CAN);
    SFREE(sens_thr);
    SFREE(thread_data);
    SFREE(user_table);
    SFREE(env);
    return ret;
}