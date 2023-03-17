//
// Created by AMagicPear on 2023/3/15.
//
//管理员界面
#ifndef CINEMACPP_ADMIN_INFO_H
#define CINEMACPP_ADMIN_INFO_H

#include <iostream>
#include <fstream>
#include <string>
#include "Arrangements.hpp"
//定义管理员密码
const std::string admin_password="ampc";

using namespace std;

class Admin {
public:
    static void Welcome_Admin() {
        cout << "====管理员====" << endl;
        string password_input;
        cout << "请输入管理员密码：";
        while (true) {
            cin >> password_input;
            if (password_input != admin_password) {
                printf("输入有误！重新输入：");
                continue;
            } else break;
        }
        cout << "管理员登录成功！" << endl;
    }

    static void main() {
        vector<Film> films = load_films("data/films.txt");
        vector<Arrangement> arrangements = load_arrangements("data/arrangements.json");
        cout << "【选项】[1]查看&编辑当前所有电影数据" << endl
             << "[2]查看当前所有的排片数据" << endl
             << "[3]进入排片系统" << endl
             << "选择一项功能：";
        int choice;
        cin >> choice;
        while (true) {
            if (choice == 1) {
                show_films(films);
                break;
            } else if (choice == 2) {
                show_arrangements(arrangements);
                break;
            } else if (choice == 3) {
                show_films(films);
                creat_arrangements(films);
                break;
            } else {
                cout << "输入有误！请输入1~3：";
            }
        }
    }
};
#endif //CINEMACPP_ADMIN_INFO_H