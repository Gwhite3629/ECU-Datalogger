#include "utils.h"
#include "commands.h"
#include "config.h"
#include "file.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

int find_dir(char **path, struct environment *env)
{
    // VIN request returns 17 chars
    char VIN[17];
    char trip[80];
    int ret = SUCCESS;
    struct can_frame frame;
    frame.can_id = CAN_ID;
    frame.can_dlc = 8;
    frame.data[0] = 0;
    frame.data[1] = 9; // Service: Request vehicle information
    frame.data[2] = 2; // Request VIN
    frame.data[3] = 0;
    frame.data[4] = 0;
    frame.data[5] = 0;
    frame.data[6] = 0;
    frame.data[7] = 0;

    while(1) {
        nbytes = read(CAN.socket, &Rframe, sizeof(Rframe));
        if (nbytes > 0) {
            int i = 0;
            for (i = 0; i < input->sens.width; i++) {
                VIN[i] = Rframe.data[i];
            }
            break;
        }
    }

    printf("Enter trip name: \n");
    scanf("%s\n", trip);

    MEM((*path), (17+1+strlen(trip)+1), char);

    strcat((*path), VIN);
    strcat((*path), "/");
    strcat((*path), trip);
    strcat((*path), "/");

exit:
    SFREE(path);
    return ret;
}

int get_file(FILE **sens_file, char *path, char *sens_ID, char *mode)
{
    int ret = SUCCESS;
    char *fpath = NULL;
    MEM(fpath, strlen(path) + strlen(sens_ID), char);
    strcat(fpath, path);
    strcat(fpath, sens_ID);
    (*sens_file) = fopen(fpath, mode);
    VALID((*sens_file), FILE_CODE, FILE_OPEN);

exit:
    SFREE(fpath);
    return ret;
}