#include <iostream>
#include "Diary.h"
#include "DiaryManager.h"
#include "include/mysql.h"

void DiaryTest(int mode, std::string title, std::string author, std::string destination, std::string content, int sortWay) {
    DiaryManager diaryManager;
    if (mode == 0) {
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

        // 排序测试

        diaryManager.diarySearch(title, author, destination, content, sortWay);

        // 关闭数据库
        mysql_close(&my_sql);
    } else if (mode == 1) {
        // 下载
        diaryManager.diaryDownload();
    } else {
        diaryManager.diaryUncompress(title);
    }
}