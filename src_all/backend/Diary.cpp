#include "Diary.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "Kmp.h"

/*获取日记*/
Diary::Diary(std::string title, std::string author, std::string destination, std::string content) {
    this->title = title;
    this->author = author;
    this->destination = destination;
    this->content = content;
    this->popularity = 0;
    this->rating = 0;
    this->score = 0;
}

/*打印日记*/
void Diary::DiaryPrint() {
    std::cout << title << " " << author << " " << destination << "\n";
    std::cout << content << "\n";
    std::cout << std::fixed << std::setprecision(1);
    std::cout << popularity << " " << ((double)rating) / 10000 << "\n";
}

void Diary::DiaryWriteintoFile() {
    // 打开文件进行追加写入
    std::string filepath = "D:\\Diarytemp.txt";
    std::ofstream file(filepath.c_str(), std::ios::app);
    if (!file.is_open()) {
        std::cerr << "无法打开文件！" << std::endl;
        return;
    }

    // 将相同的内容写入文件
    file << "标题: " << title << '\n';
    file << "作者: " << author << '\n';
    file << "游学地点: " << destination << '\n';
    file << "日记内容: " << content << '\n';
    file << "热度: " << popularity << '\n';
    file << "评分: " << ((double)rating) / 10000 << '\n';
    file << "\n";  // 添加一个空行作为条目之间的分隔

    // 关闭文件
    file.close();
}