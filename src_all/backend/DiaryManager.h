#ifndef DIARYMANAGER_H
#define DIARYMANAGER_H

#include <vector>
#include "Diary.h"

class DiaryManager {
   private:
    std::vector<Diary> diaries;

   public:
    void printAllDiaries();
    void addDiary(Diary diary);
    void getScore(int a, int b);
    void q_sort(int left, int right);
    void diarySearch(std::string search_title, std::string search_author, std::string search_destination, std::string search_content, int search_mode);
    void diaryDownload();
    void diaryUncompress(std::string path);
};

#endif
