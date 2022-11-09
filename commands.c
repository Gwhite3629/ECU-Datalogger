#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>

#include "commands.h"
#include "config.h"
#include "sensors.h"
#include "utils.h"

void *input(void *arg)
{
    int ret = SUCCESS;
    char t = 'N';
    float tf = 0.0;
    char ts[80];
    struct sensor temp;
    struct environment **env = (struct environment **)arg;

    char input[100];
    char command[20];
    char user[80];
    memset(input, 0, 100);
    memset(command, 0, 20);
    memset(user, 0, 80);

    while(1) {
        fgets(input, 100, stdin);
        strcpy(user, strpbrk(input, "\n "));
        strncpy(command, input, strcspn(input, ":"));

        if (user[0] == ' ') {
            for (int i = 0; i < (int)strlen(user); i++) {
                user[i] = user[i + 1];
            }
        } if (user[strlen(user) - 1] == '\n') {
            user[strlen(user) - 1] = '\0';
        }

        if (!strcmp(command, "SHOW")) {
            print((*(*env)->user_table), (*env)->size);
        } else if (!strcmp(command, "ADD")) {
            // Inform main thread
            (*env)->update = 1;
            // Wait for signal from main
            pthread_cond_wait((*env)->cond, (*env)->cond_lock);
            // Do update
            pthread_spin_lock(&(*env)->lock);
            int spaces = 0;
            for (int i = 0; i < (int)strlen(user); i++) {
                if (user[i] == ' ')
                    spaces++;
            }
            if (strlen(user) == 0) {
                printf("Check arguments\n");
            } else if (spaces != 2) {
                printf("Check arguments\n");
            } else {
                sscanf(user, "%s %c %f", ts, &t, &tf);
                temp = table_lookup(ts,(*(*env)->user_table), (*env)->size);
                if (temp.hash == 0)
                {
                    // Add an element to the table
                    MEM_((*(*env)->user_table), (*env)->size + 1, struct sensor);
                    // Set the value of the ID, time, and poll
                    strcpy((*(*env)->user_table)[(*env)->size].ID,ts);
                    if (t == 'Y') {
                        (*(*env)->user_table)[(*env)->size].time = 1;
                    } else {
                        (*(*env)->user_table)[(*env)->size].time = 0;
                    }
                    (*(*env)->user_table)[(*env)->size].poll = tf;
                    // Set the value of the hash
                    (*(*env)->user_table)[(*env)->size].hash = (int)(hash((*(*env)->user_table)[(*env)->size].ID) % (INT_MAX));
                    // Get pre-set values
                    temp = lookup((*(*env)->user_table)[(*env)->size].ID);
                    if (temp.hash == 0) {
                        printf("ID not found\n");
                        MEM_((*(*env)->user_table), (*env)->size, struct sensor);
                    } else {
                        (*(*env)->user_table)[(*env)->size].PID = temp.PID;
                        (*(*env)->user_table)[(*env)->size].width = temp.width;
                        (*env)->size++;
                        // Sort array
                        qsort((*(*env)->user_table), (*env)->size, sizeof(struct sensor), &cmp);
                    }
                } else {
                    printf("Sensor already being polled\n");
                }
            }
            pthread_spin_unlock(&(*env)->lock);
            // Send return signal that update has concluded
            (*env)->update = 0;
        } else if (!strcmp(command, "REMOVE")) {
            // Inform main thread
            (*env)->update = 1;
            // Wait for signal from main thread
            pthread_cond_wait((*env)->cond, (*env)->cond_lock);
            // Do update
            pthread_spin_lock(&(*env)->lock);
            if ((*env)->size != 1) {
                temp = table_lookup(user, (*(*env)->user_table), (*env)->size);
                struct sensor *r = bsearch(&temp, (*(*env)->user_table), (*env)->size, sizeof(struct sensor), &cmp);
                if (r != NULL) {
                    temp = (*(*env)->user_table)[(*env)->size - 1];
                    (*(*env)->user_table)[(*env)->size-1] = (*r);
                    (*r) = temp;
                    (*env)->size--;
                    MEM_((*(*env)->user_table), (*env)->size, struct sensor);
                    qsort((*(*env)->user_table), (*env)->size, sizeof(struct sensor), &cmp);
                } else {
                    printf("ID not found\n");
                }
            } else {
                printf("Must have atleats one sensor.\n");
            }
            pthread_spin_unlock(&(*env)->lock);
            // Send return signal
            (*env)->update = 0;
        } else if (!strcmp(command, "PRINT")) {
            pthread_spin_lock(&(*env)->lock);
            (*env)->print = !(*env)->print;
            pthread_spin_unlock(&(*env)->lock);
        } else if (!strcmp(command, "HELP")) {
            printf( \
            "VALID COMMANDS:\n \
            \tSHOW:\n \
            \t\tShow the currently monitored sensors and their stats.\n\n \
            \tADD: <ID> <TIME> <POLL>\n \
            \t\tAdd the sensor with the provided ID.\n\n \
            \tREMOVE: <ID>\n \
            \t\tRemove the sensor with the provided ID.\n\n \
            \tPRINT:\n \
            \t\tPrint the polled sensor values.\n\n \
            \tHELP:\n \
            \t\tDisplays this menu.\n\n \
            \tQUIT:\n \
            \t\tExits the program.\n\n");
        } else if (!strcmp(command, "QUIT")) {
            (*env)->exit = 1;
            goto exit;
        } else {
            printf("Please enter valid command, type HELP: for a list\n");
        }
        memset(input, 0, 100);
        memset(command, 0, 20);
        memset(user, 0, 80);
    }

exit:
    (*env)->exit = 1;
    pthread_exit(&ret);
    return NULL;
}