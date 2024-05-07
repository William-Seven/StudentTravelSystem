#include "ViewManager.h"
#include <fstream>
#include <iostream>
#include <vector>

#define TEST_MAXSIZE 90

void get_nextval(std::string t, int nextval[]);
bool kmp(std::string t, std::string s);

/*获取景点数组*/
void ViewManager::getViews() {
    View temp;
    std::ifstream file("data1.txt");
    // for (int i = 0; i < TEST_MAXSIZE; i++) {
    // std::cin >> temp.LocationID >> temp.Name >> temp.Type >> temp.Popularity >> temp.Ratings;
    // views.push_back(temp);
    //}
    if (file.is_open()) {
        for (int i = 0; i < TEST_MAXSIZE && file >> temp.LocationID >> temp.Name >> temp.Type >> temp.Popularity >> temp.Ratings; ++i) {
            views.push_back(temp);
        }
        file.close();  // 关闭文件
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

/*排序输出*/
void ViewManager::Recommendation() {
    int mode;      // 0=popularity,1=ratings
    int object;    // 0=attraction,1=school,2=all
    int quantity;  // 0=top10,1=all;
    std::string search_string;
    // std::cin>>mode>>object>>quantity>>search_string;
    std::cout << "选择景区/高校/全部展示(0/1/2): ";
    std::cin >> object;
    std::cout << "选择热度/评分排序(0/1): ";  // 0=popularity,1=ratings
    std::cin >> mode;
    std::cout << "选择展示前十/全部(0/1): ";  // 0=top10,1=all;
    std::cin >> quantity;
    std::cout << "是否进行关键词搜索？(Y/N): ";
    std::string s;
    std::cin >> s;
    if (s == "Y" || s == "y")
        search_string = "山";
    else
        search_string = "-1";
    // mode = 1;
    // object = 2;
    // quantity = 0;
    // search_string = "大学";
    int i, j;
    if (mode == 0) {
        if (object == 0) {
            if (quantity == 0) {
                getScore(1, 0);
                q_sort(0, TEST_MAXSIZE);
                for (i = 0, j = 0; i < 10 && j < TEST_MAXSIZE; i++, j++) {
                    while (views[j].Type != "attraction" || !kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            } else if (quantity == 1) {
                getScore(1, 0);
                q_sort(0, TEST_MAXSIZE);
                for (j = 0; j < TEST_MAXSIZE; j++) {
                    while (views[j].Type != "attraction" || !kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            }
        } else if (object == 1) {
            if (quantity == 0) {
                getScore(1, 0);
                q_sort(0, TEST_MAXSIZE);
                for (i = 0, j = 0; i < 10 && j < TEST_MAXSIZE; i++, j++) {
                    while (views[j].Type != "school" || !kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            } else if (quantity == 1) {
                getScore(1, 0);
                q_sort(0, TEST_MAXSIZE);
                for (j = 0; j < TEST_MAXSIZE; j++) {
                    while (views[j].Type != "school" || !kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            }
        } else if (object == 2) {
            if (quantity == 0) {
                getScore(1, 0);
                q_sort(0, TEST_MAXSIZE);
                for (i = 0, j = 0; i < 10 && j < TEST_MAXSIZE; i++, j++) {
                    while (!kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            } else if (quantity == 1) {
                getScore(1, 0);
                q_sort(0, TEST_MAXSIZE);
                for (j = 0; j < TEST_MAXSIZE; j++) {
                    while (!kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            }
        }
    } else if (mode == 1) {
        if (object == 0) {
            if (quantity == 0) {
                getScore(0, 1);
                q_sort(0, TEST_MAXSIZE);
                for (i = 0, j = 0; i < 10 && j < TEST_MAXSIZE; i++, j++) {
                    while (views[j].Type != "attraction" || !kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            } else if (quantity == 1) {
                getScore(0, 1);
                q_sort(0, TEST_MAXSIZE);
                for (j = 0; j < TEST_MAXSIZE; j++) {
                    while (views[j].Type != "attraction" || !kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            }
        } else if (object == 1) {
            if (quantity == 0) {
                getScore(0, 1);
                q_sort(0, TEST_MAXSIZE);
                for (i = 0, j = 0; i < 10 && j < TEST_MAXSIZE; i++, j++) {
                    while (views[j].Type != "school" || !kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            } else if (quantity == 1) {
                getScore(0, 1);
                q_sort(0, TEST_MAXSIZE);
                for (j = 0; j < TEST_MAXSIZE; j++) {
                    while (views[j].Type != "school" || !kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            }
        } else if (object == 2) {
            if (quantity == 0) {
                getScore(0, 1);
                q_sort(0, TEST_MAXSIZE);
                for (i = 0, j = 0; i < 10 && j < TEST_MAXSIZE; i++, j++) {
                    while (!kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            } else if (quantity == 1) {
                getScore(0, 1);
                q_sort(0, TEST_MAXSIZE);
                for (j = 0; j < TEST_MAXSIZE; j++) {
                    while (!kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings / 10000 << std::endl;
                }
            }
        }
    }
}

/*获取综合评分*/
void ViewManager::getScore(int a, int b) {
    int popularity;
    int ratings;
    for (int i = 0; i < TEST_MAXSIZE; i++) {
        if (views[i].Popularity > MAX_POPULARITY && b != 0)
            popularity = 50000;
        else
            popularity = views[i].Popularity;
        ratings = views[i].Ratings;
        views[i].Score = a * popularity + b * ratings;  // 计算公式
    }
}

/*排序算法*/
void ViewManager::q_sort(int left, int right) {
    int p = views[(left + right) / 2].Score;
    int i = left;
    int j = right;
    while (i <= j) {
        while (views[i].Score > p)
            i++;
        while (views[j].Score < p)
            j--;
        if (i <= j) {
            std::swap(views[i], views[j]);
            i++;
            j--;
        }
    }
    if (j > left)
        q_sort(left, j);
    if (right > i)
        q_sort(i, right);
}

/*获取nextval[t.length()]数组*/
void get_nextval(std::string t, int nextval[]) {
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
bool kmp(std::string t, std::string s) {
    if (t == "-1")
        return 1;
    int line_limit = t.length();
    int nextval[line_limit];
    int i = 0, j = 0;
    int s_len = s.length(), t_len = t.length();
    get_nextval(t, nextval);
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