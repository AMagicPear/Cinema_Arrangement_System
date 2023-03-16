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
//    string password;             //密码
    Ticket ticket;               //持有的票
    static int Welcome_User();
    static void userMenu(const string& ID_input);
    static string regi();
    static string login();
    void Buy_Ticket();
};
void User::Buy_Ticket(){
    //从文件中读取当前所有排片并存储在film_list中
    //可参考上面登录的写法，film_list已经在Basic Information中定义好了可以直接用

}

bool isID_exist(const string&,const string&);

//打印用户菜单界面
void User::userMenu(const string& ID_input) {
    printf("【系统】欢迎%s！！！\n", ID_input.c_str());
    printf("***************************************************\n");
    printf("**********         欢迎光临！         *************\n");
    printf("**********         1-- 购票           *************\n");
    printf("**********         2-- 退票           *************\n");
    printf("**********         0-- 退出           *************\n");
    printf("【系统】请您选择您要实现的功能（数字）：");
}
//要求用户选择注册或登录，并返回值
int User::Welcome_User(){
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
void User_Main() {
    string userID{};
    re_choose_main:
    //判断注册和登录分支
    int user_Choice = User::Welcome_User();
    switch (user_Choice) {
        case 1: //进入注册分支
            userID = User::regi();
        case 2: //进入登录分支
        {
            if(user_Choice==2) userID = User::login();
            User::userMenu(userID);
            User user{};
            user.ID=userID;
            int user_Choice_menu;
            cin>>user_Choice_menu;
        }
            break;
        default:
            cerr<<"请输入1或2！"<<endl;
            goto re_choose_main;
    }
}

// 注册函数，注册成功后调用
string User::regi() {
    string username; // 用户名
    string password; // 密码
    while (true) {
        cout<<"====注册===="<<endl;
        cout << "请输入用户名：";
        cin >> username;
        if (isID_exist(username,"data/userinfo.txt")) {
            cout <<username<<"已被注册，请重新输入用户名！" << endl;
            continue;
        }
        break;
    }
    cout << "请输入密码：";
    cin >> password;
    // 打开用户信息文件
    ofstream outfile("data/userinfo.txt", ios::app);
    if (!outfile) {
        cerr << "无法打开文件" << endl;
        exit(1);
    }
    // 写入用户名和密码，用空格分隔
    outfile << username << " " << password << endl;
    // 关闭文件
    outfile.close();
    cout <<username<< "注册成功！" << endl;
    return login();
}

// 登录函数，返回登录成功的用户名，如果失败则返回空字符串
string User::login() {
    string username; // 用户名
    string password; // 密码
    string line;     // 文件中的一行
    cout<<"====登录===="<<endl;
    cout << "请输入用户名：";
    cin >> username;

    // 打开用户信息文件
    ifstream infile("data/userinfo.txt");
    if (!infile) {
        cerr << "无法打开文件" << endl;
        exit(1);
    }
    // 逐行读取文件内容
    while (getline(infile, line)) {
        std::stringstream word(line);
        string user,pass;
        word>>user>>pass;
        if (user == username)                // 如果找到匹配的用户名，则比对密码是否正确
        {
            cout << "请输入密码：";
            cin >> password;
            if (pass == password)            // 如果密码正确，则返回该用户名，并关闭文件
            {
                cout << "登录成功！" << endl;
                infile.close();
                return user;
            } else                             // 如果密码错误，则提示用户选择重新输入或注册，并关闭文件
            {
                cout << "密码错误！请选择：" << endl;
                cout << "[1]重新输入 [2]注册账号 [3]退出程序" << endl;
                int choice;
                cin >> choice;
                infile.close();
                switch (choice) {
                    case 1:
                        return login();
                        break;   // 重新调用登录函数
                    case 2:
                        User::regi();
                        break;       // 调用注册函数
                    case 3:
                        exit(0);
                        break;              // 退出程序
                    default:
                        return "";
                        break;           // 返回空字符串
                }
            }
        }
    }
    // 如果没有找到匹配的用户名，则提示用户选择重新输入或注册，并关闭文件
    infile.close();

    cout << "用户名不存在！请选择：" << endl;
    cout << "[1]重新输入 [2]注册账号 [3]退出程序" << endl;
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            return login();
            break;   // 重新调用登录函数
        case 2:
            User::regi();
            break;       // 调用注册函数
        case 3:
            exit(0);
            break;              // 退出程序
        default:
            return "";
            break;           //返回空字符串
    }
    return "";
}

void Return_Tikcet(){
    ;
}

//检查传入的ID是否已被注册，若是则返回true
bool isID_exist(const string& ID_input,const string& filename){
    //打开存储所有用户信息的accounts.txt文件
    fstream accounts_file;
    accounts_file.open(filename,std::ios::in);
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
            accounts_file.close();
            return true;
        }
    }
    ::free(line);
    accounts_file.close();
    return false;
}

#endif //CINEMACPP_AUDIENCE_INFO_H