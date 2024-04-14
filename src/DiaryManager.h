#ifndef DIARYMANAGER_H
#define DIARYMANAGER_H

#include <vector>
#include "Diary.h"

class DiaryManager {
   private:
    std::vector<Diary> diaries;

   public:
    void addDiary(Diary diary);
    void deleteDiary(int index);
    std::vector<Diary> getAllDiaries();
};

#endif
