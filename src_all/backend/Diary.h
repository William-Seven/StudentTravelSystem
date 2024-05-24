#ifndef DIARY_H
#define DIARY_H

#define MAX_POPULARITY 50000

#include <string>

class Diary {
   public:
    std::string title;
    // std::string authorID;
    std::string author;
    std::string destination;
    std::string content;
    int popularity;
    int rating;
    int score;

    Diary(std::string title, std::string author, std::string destination, std::string content);

    void DiaryPrint();
    void DiaryWriteintoFile();
};

#endif
