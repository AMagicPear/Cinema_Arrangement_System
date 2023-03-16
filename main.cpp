#include <iostream>
//包含基本结构体信息的头文件
#include "Basic Information.h"
#include "Audience Info.h"
#include "general_action.h"
//声明外部函数：欢迎和选择界面部分，详见文件Welcome.cpp
extern int PrintStartScreen_Choice();
extern void get_arrangements();

#define DEBUG //定义Debug模式
#ifndef DEBUG
//主函数
int main() {
    //确定两个大分支中选择哪一个
    int user_Choice = PrintStartScreen_Choice();
    switch (user_Choice) {
        case 1:
            //进入观众大分支
            Audience();
            break;
        case 2:
            //进入管理员大分支
            Administrator();
            break;
        default:
            printf("Error!");
    }
    return 0;
}
#else
#include <fstream>
//测试用
//DEBUG模式的主函数
int main(){
    //获取今日日期，存入today对象中
    Date today{};
    today.set("today");
//    get_arrangements(arrangement_list);
//    User_Main();
    //
}

#endif