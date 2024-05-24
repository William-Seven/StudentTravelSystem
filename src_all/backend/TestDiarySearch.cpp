#include "DiarySearchDown.h"

int main(int argc, char* argv[]) {
    std::string title = argv[1];
    std::string author = argv[2];
    std::string dest = argv[3];
    std::string content = argv[4];
    DiaryTest(0, title, author, dest, content, std::stoi(argv[5]));

    return 0;
}