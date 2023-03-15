#include <iostream>
//包含基本结构体信息的头文件
#include "Basic Information.h"
#include "Audience Info.h"
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
void Show_Arrangement(const Arrangement&);
void Show_All_Arrangements(Arrangement*);
#include <fstream>
//测试用
//初始化
Film* film_list=new Film[FILM_NUM];
auto* arrangement_list=new Arrangement[ARRANGE_NUM];
Hall* hall_list=new Hall[3];
//主函数
int main(){
    //获取今日日期，存入today对象中
    Date today{};
    today.set("today");
    //测试用的排片：
    film_list[0]={"电影0","类型0",0};
    film_list[1]={"电影1","类型1",1};
    arrangement_list[0].set(film_list[0],0,{today,0,0});
    arrangement_list[1].set(film_list[1],1,{today,1,1});
    //观众页面
    User_Fun();
}
//输出当前的所有排片
void Show_All_Arrangements(Arrangement* list){
    cout<<"影片名称\t类型\t时长\t影厅号\t开始时间"<<endl;
    Film film;
    for (int i = 0; i < 2; ++i) {
        film=list[i].film;
        cout<<film.name<<"\t"<<film.type<<"\t"<<film.time_during<<"\t"<<(list+i)->hall_ID<<"\t";
        list[i].begin_time.print_accurate();
    }
}
#endif