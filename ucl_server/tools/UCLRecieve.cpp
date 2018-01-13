//
// Created by fly on 11/1/17.
//
#include "UCLRecieve.h"

int s;
struct sockaddr_in serverAddr;
socklen_t len;
std::list<int> li;

void getConn() {
    while (1) {
        int conn = accept(s, (struct sockaddr *) &serverAddr, &len);
        li.push_back(conn);
//        printf("%d\n", conn);
    }
}

void getData() {
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    int count = 1;
    while (1) {
        std::list<int>::iterator it;
        for (it = li.begin(); it != li.end(); ++it) {
            fd_set rfds;
            FD_ZERO(&rfds);
            int maxfd = 0;
            int retval = 0;
            FD_SET(*it, &rfds);
            if (maxfd < *it) {
                maxfd = *it;
            }
            retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
            if (retval == -1) {
                printf("select error\n");
            } else if (retval == 0) {
                printf("not message\n");
            } else {
                char buf[10240];
                memset(buf, 0, sizeof(buf));
                int len = recv(*it, buf, sizeof(buf), 0);
                string str_ucl = string(len, '0');
                for (int i = 0; i < len; i++) {
                    str_ucl[i] = buf[i];
                }
                if (len > 0) {
                    printf("已收到第%d条UCL：", count++);
                    printPackString(str_ucl);
                    UCL ucl;
                    ucl.unpack(str_ucl);
                    ucl.showUCL();
                }
            }
        }
    }
}

void sendMess() {
    while (1) {
        char buf[1024];
        fgets(buf, sizeof(buf), stdin);
        std::list<int>::iterator it;
        for (it = li.begin(); it != li.end(); ++it) {
            send(*it, buf, sizeof(buf), 0);
        }
    }
}

void socketRecieve() {
    cout << "\n========== Server begin==========\n";
    //new socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IP);
    if (bind(s, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(s, 20) == -1) {
        perror("listen");
        exit(1);
    }
    len = sizeof(serverAddr);


    //thread : while ==>> accpet
    std::thread t(getConn);
    t.detach();
    //printf("done\n");
    //thread : input ==>> send
    std::thread t1(sendMess);
    t1.detach();
    //thread : recv ==>> show
    std::thread t2(getData);
    t2.detach();
    while (1);
}