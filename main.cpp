#include <iostream>
//包含基本结构体信息的头文件
#include "Arrangements.hpp"
#include "Basic Information.h"
#include "Audience Info.h"
#include "Admin Info.h"
#include "halls&tickets.h"
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
            User::main();
            break;
        case 2:
            //进入管理员大分支
            Admin::main();
            break;
        default:
            printf("Error!");
    }
    return 0;
}
#else
//DEBUG模式的主函数

int main(){
//    Halls halls;
//    Hall_seats hall1= create_hall(4,4);
//    hall1[2][3]=true;
//    print_hall_seats(hall1);
//    halls.push_back(hall1);
//    save_halls(halls,"data/halls.dat");
//    halls= load_halls("data/halls.dat");
//    print_hall_seats(halls[0]);
    Arrangements ars(load_arrangements(arrangements_json));
    show_arrangements(ars);
    int choice;

    cout<<"请选择购买哪一场（输入序号）：";
    cin>>choice;

    return 0;
}

#endif