#include <iostream>
#include "Diary.h"
#include "DiaryManager.h"

void DiaryTest() {
    DiaryManager diaryManager;

    Diary diary1("HomeDisire", "666", "北京邮电大学", "I want to go back to shenzhen!");
    Diary diary2("NoFunAnyMore", "250", "北京邮电大学", "Here is not fun!");
    Diary diary3("ShitWeather", "555", "北京首都机场", "My plane was cancelled because of the fxxking weather!");
    Diary diary4("SoooooooTired", "555", "北京首都机场", "I want to SLEEP!!!!!!!!!!!!!!!!!");
    diary1.popularity = 12000;
    diary1.rating = 15000;
    diary2.popularity = 13000;
    diary2.rating = 14000;
    diary3.popularity = 20000;
    diary3.rating = 50000;
    diary4.popularity = 30000;
    diary4.rating = 40000;

    diaryManager.addDiary(diary1);
    diaryManager.addDiary(diary2);
    diaryManager.addDiary(diary3);
    diaryManager.addDiary(diary4);

    // 排序测试
    diaryManager.diarySearch("-1", "666", "-1", "北京邮电大", "-1", 0);  // 日记标题，日记作者ID，日记作者名，日记评测对象，日记内容，排序方式
}