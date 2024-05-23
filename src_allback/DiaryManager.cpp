#include "DiaryManager.h"
#include "Kmp.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "FileCompress.h"

void DiaryManager::printAllDiaries() {
    for (Diary diary : diaries) {
        diary.DiaryPrint();
    }
}

void DiaryManager::addDiary(Diary diary) {
    diaries.push_back(diary);
}

void DiaryManager::deleteDiary(int index) {
    if (index >= 0 && index < diaries.size()) {
        diaries.erase(diaries.begin() + index);
    }
}

int DiaryManager::getIndex(int mode, std::string t) {
    int i = 0;
    for (std::vector<Diary>::iterator iter = diaries.begin(); iter != diaries.end(); iter++, i++) {
        if (mode == 0)  // 按title搜索
        {
            if (kmp(t, iter->title))
                return i;
        } else if (mode == 1)  // 按authorID搜索
        {
            if (kmp(t, iter->authorID))
                return i;
        } else if (mode == 2)  // 按author搜索
        {
            if (kmp(t, iter->author))
                return i;
        } else if (mode == 3)  // 按destination搜索
        {
            if (kmp(t, iter->destination))
                return i;
        } else if (mode == 4)  // 按content搜索
        {
            if (kmp(t, iter->content))
                return i;
        }
    }
    return -1;
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

void DiaryManager::diarySearch(std::string search_title, std::string search_authorID, std::string search_author, std::string search_destination, std::string search_content, int search_mode) {
    if (search_title == "-1")
        search_title = "";
    if (search_authorID == "-1")
        search_authorID = "";
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
        if (kmp(search_title, diary.title) && kmp(search_authorID, diary.authorID) && kmp(search_author, diary.author) && kmp(search_destination, diary.destination) && kmp(search_content, diary.content)) {
            diary.DiaryPrint();
            diary.DiaryWriteintoFile();
        }
    }
}

void DiaryManager::diaryDownload() {
    std::string file = "D:\\Diarytemp.txt";
    FileCompress cps;
    cps.Compress(file.c_str());
    std::cout << "压缩成功！" << std::endl;
    std::cout << "是否需要解压？(y/n)" << std::endl;
    char c;
    std::cin >> c;
    if (c == 'y') {
        std::cout << "请输入下载的Diarytemp.zlx文件路径: (例：D:\\Diarytemp.zlx)" << std::endl;
        std::cin >> file;
        FileCompress cps;
        cps.UnCompress(file.c_str());
        std::cout << "解压成功！" << std::endl;
    } else if (c == 'n') {
        std::cout << "已取消解压！" << std::endl;
    }
}
