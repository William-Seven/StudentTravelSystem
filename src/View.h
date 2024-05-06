#include <string>
#include "Tag.h"

#define MAXSIZE 100
#define MAX_POPULARITY 50000

class View
{
public:
    int LocationID;               // 地标ID
    std::string Name;          // 名字
    std::string Type;          // 分开景区和学校
    int OpenTime;         // 开放时间
    int CloseTime;        // 关闭时间
    Tag tag;     // 对应的喜好标签
    int Popularity;                  // 游学热度
    int Ratings;                   // 评分（0~5分）
    int Score;                     //综合评分
    int Bulidings[MAXSIZE][MAXSIZE]; // 二维矩阵，存建筑ID
    int TicketPrice; // 门票价格

};