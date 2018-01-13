//
// Created by fly on 11/1/17.
//

#ifndef UCL_SERVER_UCLRECIEVE_H
#define UCL_SERVER_UCLRECIEVE_H

#include "test/test.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <thread>
#include <list>
#include <cstring>

#define PORT 7000
#define IP "127.0.0.1"

void getConn();

void getData();

void sendMess();

void socketRecieve();

#endif //UCL_SERVER_UCLRECIEVE_H
