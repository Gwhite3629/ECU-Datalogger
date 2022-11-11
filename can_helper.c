#include "sensors.h"
#include "can_helper.h"
#include "utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

struct can_frame construct_frame(struct sensor sens)
{
    struct can_frame frame;
    frame.can_id = CAN_ID;
    frame.can_dlc = 8;
    frame.data[0] = 0;
    frame.data[1] = 1;
    frame.data[2] = sens.PID;
    frame.data[3] = 0;
    frame.data[4] = 0;
    frame.data[5] = 0;
    frame.data[6] = 0;
    frame.data[7] = 0;

    return frame;
}

int init_socket(struct can_info *sock)
{
    int ret = SUCCESS;
    system("sudo ip link set can0 type can bitrate 500000");
    system("sudo ifconfig can0 up");

    // Create socket
    sock->socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    HANDLE(sock->socket < 0, SOCKET_OPEN);

    // Specify device
    strcpy(sock->ifr.ifr_name, "can0");
    ret = ioctl(sock->socket, SIOCGIFINDEX, &sock->ifr);
    HANDLE(ret < 0, IOCTL_ERR);

    // Bind socket to device
    sock->addr.can_family = AF_CAN;
    sock->addr.can_ifindex = sock->ifr.ifr_ifindex;
    ret = bind(sock->socket, (struct sockaddr *)&sock->addr, sizeof(sock->addr));
    HANDLE(ret < 0, BIND_ERR);

    // Define receive rules
    struct can_filter rfilter[1];
    rfilter[0].can_id = CAN_ID;
    rfilter[0].can_mask = CAN_SFF_MASK;
    setsockopt(sock->socket, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

exit:
    return ret;
}

void clean_socket(struct can_info sock)
{
    close(sock.socket);
    system("sudo ifconfig can0 down");
}
