#include <iostream>
#include <string>
#include "Graph.h"
#include "LocationQuery.h"
#include "TestDiary.h"
#include "TestQuery.h"
#include "TestRecommend.h"
#include "TestRouter.h"

int main() {
    // 用户登录
    std::string user_name;
    std::cout << "请输入用户名：";
    std::cin >> user_name;
    std::cout << "欢迎使用学生游学系统，用户名：" << user_name << std::endl;

    // 测试各模块
    int op = 0;
    while (op != 5) {
        std::cout << "请选择要测试的功能：\n";
        std::cout << "1. 推荐模块\n";
        std::cout << "2. 路线规划模块\n";
        std::cout << "3. 场所查询模块\n";
        std::cout << "4. 日记模块\n";
        std::cout << "5. 退出\n";
        std::cin >> op;
        switch (op) {
            case 1:
                RecommendTest();
                // std::cout << "11111";
                break;
            case 2:
                RouterTest();
                break;
            case 3:
                QueryTest();
                break;
            case 4:
                DiaryTest();
                break;
            case 5:
                std::cout << "感谢使用学生游学系统，再见！" << std::endl;
                return 0;
            default:
                std::cout << "输入有误，请重新输入！" << std::endl;
                break;
        }
    }

    return 0;
}
