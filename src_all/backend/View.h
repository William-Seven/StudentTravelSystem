#include <string>

#define MAX_POPULARITY 50000

class View {
   public:
    int LocationID;    // 地标ID
    std::string Name;  // 名字
    std::string Type;  // 分开景区和学校
    int OpenTime;      // 开放时间
    int CloseTime;     // 关闭时间
    int Popularity;    // 游学热度
    double Ratings;    // 评分（0~5分）
    int Score;         // 综合评分
    int TicketPrice;   // 门票价格
};