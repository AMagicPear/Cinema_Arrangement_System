#include <iostream>
//包含基本结构体信息的头文件
#include "Arrangements.hpp"
#include "Basic Information.h"
#include "Audience Info.h"
#include "Admin Info.h"
//声明外部函数：欢迎和选择界面部分，详见文件Welcome.cpp
extern int PrintStartScreen_Choice();
#define DEBUG //定义Debug模式
#ifndef DEBUG
//主函数
int main() {
    //确定两个大分支中选择哪一个
    int user_Choice = PrintStartScreen_Choice();
    switch (user_Choice) {
        case 1:
            //进入观众大分支
            User::main();
            break;
        case 2:
            //进入管理员大分支
            Admin::main();
            break;
        default:
            printf("Error!");
    }
    return 0;
}
#else
#include <fstream>

//DEBUG模式的主函数

int main(){
    Halls halls;
    Hall hall1={{1,0,1,0,0,1,1,1,0},
                {0,0}};
    print_hall(hall1);

    return 0;
}

#endif