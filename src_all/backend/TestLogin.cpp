#include "Login.h"

int main(int argc, char* argv[]) {
    // 用户登录
    if (Login(2, argv[1], argv[2], argv[3]) == 1) {
        std::cout << "登录成功";
    } else {
        std::cout << "账号或密码错误";
    }

    return 0;
}