#ifndef _CAN_HELPER_H_
#define _CAN_HELPER_H_

#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>

#include "sensors.h"

struct can_info {
    struct sockaddr_can addr;
    struct ifreq ifr;
    int socket;
};

#define CAN_ID 0x7DF

struct can_frame construct_frame(struct sensor sens);

int init_socket(struct can_info *sock);

void clean_socket(struct can_info sock);

#endif // _CAN_HELPER_H_
