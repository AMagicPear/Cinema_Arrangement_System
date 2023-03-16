#include <iostream>
//包含基本结构体信息的头文件
#include "Basic Information.h"
#include "Audience Info.h"
#include "general_action.h"
//声明外部函数：欢迎和选择界面部分，详见文件Welcome.cpp
extern int PrintStartScreen_Choice();
extern void get_arrangements();

#define DEBUG //定义Debug模式
#ifndef DEBUG
//主函数
int main() {
    //确定两个大分支中选择哪一个
    int user_Choice = PrintStartScreen_Choice();
    switch (user_Choice) {
        case 1:
            //进入观众大分支
            Audience();
            break;
        case 2:
            //进入管理员大分支
            Administrator();
            break;
        default:
            printf("Error!");
    }
    return 0;
}
#else
#include <fstream>
//测试用
//DEBUG模式的主函数
int main(){
    //获取今日日期，存入today对象中
    Date today{};
    today.set("today");
//    get_arrangements(arrangement_list);
//    User_Main();
    Arrangement ar0={{"电影0","类型0",100},1,{today,11,10}};
    Film film1={"电影1","科幻",100};
    Film film2={"电影2","喜剧",90};
    film_list.push_back(film1);
    film_list.push_back(film2);
    Arrangement ar1={film1,1,{{2023,2,15},20,10}};
    Arrangement ar2={film1,2,{today,21,00}};
    arrangement_list.push_back(ar0);
    arrangement_list.push_back(ar1);
    arrangement_list.push_back(ar2);

    fstream file1;
    file1.open("data/arrangements.txt",ios::app);

//    cout<<ar1.film.name<<endl;
//    cout<<arrangement_list[0].film.name;
//    file1<<ar1.film.name<<endl;
//    file1<<arrangement_list[0].film.name;
    int num,ID;
    string str;

    cout<<"请输入影片号码：";
    cin>>num;
    cin>>ID;
    cin>>str;

    Arrangement ar={film_list[num],ID,{today,1,1}};

    cout<<"电影名称："<<ar.film.name<<endl;
    cout<<"类型："<<ar.film.type<<endl;
    cout<<"持续时间："<<ar.film.time_during<<endl;
    cout<<"影厅号"<<ar.hall_ID<<endl;
}

#endif