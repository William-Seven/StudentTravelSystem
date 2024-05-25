#include "DiarySearchDown.h"

int main(int argc, char* argv[]) {
    std::string title = argv[1];
    std::string author = argv[2];
    std::string dest = argv[3];
    std::string content = argv[4];
    DiaryTest(5, title, author, dest, content, -1);

    return 0;
}