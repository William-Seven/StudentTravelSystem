#include "Diary.h"
#include <iostream>

/*获取日记*/
Diary::Diary(std::string title, std::string authorID, std::string destination, std::string content) {
    this->title = title;
    this->authorID = authorID;
    this->destination = destination;
    this->content = content;
    this->popularity = 0;
    this->rating = 0;
    this->score = 0;
}

/*打印日记*/
void Diary::DiaryPrint() {
    std::cout << "Title: " << title << std::endl;
    std::cout << "AuthorID: " << authorID << std::endl;
    std::cout << "Destination: " << destination << std::endl;
    std::cout << "Content: " << content << std::endl;
    std::cout << "Popularity: " << popularity << std::endl;
    std::cout << "Rating: " << ((double)rating) / 10000 << std::endl;
    std::cout << std::endl;
}

/*获取nextval[t.length()]数组*/
void getnextval(std::string t, int nextval[]) {
    int j = 0, k = -1;
    int t_len = t.length();
    nextval[0] = -1;
    while (j < t_len)
        if (k == -1 || t[j] == t[k]) {
            j++;
            k++;
            if (t[j] != t[k])
                nextval[j] = k;
            else
                nextval[j] = nextval[k];
        } else
            k = nextval[k];
}

/*在字符串s中查找字符串t第一次出现的下标*/
bool Diary::kmp(std::string t, std::string s) {
    if (t == "-1")
        return 1;
    int line_limit = t.length();
    int nextval[line_limit];
    int i = 0, j = 0;
    int s_len = s.length(), t_len = t.length();
    getnextval(t, nextval);
    while (i < s_len && j < t_len)
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else
            j = nextval[j];
    if (j >= t_len)
        return true;
    else
        return false;
}