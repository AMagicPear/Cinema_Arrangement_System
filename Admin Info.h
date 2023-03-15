//
// Created by AMagicPear on 2023/3/15.
//
//管理员界面
#ifndef CINEMACPP_ADMIN_INFO_H
#define CINEMACPP_ADMIN_INFO_H

#include<iostream>

using namespace std;
struct Administrator {
    string ID;
    string password;
};

void menu_administrator(string ID) {
    printf("【系统】欢迎%s！！！\n", ID.c_str());
    printf("*************************************************\n");
    printf("**********          欢迎！！！          **********\n");
    printf("**********          1————增加影片       **********\n");
    printf("**********          2————显示影片       **********\n");
    printf("**********          3————查找影片       **********\n");
    printf("**********          4————修改影片       **********\n");
    printf("**********          5————删除影片       **********\n");
    printf("**********          6————排序影片       **********\n");
    printf("**********          0————退出           **********\n");
    printf("**************************************************\n");
    printf("【系统】请您选择您要实现的功能（数字）：");
}

#endif //CINEMACPP_ADMIN_INFO_H


//管理员功能
