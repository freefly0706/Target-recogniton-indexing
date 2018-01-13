# -*- coding: UTF-8 -*-
import MySQLdb


class DBHelper(object):
    def __init__(self):
        # 数据库名称
        self.__DATABASE_NAME = 'ssd'
        self.__HOST = 'localhost'
        # 端口号
        self.__PORT = 3306
        # 用户名称
        self.__USER_NAME = 'root'
        # 数据库密码
        self.__PASSWORD = '12345'
        # 获取数据库连接
        self.__conn = None

    # 获取连接
    def get_conn(self):
        self.__conn = MySQLdb.connect(host=self.__HOST, port=self.__PORT, user=self.__USER_NAME,
                                      passwd=self.__PASSWORD)

    # 关闭连接
    def close_conn(self):
        if self.__conn is not None:
            self.__conn.close()

    # 关闭游标
    def close_cursor(self, cursor):
        if cursor is not None:
            cursor.close()

    # 创建数据库
    def create_database(self):
        sql = 'CREATE DATABASE IF NOT EXISTS ' + self.__DATABASE_NAME
        cursor = self.__conn.cursor()
        try:
            cursor.execute(sql)
            self.__conn.commit()
        except MySQLdb.Error:
            print 'Error: failed to create database!'
        self.__conn.select_db(self.__DATABASE_NAME)

    def create_table(self):
        sql = '''
            CREATE TABLE IF NOT EXISTS ssd_detect_res (
            id INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
            imageName VARCHAR(20) NOT NULL,
            hasObject BOOLEAN DEFAULT TRUE ,
            objectClass VARCHAR(20) NOT NULL DEFAULT 'unknown',
            localXMIN INTEGER DEFAULT 0,
            localYMIN INTEGER DEFAULT 0,
            localXMAX INTEGER DEFAULT 0,
            localYMAX INTEGER DEFAULT 0,
            score FLOAT DEFAULT 0.0,
            hasDone BOOLEAN DEFAULT FALSE 
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8
            '''
        image_byte = '''
                    CREATE TABLE IF NOT EXISTS image_byte (
                    id INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
                    imageName VARCHAR(20) NOT NULL,
                    imageByte FLOAT DEFAULT 0.0
                    ) ENGINE=InnoDB DEFAULT CHARSET=utf8
                    '''
        cursor = self.__conn.cursor()
        result = False
        try:
            result = cursor.execute(sql)
            self.__conn.commit()
        except MySQLdb.Error:
            print 'Error: failed to create table!'
        try:
            result = cursor.execute(image_byte)
            self.__conn.commit()
        except MySQLdb.Error:
            print 'Error: failed to create table!'
        self.close_cursor(cursor)
        return result

    def insert_data(self, *args):
        if len(args) == 2:
            sql = '''INSERT INTO image_byte(imageName, imageByte)
                                 VALUES ('%s','%f')''' % (args[0], args[1])
        elif len(args) == 7:
            sql = '''INSERT INTO ssd_detect_res(imageName, objectClass, 
                     localXMIN, localYMIN, localXMAX, localYMAX, score)
                     VALUES ('%s','%s','%d','%d','%d','%d','%f')''' % (
                args[0], args[1], args[2], args[3], args[4], args[5], args[6])
        elif len(args) == 8:
            sql = '''INSERT INTO ssd_detect_res(imageName, objectClass, 
                     localXMIN, localYMIN, localXMAX, localYMAX, score, hasDone)
                     VALUES ('%s','%s','%d','%d','%d','%d','%f','%d')''' % (
                args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7])
        else:
            sql = '''INSERT INTO ssd_detect_res(imageName, hasObject, hasDone)
                     VALUES ('%s','%d','%d')''' % (args[0], args[1], args[2])
        cursor = self.__conn.cursor()
        result = False
        try:
            result = cursor.execute(sql)
            self.__conn.commit()
        except MySQLdb.Error:
            self.__conn.rollback()
        self.close_cursor(cursor)
        return result

    def delete_data(self, imageName, table_name):
        sql = "DELETE FROM " + table_name + " WHERE imageName = '%s'" % (imageName)
        cursor = self.__conn.cursor()
        result = False
        try:
            result = cursor.execute(sql)
            self.__conn.commit()
        except MySQLdb.Error:
            self.__conn.rollback()
            print 'Error: delete data failed!'
        self.close_cursor(cursor)
        return result

    def search(self, imageName, table_name):
        num = 0
        sql = "SELECT COUNT(*) FROM " + table_name + " WHERE imageName = '%s'" % (imageName)
        cursor = self.__conn.cursor()
        try:
            cursor.execute(sql)
            num = cursor.fetchone()[0]
        except MySQLdb.Error:
            print 'Error: search failed!'
        return num


if __name__ == '__main__':
    db = DBHelper()
    db.get_conn()
    db.create_database()
    db.create_table()
    db.close_conn()
