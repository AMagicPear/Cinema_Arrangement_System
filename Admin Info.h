//
// Created by AMagicPear on 2023/3/15.
//
//管理员界面
#ifndef CINEMACPP_ADMIN_INFO_H
#define CINEMACPP_ADMIN_INFO_H

#include <iostream>
#include <fstream>
#include <string>
//定义管理员密码
const std::string admin_password="AD";

using namespace std;
struct Administrator {
    string ID;
    string password;
};

void Menu_administrator(const string& ID) {
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

void Admin_Login(){
    string password_input;
    cout<<"请输入管理员密码：";
    while (true) {
        cin>>password_input;
        if(password_input!=admin_password){
            printf("输入有误！重新输入：");
            continue;
        }else break;
    }
}

#endif //CINEMACPP_ADMIN_INFO_H


//管理员功能
