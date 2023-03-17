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
