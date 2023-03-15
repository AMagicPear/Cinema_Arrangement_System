#include <iostream>
//包含基本结构体信息的头文件
#include "Basic Information.h"
#include "Audience Info.h"
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
    //测试用的排片：
    film_list[0]={"电影0","类型0",0};
    film_list[1]={"电影1","类型1",1};
    arrangement_list[0].set(film_list[0],0,{today,0,0});
    arrangement_list[1].set(film_list[1],1,{today,1,1});
    //观众页面
    User_Main();

}

#endif