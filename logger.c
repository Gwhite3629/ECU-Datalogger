#include "config.h"
#include "utils.h"

#include <stdio.h>

int main(void)
{
    int ret = SUCCESS;
    char conf[20] = "DEFAULT";
    struct sensor *user_table = NULL;
    int size = 0;

    init_table();
    
    CHECK(read_config(&user_table, &size, conf));

    for (int i = 0; i < size; i++) {
        printf("Table[%d]\n\tID: %s\n\tHash: %lu\n\tPID: 0x%02X\n\tTime: %d\n\tWidth: %d\n\tPoll: %f\n\n", \
        i, user_table[i].ID, user_table[i].hash, user_table[i].PID, user_table[i].time, user_table[i].width, \
        user_table[i].poll);
    }

exit:
    SFREE(user_table);
    return ret;
}