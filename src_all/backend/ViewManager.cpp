#include "ViewManager.h"
#include <mysql.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "Kmp.h"

#define TEST_MAXSIZE 318

/*获取景点数组*/
void ViewManager::getViews() {
    MYSQL my_sql;
    MYSQL_RES* res;  // 查询结果集
    MYSQL_ROW row;   // 记录结构体

    // 初始化数据库
    mysql_init(&my_sql);

    // 连接数据库
    if (!mysql_real_connect(&my_sql, "localhost", "root", "abc123", "test3", 3306, NULL, 0)) {
        std::cout << "错误原因：" << mysql_error(&my_sql) << "\n";
        std::cout << "连接数据库失败" << "\n";
        exit(-1);
    }

    // 查询nodes
    mysql_query(&my_sql, "select * from views;");

    // 获取结果集
    int count = 0;
    res = mysql_store_result(&my_sql);
    while (row = mysql_fetch_row(res)) {
        View temp;
        temp.LocationID = std::stoi(row[0]);
        temp.Name = row[1];
        temp.Type = row[2];
        temp.Popularity = std::stoi(row[3]);
        temp.Ratings = std::stod(row[4]);
        views.push_back(temp);
    }
}

/*排序输出*/
void ViewManager::Recommendation(int obj, int quan, int mo, std::string s_s) {
    int mode = mo;        // 0=popularity,1=ratings,2=default
    int object = obj;     // 0=attraction,1=school,2=all
    int quantity = quan;  // 0=top10,1=all;
    std::string search_string = s_s;

    int i, j;
    if (mode == 0) {
        if (object == 0) {
            if (quantity == 0) {
                getScore(1, 0);
                std::vector<View> filteredViews = selectSort(TEST_MAXSIZE, object, search_string);
                for (i = 0; i < 10 && i < filteredViews.size(); i++) {
                    std::cout << filteredViews[i].LocationID << " " << filteredViews[i].Name << " " << filteredViews[i].Type << " " << filteredViews[i].Popularity << " " << filteredViews[i].Ratings << "\n";
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
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings << "\n";
                }
            }
        } else if (object == 1) {
            if (quantity == 0) {
                getScore(1, 0);
                std::vector<View> filteredViews = selectSort(TEST_MAXSIZE, object, search_string);
                for (i = 0; i < 10 && i < filteredViews.size(); i++) {
                    std::cout << filteredViews[i].LocationID << " " << filteredViews[i].Name << " " << filteredViews[i].Type << " " << filteredViews[i].Popularity << " " << filteredViews[i].Ratings << "\n";
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
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings << "\n";
                }
            }
        } else if (object == 2) {
            if (quantity == 0) {
                getScore(1, 0);
                std::vector<View> filteredViews = selectSort(TEST_MAXSIZE, object, search_string);
                for (i = 0; i < 10 && i < filteredViews.size(); i++) {
                    std::cout << filteredViews[i].LocationID << " " << filteredViews[i].Name << " " << filteredViews[i].Type << " " << filteredViews[i].Popularity << " " << filteredViews[i].Ratings << "\n";
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
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings << "\n";
                }
            }
        }
    } else if (mode == 1) {
        if (object == 0) {
            if (quantity == 0) {
                getScore(0, 1);
                std::vector<View> filteredViews = selectSort(TEST_MAXSIZE, object, search_string);
                for (i = 0; i < 10 && i < filteredViews.size(); i++) {
                    std::cout << filteredViews[i].LocationID << " " << filteredViews[i].Name << " " << filteredViews[i].Type << " " << filteredViews[i].Popularity << " " << filteredViews[i].Ratings << "\n";
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
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings << "\n";
                }
            }
        } else if (object == 1) {
            if (quantity == 0) {
                getScore(0, 1);
                std::vector<View> filteredViews = selectSort(TEST_MAXSIZE, object, search_string);
                for (i = 0; i < 10 && i < filteredViews.size(); i++) {
                    std::cout << filteredViews[i].LocationID << " " << filteredViews[i].Name << " " << filteredViews[i].Type << " " << filteredViews[i].Popularity << " " << filteredViews[i].Ratings << "\n";
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
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings << "\n";
                }
            }
        } else if (object == 2) {
            if (quantity == 0) {
                getScore(0, 1);
                std::vector<View> filteredViews = selectSort(TEST_MAXSIZE, object, search_string);
                for (i = 0; i < 10 && i < filteredViews.size(); i++) {
                    std::cout << filteredViews[i].LocationID << " " << filteredViews[i].Name << " " << filteredViews[i].Type << " " << filteredViews[i].Popularity << " " << filteredViews[i].Ratings << "\n";
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
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings << "\n";
                }
            }
        } else if (object == 2) {
            if (quantity == 0) {
                getScore(1, 0);
                std::vector<View> filteredViews = selectSort(TEST_MAXSIZE, object, search_string);
                for (i = 0; i < 10 && i < filteredViews.size(); i++) {
                    std::cout << filteredViews[i].LocationID << " " << filteredViews[i].Name << " " << filteredViews[i].Type << " " << filteredViews[i].Popularity << " " << filteredViews[i].Ratings << "\n";
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
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings << "\n";
                }
            }
        }
    } else if (mode == 2) {
        if (object == 0) {
            if (quantity == 0) {
                getScore(3, 7);
                std::vector<View> filteredViews = selectSort(TEST_MAXSIZE, object, search_string);
                for (i = 0; i < 10 && i < filteredViews.size(); i++) {
                    std::cout << filteredViews[i].LocationID << " " << filteredViews[i].Name << " " << filteredViews[i].Type << " " << filteredViews[i].Popularity << " " << filteredViews[i].Ratings << "\n";
                }
            } else if (quantity == 1) {
                getScore(3, 7);
                q_sort(0, TEST_MAXSIZE);
                for (j = 0; j < TEST_MAXSIZE; j++) {
                    while (views[j].Type != "attraction" || !kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings << "\n";
                }
            }
        } else if (object == 1) {
            if (quantity == 0) {
                getScore(3, 7);
                std::vector<View> filteredViews = selectSort(TEST_MAXSIZE, object, search_string);
                for (i = 0; i < 10 && i < filteredViews.size(); i++) {
                    std::cout << filteredViews[i].LocationID << " " << filteredViews[i].Name << " " << filteredViews[i].Type << " " << filteredViews[i].Popularity << " " << filteredViews[i].Ratings << "\n";
                }
            } else if (quantity == 1) {
                getScore(3, 7);
                q_sort(0, TEST_MAXSIZE);
                for (j = 0; j < TEST_MAXSIZE; j++) {
                    while (views[j].Type != "school" || !kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings << "\n";
                }
            }
        } else if (object == 2) {
            if (quantity == 0) {
                getScore(3, 7);
                std::vector<View> filteredViews = selectSort(TEST_MAXSIZE, object, search_string);
                for (i = 0; i < filteredViews.size(); i++) {
                    std::cout << filteredViews[i].LocationID << " " << filteredViews[i].Name << " " << filteredViews[i].Type << " " << filteredViews[i].Popularity << " " << filteredViews[i].Ratings << "\n";
                }
            } else if (quantity == 1) {
                getScore(3, 7);
                q_sort(0, TEST_MAXSIZE);
                for (j = 0; j < TEST_MAXSIZE; j++) {
                    while (!kmp(search_string, views[j].Name)) {
                        j++;
                        if (j >= TEST_MAXSIZE)
                            break;
                    }
                    if (j >= TEST_MAXSIZE)
                        break;
                    std::cout << views[j].LocationID << " " << views[j].Name << " " << views[j].Type << " " << views[j].Popularity << " " << views[j].Ratings << "\n";
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
        ratings = (int)(views[i].Ratings * 1000);
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

// 选择排序，实现非全排列展示前十个
std::vector<View> ViewManager::selectSort(int length, int object, std::string search_string) {
    std::vector<View> filteredViews;
    if (object == 0) {
        for (int i = 0; i < length; i++)
            if (views[i].Type == "attraction" && kmp(search_string, views[i].Name))
                filteredViews.push_back(views[i]);
    } else if (object == 1) {
        for (int i = 0; i < length; i++)
            if (views[i].Type == "school" && kmp(search_string, views[i].Name))
                filteredViews.push_back(views[i]);
    } else if (object == 2) {
        for (int i = 0; i < length; i++)
            if (kmp(search_string, views[i].Name))
                filteredViews.push_back(views[i]);
    }
    int index;
    for (int i = 0; i < filteredViews.size() && i < 10; i++) {
        index = i;
        for (int j = i + 1; j < filteredViews.size(); j++) {
            if (filteredViews[j].Score > filteredViews[index].Score)
                index = j;
        }
        std::swap(filteredViews[i], filteredViews[index]);
    }
    return filteredViews;
}