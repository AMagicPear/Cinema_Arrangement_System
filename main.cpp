#include <iostream>
//包含基本结构体信息的头文件
#include "Arrangements.hpp"
#include "Basic Information.h"
#include "Audience Info.h"
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
const string& file_arrangements="data/arrangements.json";
int main(){
    Date today;
    today.set("today");
    Film film("Deep","sci",100);
    Arrangement ar(1,film,{today,10,00});
    Arrangement ar2(10,film,{{today.year,today.month,today.day},8,10});
    vector<Arrangement> arrangements;
    arrangements.push_back(ar);
    arrangements.push_back(ar2);
    sort_arrangements(arrangements);
    save_arrangements(arrangements,file_arrangements);
    show_arrangements(load_arrangements(file_arrangements));
    return 0;
}

#endif