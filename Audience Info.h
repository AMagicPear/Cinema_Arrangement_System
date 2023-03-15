//
// Created by AMagicPear on 2023/3/15.
//

#ifndef CINEMACPP_AUDIENCE_INFO_H
#define CINEMACPP_AUDIENCE_INFO_H
#include <iostream>
using namespace std;
struct User 
{
    string ID;                   //用户名
    string password;             //密码 

};
//用户界面
void menu_user(string ID)
{
    printf("【系统】欢迎%s！！！\n",ID.c_str());
    printf("***************************************************");
    printf("**********         欢迎光临！         *************");
    printf("**********         1-- 购票           *************");
    printf("**********         2-- 取票           *************");
    printf("**********         3-- 退票           *************");
    printf("**********         0-- 退出           *************");
    printf("【系统】请您选择您要实现的功能（数字）：");
 
}

#endif //CINEMACPP_AUDIENCE_INFO_H
