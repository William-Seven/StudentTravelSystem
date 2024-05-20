#include <iostream>
#include "Diary.h"
#include "DiaryManager.h"
#include "include/mysql.h"

void DiaryTest() {
    DiaryManager diaryManager;
    /*
        Diary diary1("HomeDisire", "2022211", "北京邮电大学Beijing University of Posts and Telecommunications", "I want to go back to shenzhen!");
        diary1.popularity = 12000;
        diary1.rating = 25000;
        diaryManager.addDiary(diary1);

        Diary diary2("NoFunAnyMore", "2023211", "北京邮电大学Beijing University of Posts and Telecommunications", "Here is not fun!");
        diary2.popularity = 13000;
        diary2.rating = 34000;
        diaryManager.addDiary(diary2);

        Diary diary3("ShitWeather", "2022211", "北京首都机场Beijing Capital International Airport", "My plane was cancelled because of the fxxking weather!");
        diary3.popularity = 20000;
        diary3.rating = 50000;
        diaryManager.addDiary(diary3);

        Diary diary4("SoooooooTired", "2021211", "北京首都机场Beijing Capital International Airport", "I want to SLEEP!!!!!!!!!!!!!!!!!");
        diary4.popularity = 30000;
        diary4.rating = 40000;
        diaryManager.addDiary(diary4);

        Diary positiveDiary("FeelingGreat", "2022211", "深圳Shenzhen", "Enjoying the sunny weather!");
        positiveDiary.popularity = 5000;
        positiveDiary.rating = 46000;
        diaryManager.addDiary(positiveDiary);

        Diary negativeDiary("BadDay", "2020211", "上海Shanghai", "Everything went wrong today!");
        negativeDiary.popularity = 3000;
        negativeDiary.rating = 12000;
        diaryManager.addDiary(negativeDiary);

        Diary neutralDiary("DailyRoutine", "2022211", "北京Beijing", "Just another ordinary day.");
        neutralDiary.popularity = 8000;
        neutralDiary.rating = 37000;
        diaryManager.addDiary(neutralDiary);

        Diary shortLocationDiary("WeekendGetaway", "2023211", "江苏Jiangsu", "Enjoying the beautiful sights of the city of love!");
        shortLocationDiary.popularity = 7000;
        shortLocationDiary.rating = 48000;
        diaryManager.addDiary(shortLocationDiary);

        Diary viralDiary("InternetSensation", "2019211", "Seoul", "My diary went viral overnight!");
        viralDiary.popularity = 100000;
        viralDiary.rating = 30000;
        diaryManager.addDiary(viralDiary);
    */

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
    // diaryManager.diarySearch("-1", "-1", "-1", "北京", "-1", 0);  // 日记标题，日记作者ID，日记作者名，日记评测对象，日记内容，排序方式
    std::string title, ID, location, content;
    int sortWay;
    std::cout << "输入搜索关键词：（-1表示默认）" << std::endl;
    std::cout << "1. 日记标题：";
    std::cin >> title;
    std::cout << "2. 日记作者ID：";
    std::cin >> ID;
    std::cout << "3. 日记评测对象：";
    std::cin >> location;
    std::cout << "4. 日记内容：";
    std::cin >> content;
    std::cout << "选择排序方式（0表示按热度排序，1表示按评分排序）：";
    std::cin >> sortWay;

    diaryManager.diarySearch(title, ID, "-1", location, content, sortWay);

    std::cout << "是否需要下载？(y/n)" << std::endl;
    std::string download;
    std::cin >> download;
    if (download == "y") {
        diaryManager.diaryDownload();
    }

    // 关闭数据库
    mysql_close(&my_sql);
}