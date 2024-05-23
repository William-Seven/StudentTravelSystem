#include <iostream>
#include "ViewManager.h"

ViewManager views;

int main(int argc, char* argv[]) {
    views.getViews();
    views.Recommendation(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]), argv[4]);
}