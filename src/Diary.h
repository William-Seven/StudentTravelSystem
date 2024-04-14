#ifndef DIARY_H
#define DIARY_H

#include <string>

class Diary {
   public:
    std::string title;
    std::string content;
    int popularity;
    int rating;

    Diary(std::string title, std::string content);
};

#endif
