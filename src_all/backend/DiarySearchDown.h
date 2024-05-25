#include <iostream>
#include "Diary.h"
#include "DiaryManager.h"
#include "include/mysql.h"

void DiaryTest(int mode, std::string title, std::string author, std::string destination, std::string content, int sortWay) {
    DiaryManager diaryManager;

    MYSQL my_sql;
    MYSQL_RES* res;  // 查询结果集
    MYSQL_ROW row;   // 记录结构体

    // 初始化数据库
    mysql_init(&my_sql);

    // 连接数据库
    if (!mysql_real_connect(&my_sql, "localhost", "root", "abc123", "test3", 3306, NULL, 0)) {
        std::cout << "错误原因：" << mysql_error(&my_sql) << std::endl;
        std::cout << "连接数据库失败" << std::endl;
        exit(-1);
    }

    // 查询nodes
    mysql_query(&my_sql, "select * from diary;");

    // 获取结果集
    res = mysql_store_result(&my_sql);
    while (row = mysql_fetch_row(res)) {
        Diary temp(row[0], row[1], row[2], row[3]);
        // temp.title = row[0];
        // temp.authorID = row[1];
        // temp.destination = row[2];
        // temp.content = row[3];
        temp.popularity = std::stoi(row[4]);
        temp.rating = std::stoi(row[5]);
        diaryManager.addDiary(temp);
    }

    if (mode == 0) {
        // 排序测试
        diaryManager.diarySearch(title, author, destination, content, sortWay);
    } else if (mode == 1) {
        // 下载
        diaryManager.diaryDownload();
    } else if (mode == 2) {
        diaryManager.diaryUncompress(title);
    } else if (mode == 3) {
        int newpopularity = diaryManager.up_popularity(content);
        if (newpopularity != -1) {
            std::string newpopularity_str = std::to_string(newpopularity);
            std::string query = "UPDATE diary SET popularity = " + newpopularity_str + " WHERE content = '" + content + "'";
            mysql_query(&my_sql, query.c_str());
            std::cout << newpopularity;
        }
    } else if (mode == 4) {
        int newrating = diaryManager.update_rate(content, sortWay);
        if (newrating != -1) {
            std::string newrating_str = std::to_string(newrating);
            std::string query = "UPDATE diary SET rating = " + newrating_str + " WHERE content = '" + content + "'";
            mysql_query(&my_sql, query.c_str());
            std::cout << newrating;
        }
    } else {
        // 写日记到数据库
        std::string query = "INSERT INTO diary (title, authorID, destination, content, popularity, rating) VALUES ('" + title + "', '" + author + "', '" + destination + "', '" + content + "', 5000, 40000)";
        mysql_query(&my_sql, query.c_str());
        std::cout << "写入成功\n";
    }

    // 关闭数据库
    mysql_close(&my_sql);
}