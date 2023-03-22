//包含基本结构体信息的头文件
#include "Basic Information.hpp"
#include "Audience Info.hpp"
#include "Admin Info.hpp"

//声明外部函数：欢迎和选择界面部分，详见文件Welcome.c
extern int main_menu();
//#define DEBUG //定义Debug模式
#ifndef DEBUG

//主函数
int main() {
    rewind_arrangements();
    //确定两个大分支中选择哪一个
    restart:
    int user_choice = main_menu();
    switch (user_choice) {
        case 1:
            //进入观众大分支
            User::main();
            break;
        case 2:
            //进入管理员大分支
            Admin::check();
            Admin::main();
            break;
        case 0:
            exit(1);
        default:
            printf("请输入1-3：");
            goto restart;
    }
    return 0;
}

#else
int main(){
//    show_arrangements(load_arrangements(arrangements_json,seats_folder));
    show_arrangements(load_arrangements(ar_old_json,""));
    return 0;
}

#endif