#include "DiaryManager.h"

void DiaryManager::addDiary(Diary diary) {
    diaries.push_back(diary);
}

void DiaryManager::deleteDiary(int index) {
    if (index >= 0 && index < diaries.size()) {
        diaries.erase(diaries.begin() + index);
    }
}

std::vector<Diary> DiaryManager::getAllDiaries() {
    return diaries;
}
