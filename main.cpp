//包含基本结构体信息的头文件
#include "Basic Information.hpp"
#include "Audience Info.hpp"
#include "Admin Info.hpp"
//声明外部函数：欢迎和选择界面部分，详见文件Welcome.c
extern "C" int PrintStartScreen_Choice();
//#define DEBUG //定义Debug模式
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
//    show_arrangements(load_arrangements(arrangements_json));

    return 0;
}

#endif