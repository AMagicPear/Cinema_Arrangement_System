//
// Created by AMagicPear on 2023/3/15.
//

#ifndef CINEMACPP_AUDIENCE_INFO_H
#define CINEMACPP_AUDIENCE_INFO_H
#define DEBUG
#include <iostream>
#include <fstream>
#include "Basic Information.h"
using namespace std;
//定义用户
struct User {
    string ID;                   //用户名
    string password;             //密码
    Ticket ticket;               //持有的票
};
#define USER_NUM 100
User user_list[USER_NUM];
void User_Login();
void User_Register();
bool Check_pass(const string& ID_input,const string& password_input);
//打印用户菜单界面
void Menu_user(const string &ID) {
    printf("【系统】欢迎%s！！！\n", ID.c_str());
    printf("***************************************************\n");
    printf("**********         欢迎光临！         *************\n");
    printf("**********         1-- 购票           *************\n");
    printf("**********         2-- 退票           *************\n");
    printf("**********         0-- 退出           *************\n");
    printf("【系统】请您选择您要实现的功能（数字）：");
}
//要求用户选择注册或登录，并返回值
int Welcome_User(){
    cout<<"====用户===="<<endl;
    printf("1. 注册\t 2. 登录\n");
    int user_Choice=0;
    while (true) {
        cin>>user_Choice;
        if(!(user_Choice==1||user_Choice==2)){
            printf("输入有误！请输入1或2以选择：");
            continue;
        }else break;
    }
    return user_Choice;
}
//用户主函数
void User_Main(){
    //判断注册和登录分支
    int user_Choice=Welcome_User();
    //进入注册分支
    if(user_Choice==1){
        User_Register();
    }
    //进入登录分支
    else if(user_Choice==2){
        User_Login();
    }
}
void Buy_Ticket(){
    //从文件中读取当前所有排片并存储在film_list中
    //可参考上面登录的写法，film_list已经在Basic Information中定义好了可以直接用

}
void Return_Tikcet(){
    ;
}
//用户注册
void User_Register(){
    //要求用户输入ID和密码并存储
    string ID_input,password_input;
    //打开存储所有用户信息的accounts.txt文件
    fstream accounts_file;
    accounts_file.open("accounts_file.txt");
    re_register:
    cout<<"====注册===="<<endl;
    cout<<"用户名：";
    cin>>ID_input;
    //将accounts.txt文件内的用户信息存入一个对象数组中
    int member=0;
    while (accounts_file >> user_list[member].ID >> user_list[member].password)
        member++;
    //遍历对象数组
    for (;member>0; member--) {
        //查找是否有输入的ID
        if (user_list[member].ID==ID_input){
            cout<<"用户ID已存在！请重新输入。";
            goto re_register;
        }
    }
    cout<<"密码：";
    cin>>password_input;//此处可加重复确认密码功能

}
//用户登录
void User_Login(){
    //要求用户输入ID和密码并存储
    string ID_input,password_input;
    cout<<"====登录===="<<endl;
    cout<<"用户名：";
    cin>>ID_input;
#ifdef DEBUG
    //！！调试使用：如果用户名为"1"直接跳过登录
    if(ID_input=="1"){
        Menu_user("AMagicPear【！调试模式！】");
        return;
    }
#endif
    cout<<"密码：";
    cin>>password_input;
    if (Check_pass(ID_input, password_input)) {
        Menu_user(ID_input);
        int user_Choice = ::getchar();
        switch (user_Choice) {
            case 1:
                Buy_Ticket();
                break;
            case 2:
                Return_Tikcet();
                break;
            default:
                cout<<"已退出！";
                ::exit(1);
        }
    }
}
//根据文件信息判断ID和密码是否正确
bool Check_pass(const string& ID_input,const string& password_input){
    //打开存储所有用户信息的accounts.txt文件
    ifstream accounts("accounts.txt");
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
                return true;
            }return false;
        }return false;
    }return false;
}
#endif //CINEMACPP_AUDIENCE_INFO_H