//
// Created by fly on 9/19/17.
//
#include "dbHelper.h"

bool DBHelper::getConn() {
    mysql_init(&conn);
    return mysql_real_connect(&conn, HOST, USER_NAME, PASSWORD, DATABASE_NAME, 0, NULL, 0);
}

std::vector<std::vector<std::string>> DBHelper::getData(const std::string &imageName) {
    std::string sqlImgExist;  //用于判断数据库是否有传入图片的相关数据
    sqlImgExist = "SELECT COUNT(*) FROM ssd_detect_res WHERE imageName='" + imageName + "'";
    if (mysql_query(&conn, sqlImgExist.c_str())) {  //查询失败
        std::cout << "Error: qury data failed!";
        closeConn();
        assert(0);
    }
    MYSQL_ROW result_row; //按行返回的查询信息
    quryResult = mysql_store_result(&conn);
    if (quryResult) {
        result_row = mysql_fetch_row(quryResult);
        if (!strcmp(result_row[0], "0")) {  //数据库中没有输入图片的数据则抛出异常
            throw "NoImage!";
        }
    }

    std::string sqlHasDone;  //用于判断传入图片所对应的所有目标信息服务端是否已经写入完成
    sqlHasDone = "SELECT COUNT(*) FROM ssd_detect_res WHERE imageName='" + imageName + "' and hasDone=1";
    int hasDone = 0;
    while (!hasDone) {  //服务端数据未写入完成则循环等待,直至数据写入完成
        if (mysql_query(&conn, sqlHasDone.c_str())) {  //查询失败
            std::cout << "Error: qury data failed!";
            closeConn();
            assert(0);
        }
        quryResult = mysql_store_result(&conn);
        if (quryResult) {
            result_row = mysql_fetch_row(quryResult);
            hasDone = atoi(result_row[0]);
        }
        usleep(1000);
    }

    std::string sqlRes;  //查询图片所有识别数据的sql语句
    sqlRes = "SELECT hasObject,objectClass,localXMIN,localYMIN,localXMAX,localYMAX,"
                     "localYMAX,score FROM ssd_detect_res WHERE imageName='" + imageName + "'";
    std::vector<std::vector<std::string>> res;  //存储结果
    std::vector<std::string> item;  //存储查询到的一条数据
    int row, column;  //记录查询所返回的行数和列数
    if (mysql_query(&conn, sqlRes.c_str())) {  //查询失败
        std::cout << "Error: qury data failed!" << std::endl;
        closeConn();
        assert(0);
    }
    quryResult = mysql_store_result(&conn);
    if (quryResult) {
        column = mysql_num_fields(quryResult);
        row = mysql_num_rows(quryResult);
        for (int i = 0; i < row; i++) {
            result_row = mysql_fetch_row(quryResult);
            for (int j = 0; j < column; j++) {
                item.push_back((std::string) result_row[j]);
            }
            res.push_back(item);
            item.clear();
        }
    }
    return res;
}

bool DBHelper::createdbTable() {
    std::string sql = "CREATE TABLE IF NOT EXISTS " + TABLE_NAME + " (" +
                      "id INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY," +
                      "imageName VARCHAR(20) NOT NULL," +
                      "ucl TEXT NOT NULL," +
                      "uclSign TEXT NOT NULL," +
                      "uclKByte FLOAT DEFAULT 0.0," +
                      "uclTimeStamp VARCHAR(20) NOT NULL " +
                      ") ENGINE=InnoDB DEFAULT CHARSET=utf8";
    if (mysql_query(&conn, sql.c_str())) {
        std::cout << "Create table error " << mysql_errno(&conn) << "," << mysql_error(&conn) << std::endl;
        closeConn();
        assert(0);
        return false;
    }
    return true;
}

bool DBHelper::insert(const std::string &imageName, const std::string &ucl, const std::string &uclSign,
                      const uint32_t &uclByte, const std::string &uclTimeStamp) {

    std::string sql = "INSERT INTO " + TABLE_NAME + "(imageName,ucl,uclSign,uclKByte,uclTimeStamp) VALUES('"
                      + imageName + "','" + ucl + "','" + uclSign + "','" + std::to_string(uclByte / 1024.0)
                      + "','" + uclTimeStamp + "')";
    int res = mysql_query(&conn, sql.c_str());
    if (res) {
        std::cout << "Insert error " << mysql_errno(&conn) << "," << mysql_error(&conn) << std::endl;
        closeConn();
        assert(0);
        return false;
    }
    return true;
}

bool DBHelper::search(const std::string &imageName) {
    std::string sql = "SELECT COUNT(*) FROM " + TABLE_NAME +
                      " WHERE imageName='" + imageName + "'";
    if (mysql_query(&conn, sql.c_str())) {  //查询失败
        std::cout << "Error: search data failed!";
        closeConn();
        assert(0);
    }
    MYSQL_ROW result_row; //按行返回的查询信息
    quryResult = mysql_store_result(&conn);
    if (quryResult) {
        result_row = mysql_fetch_row(quryResult);
        if (!strcmp(result_row[0], "0")) {  //数据库中没有输入图片的数据
            return false;
        }
    }
    return true;
}

bool DBHelper::update(const std::string &imageName, const std::string &ucl, const std::string &uclSign,
                      const uint32_t &uclByte, const std::string &uclTimeStamp) {

    std::string sql = "UPDATE " + TABLE_NAME + " SET ucl='" + ucl + "',uclSign='"
                      + uclSign + "',uclKByte='" + std::to_string(uclByte / 1024.0)
                      + "',uclTimeStamp='" + uclTimeStamp + "' WHERE imageName='" + imageName + "';";
    int res = mysql_query(&conn, sql.c_str());
    if (res) {
        std::cout << "Update error " << mysql_errno(&conn) << "," << mysql_error(&conn) << std::endl;
        closeConn();
        assert(0);
        return false;
    }
    return true;
}

void DBHelper::closeConn() {
    mysql_free_result(quryResult);
    mysql_close(&conn);
    mysql_library_end();
}