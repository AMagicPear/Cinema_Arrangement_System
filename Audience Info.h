//
// Created by AMagicPear on 2023/3/15.
//

#ifndef CINEMACPP_AUDIENCE_INFO_H
#define CINEMACPP_AUDIENCE_INFO_H

#include <iostream>
#include <fstream>
#include "Basic Information.h"
using namespace std;
struct User {
    string ID;                   //用户名
    string password;             //密码
};
#define USER_NUM 100
//打印用户菜单界面
void Menu_user(const string &ID) {
    printf("【系统】欢迎%s！！！\n", ID.c_str());
    printf("***************************************************\n");
    printf("**********         欢迎光临！         *************\n");
    printf("**********         1-- 购票           *************\n");
    printf("**********         2-- 取票           ************\n");
    printf("**********         3-- 退票           *************\n");
    printf("**********         0-- 退出           *************\n");
    printf("【系统】请您选择您要实现的功能（数字）：");
}
//要求用户选择注册或登录，并返回值
int Welcome_User(){
    printf("1. 注册\t 2. 登录\n");
    int user_Choice=0;
    while (true) {
        scanf("%d",&user_Choice);
        if(!(user_Choice==1||user_Choice==2)){
            printf("输入有误！请输入1或2以选择：");
            continue;
        }else break;
    }
    return user_Choice;
}
//用户注册
void User_Register(){
    cout<<"User_Register";
}
//用户主函数
void User_Fun(){
    //判断注册和登录分支
    int user_Choice=Welcome_User();
    //进入注册分支
    if(user_Choice==1){
        User_Register();
    }
    //进入登录分支
    else if(user_Choice==2){
        //要求用户输入ID和密码并存储
        string ID_input,password_input;
        cout<<"====登录===="<<endl;
        cout<<"用户名：";
        cin>>ID_input;
        cout<<"密码：";
        cin>>password_input;
        //打开存储所有用户信息的accounts.txt文件
        ifstream accounts("accounts.txt");
        User user_list[USER_NUM];
        //将accounts.txt文件内的用户信息存入一个对象数组中
        int member=0;
        while (accounts>>user_list[member].ID>>user_list[member].password)
            member++;
        //遍历对象数组
        for (;member>0; member--) {
            //查找是否有输入的ID
            if (user_list[member].ID==ID_input){
                //查找对应ID的密码是否正确
                if(user_list[member].password==password_input){
                    //进入用户菜单界面
                    Menu_user(ID_input);
                }
            }
            cout<<"用户名错误或无此用户，请检查输入的用户名";
            //待增加功能：跳转到注册
        }
    }
}
void Buy_Ticket(){
    //从文件中读取当前所有排片并存储在film_list中
    //可参考上面登录的写法，film_list已经在Basic Information中定义好了可以直接用
    

}
void Get_Tikcet(){

}

#endif //CINEMACPP_AUDIENCE_INFO_H