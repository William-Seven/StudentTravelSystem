#include "Login.h"

int main(int argc, char* argv[]) {
    // 用户注册
    if (Login(1, argv[1], argv[2]) == 1) {
        std::cout << "注册成功";
    } else if (Login(1, argv[1], argv[2], argv[3]) == 0) {
        // 用户名被注册
        std::cout << "用户名已被注册";
    } else {
        // 注册失败
        std::cout << "注册失败";
        return 1;
    }

    return 0;
}