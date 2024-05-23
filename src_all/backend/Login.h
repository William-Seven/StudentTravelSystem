#include <string.h>
#include <iostream>
#include "include/mysql.h"
// using namespace std;

// 函数声明
bool isUsernameRegistered(MYSQL* conn, const std::string& username) {
    std::string query = "SELECT COUNT(*) FROM users WHERE username = '" + username + "'";

    if (mysql_query(conn, query.c_str())) {
        std::cout << "查询失败: " << mysql_error(conn) << std::endl;
        return false;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        std::cout << "获取查询结果失败: " << mysql_error(conn) << std::endl;
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);

    mysql_free_result(result);

    return (count > 0);
}

// 查找用户密码
bool retrievePassword(MYSQL* conn, const std::string& username) {
    // 构造 SQL 查询语句
    std::string query = "SELECT password FROM users WHERE username = '" + username + "'";

    // 执行查询
    if (mysql_query(conn, query.c_str())) {
        std::cout << "查询失败: " << mysql_error(conn) << std::endl;
        exit(1);
    }

    // 获取查询结果
    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        std::cout << "获取查询结果失败: " << mysql_error(conn) << std::endl;
        exit(1);
    }

    // 获取查询结果中的数据行
    MYSQL_ROW row = mysql_fetch_row(result);

    // 检查是否找到了对应用户名的密码
    if (row == NULL) {
        std::cout << "用户名不存在！";
        mysql_free_result(result);
        return false;
    }

    // 打印找回的密码
    std::cout << "用户名为 " << username << " 的密码是：" << row[0];

    // 释放查询结果内存
    mysql_free_result(result);

    return true;
}

// 函数定义：修改密码
bool changePassword(MYSQL* conn, const std::string& username, const std::string& oldPassword, const std::string& newPassword) {
    // 构造 SQL 查询语句
    std::string query = "UPDATE users SET password = '" + newPassword + "' WHERE username = '" + username + "' AND password = '" + oldPassword + "'";

    // 执行更新
    if (mysql_query(conn, query.c_str())) {
        std::cout << "密码修改失败: " << mysql_error(conn) << std::endl;
        exit(1);
    }

    // 检查是否有行受到影响
    if (mysql_affected_rows(conn) == 0) {
        // std::cout << "用户名或旧密码不正确" << std::endl;
        return false;
    }

    return true;
}

int Login(int mode, std::string user, std::string pass, std::string pass_new) {
    MYSQL my_sql;
    MYSQL_RES* res;  // 查询结果集
    MYSQL_ROW row;   // 记录结构体

    // 初始化数据库
    mysql_init(&my_sql);

    // 连接数据库
    if (!mysql_real_connect(&my_sql, "localhost", "root", "abc123", "test3", 3306, NULL, 0)) {
        std::cout << "连接数据库失败：" << mysql_error(&my_sql) << std::endl;
        exit(-1);
    }

    //=====欢迎使用学生游学系统！=====

    int index = mode;
    // 1. 注册 2. 登录 3. 忘记密码 4. 修改密码 5. 其余为退出

    switch (index) {
        case 1: {
            std::string sql = "SELECT * FROM users";

            std::string username = user;
            bool registered;

            do {
                // 调用函数查询用户名是否已被注册
                registered = isUsernameRegistered(&my_sql, username);
                if (registered)  // 用户名已被注册
                    return 0;
            } while (registered);

            // 用户名未被注册
            // 输入密码
            std::string reg_password = pass;

            sql = "INSERT INTO users(username, password) VALUES(\"" + username + "\", \"" + reg_password + "\")";

            if (mysql_query(&my_sql, sql.c_str()))  // 注册失败
                return 2;

            // 注册成功
            return 1;
        }
        case 2: {
            // 构建查询语句
            std::string sql = "SELECT * FROM users WHERE username = '" + user + "' AND password = '" + pass + "';";

            // 执行查询
            if (mysql_query(&my_sql, sql.c_str())) {
                // std::cout << "查询失败：" << mysql_error(&my_sql) << std::endl;
                mysql_close(&my_sql);
                return 0;
            }

            // 获取结果集
            res = mysql_store_result(&my_sql);
            if (!res) {
                // 没有该用户或查询结果集为空
                mysql_close(&my_sql);
                return 0;
            }

            // 遍历结果集
            while ((row = mysql_fetch_row(res))) {
                std::string username = row[0];  // 第一列为用户名
                std::string password = row[1];  // 第二列为密码
                if (username == user && password == pass) {
                    // 登录成功
                    mysql_free_result(res);
                    mysql_close(&my_sql);
                    return 1;
                }
            }

            // 账号或密码错误
            mysql_free_result(res);
            mysql_close(&my_sql);
            return 0;
        }
        case 3: {
            // 通过用户名找回密码
            std::string username = user;

            // 调用函数试图找回密码
            bool success = retrievePassword(&my_sql, username);
            if (!success) {
                // std::cout << "找回密码失败，用户名不存在或发生其它错误。" << std::endl;
                return 0;
            }

            return 1;
        }
        case 4: {
            std::string username, oldPassword, newPassword;
            username = user;
            oldPassword = pass;
            newPassword = pass_new;

            // 调用函数尝试修改密码
            bool success = changePassword(&my_sql, username, oldPassword, newPassword);
            if (success) {
                std::cout << "密码修改成功！";
            } else {
                std::cout << "密码修改失败，用户名或旧密码不正确";
            }

            return 1;
        }
        default: {
            std::cout << "已退出！" << std::endl;
            break;
        }
    }  // end of case

    mysql_close(&my_sql);
    return 0;
}
