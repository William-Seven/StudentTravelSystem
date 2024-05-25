#include "DiarySearchDown.h"

int main(int argc, char* argv[]) {
    std::string content = argv[1];
    int newrate = std::stoi(argv[2]);
    DiaryTest(4, "", "", "", content, newrate);

    return 0;
}