#ifndef UCL_TEST_SOCKETSEND_H
#define UCL_TEST_SOCKETSEND_H

#include "test/test.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <cstring>
#include <sys/timeb.h>

#define MYPORT  7000
#define IP "127.0.0.1"

// 生成code部分
UCLCode generateCode(uint64_t timeStamp);

// 生成CGPS部分
UCLPropertySet generateCGPS();

// 生成ZCPS部分
UCLPropertySet generateZCPS(const string &hasObject,const string &boundingBox);

void socketSend(string ucl, int len);

string int2Hex(uint64_t num);

string BinToHex(const string &strBin, bool bIsUpper);

void genSendUCL(const vector<string> &imageList);

#endif //UCL_TEST_SOCKETSEND_H
