//
// Created by fly on 9/19/17.
//

#ifndef UCL_CPP_DBHELPER_H
#define UCL_CPP_DBHELPER_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <mysql/mysql.h>
#include <vector>
#include <cassert>
#include <cmath>

class DBHelper {
private:
    char *DATABASE_NAME = "ssd";
    char *HOST = "localhost";
    char *USER_NAME = "root";
    char *PASSWORD = "12345";
    std::string TABLE_NAME = "ucl_bt";
    MYSQL_RES *quryResult = NULL;
    MYSQL conn;
public:
    bool getConn();

    void closeConn();

    bool createdbTable();

    bool insert(const std::string &imageName, const std::string &ucl, const std::string &uclSign,
                const uint32_t &uclByte, const std::string &uclTimeStamp);

    bool search(const std::string &imageName);

    bool update(const std::string &imageName, const std::string &ucl, const std::string &uclSign,
                const uint32_t &uclByte, const std::string &uclTimeStamp);

    std::vector<std::vector<std::string>> getData(const std::string &imageName);
};

#endif //UCL_CPP_DBHELPER_H
