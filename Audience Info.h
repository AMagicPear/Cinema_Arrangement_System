//
// Created by AMagicPear on 2023/3/15.
//

#ifndef CINEMACPP_AUDIENCE_INFO_H
#define CINEMACPP_AUDIENCE_INFO_H
#define DEBUG
#define USER_NUM 100
#include <iostream>
#include <fstream>
#include <sstream>
#include "Basic Information.h"
using namespace std;
//定义用户
struct User {
    string ID;                   //用户名
    string password;             //密码
    Ticket ticket;               //持有的票
};
void User_Login();
void User_Register();
bool Check_pass(const string& ID_input,const string& password_input);
bool isID_exist(const string& ID_input);
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
        User_Login();
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
    while (true) {
        cout << "====注册====" << endl;
        cout << "用户名：";
        cin >> ID_input;
        if (isID_exist(ID_input)) {
            cout <<ID_input<<"已被注册，请重新输入用户名！" << endl;
            continue;
        }
        break;
    }
    cout<<"密码：";
    cin>>password_input;//此处可加重复确认密码功能
    ofstream accounts_file;
    accounts_file.open("accounts_file.txt",ios::app);//设置为向末尾追加
    accounts_file<<ID_input<<" "<<password_input<<endl; //将注册的ID和密码存入账户文件
    cout<<"注册成功！您的用户名是："<<ID_input<<endl;
}
//检查传入的ID是否已被注册，若是则返回true
bool isID_exist(const string& ID_input){
    //打开存储所有用户信息的accounts.txt文件
    fstream accounts_file;
    accounts_file.open("accounts_file.txt",std::ios::in);
    if(!accounts_file.is_open()){
        cerr<<"cannot open the accounts_file!";
        ::exit(0);
    }
    char* line= (char*) ::malloc(sizeof(char*)*USER_NUM);
    while (accounts_file.getline(line, sizeof(char*)*USER_NUM)){
        string get_name;
        std::stringstream word(line);
        word >> get_name;
        if(ID_input==get_name){
            ::free(line);
            return true;
        }
    }
    ::free(line);
    return false;
}
//用户登录
void User_Login(){
    //要求用户输入ID和密码并存储
    string ID_input,password_input;
    re_login:
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
    bool check_pass= Check_pass(ID_input,password_input);
    if (check_pass) {
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
    } else{
        cout<<"请重新输入："<<endl;
        goto re_login;
    }
}
//根据文件信息判断ID和密码是否正确
bool Check_pass(const string& ID_input,const string& password_input){
    //打开存储所有用户信息的accounts.txt文件
    fstream accounts_file;
    accounts_file.open("accounts_file.txt",std::ios::in);
    if(!accounts_file.is_open()){
        cerr<<"cannot open the accounts_file!";
        ::exit(0);
    }
    char* line= (char*) ::malloc(sizeof(char*)*100);
    while (accounts_file.getline(line, sizeof(char*)*100)){
        string get_name,get_password;
        std::stringstream word(line);
        word >> get_name>>get_password;
        if (ID_input == get_name) {
            if (password_input == get_password) {
                ::free(line);
                return true;
            } else{
                cout<<"密码错误！";
                return false;
            }
        }
    }
    cout<<"用户名不存在！";
    return false;
    ::free(line);
}
#endif //CINEMACPP_AUDIENCE_INFO_H