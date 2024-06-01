#include "DiaryManager.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "FileCompress.h"
#include "Kmp.h"

void DiaryManager::printAllDiaries() {
    for (Diary diary : diaries) {
        diary.DiaryPrint();
    }
}

void DiaryManager::addDiary(Diary diary) {
    diaries.push_back(diary);
}

/*获取综合评分*/
void DiaryManager::getScore(int a, int b) {
    int popularity;
    int ratings;
    for (Diary& diary : diaries) {
        if (diary.popularity > MAX_POPULARITY && b != 0)
            popularity = 50000;
        else
            popularity = diary.popularity;
        ratings = diary.rating;
        diary.score = a * popularity + b * ratings;  // 计算公式
    }
}

/*排序算法*/
void DiaryManager::q_sort(int left, int right) {
    int p = diaries[(left + right) / 2].score;
    int i = left;
    int j = right;
    while (i <= j) {
        while (diaries[i].score > p)
            i++;
        while (diaries[j].score < p)
            j--;
        if (i <= j) {
            std::swap(diaries[i], diaries[j]);
            i++;
            j--;
        }
    }
    if (j > left)
        q_sort(left, j);
    if (right > i)
        q_sort(i, right);
}

void DiaryManager::diarySearch(std::string search_title, std::string search_author, std::string search_destination, std::string search_content, int search_mode) {
    if (search_title == "-1")
        search_title = "";
    if (search_author == "-1")
        search_author = "";
    if (search_destination == "-1")
        search_destination = "";
    if (search_content == "-1")
        search_content = "";
    int a;
    int b;
    if (search_mode == 0)  // 按popularity
    {
        a = 1;
        b = 0;
    } else if (search_mode == 1)  // 按rating
    {
        a = 0;
        b = 1;
    }
    getScore(a, b);
    q_sort(0, diaries.size() - 1);

    // 清空下载缓存文件
    std::string filepath = "D:\\Diarytemp.txt";
    std::ofstream file(filepath.c_str());
    if (!file.is_open()) {
        std::cerr << "无法打开缓存文件！" << std::endl;
    }
    file.close();

    // 匹配操作
    for (Diary diary : diaries) {
        if (kmp(search_title, diary.title) && kmp(search_author, diary.author) && kmp(search_destination, diary.destination) && kmp(search_content, diary.content)) {
            diary.DiaryPrint();
            diary.DiaryWriteintoFile();
        }
    }
}

void DiaryManager::diaryDownload() {
    std::string file = "D:\\Diarytemp.txt";
    FileCompress cps;
    cps.Compress(file.c_str());
}

// 文件解压
void DiaryManager::diaryUncompress(std::string path) {
    FileCompress cps;
    cps.UnCompress(path.c_str());
}

// 热度自增
int DiaryManager::up_popularity(std::string content) {
    for (Diary diary : diaries) {
        if (kmp(content, diary.content)) {
            diary.popularity += 10;
            return diary.popularity;
        }
    }
    return -1;
}

// 日记评分
int DiaryManager::update_rate(std::string content, int new_rating) {
    for (Diary diary : diaries) {
        if (kmp(content, diary.content)) {
            diary.rating = (diary.rating + new_rating) / 2;
            return diary.rating;
        }
    }
    return -1;
}
