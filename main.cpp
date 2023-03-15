#include <iostream>
//包含基本结构体信息的头文件
#include "Basic Information.h"
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
int main(){
    Film* film_list=new Film[FILM_NUM];
    film_list[0].set("电影1","科幻",173);
    auto* arrangement_list=new Arrangement[ARRANGE_NUM];
    Date date1={2023, 3, 3};
    date1.set("today");
    arrangement_list[0].set(film_list[0],1,{date1, 12, 12});
    arrangement_list[1].set({"电影2","奇幻",112},3,{date1,11,1});
    Show_All_Arrangements(arrangement_list);
    Hall hall;
    for (auto & i : hall.seats) {
        for (int j : i)
            cout << noboolalpha << *(i + j) << " ";
        cout<<endl;
    }
//    Film film[]
}
/*
//输出一部影片的名称、类型、时长、影厅号
void Show_Arrangement(const Arrangement& arrangement){
    cout<<"影片名称："<<arrangement.film.name<<endl
        <<"影片类型："<<arrangement.film.type<<endl
        <<"影片时长："<<arrangement.film.time_during<<" min"<<endl
        <<"影厅号："<<arrangement.hall_ID<<endl;
}
//循环输出当前的所有排片
void Show_All_Arrangements(Arrangement* list){
    for(int i=0;i<=1;i++)
        Show_Arrangement(list[i]);
}*/
//输出当前的所有排片
void Show_All_Arrangements(Arrangement* list){
    cout<<"影片名称\t类型\t时长\t影厅号"<<endl;
    Film film;
//    for(Arrangement i : list){
    for (int i = 0; i < 2; ++i) {
        film=list[i].film;
        cout<<film.name<<"\t"<<film.type<<"\t"<<film.time_during<<"\t"<<(list+i)->hall_ID<<"\t";
        list[i].begin_time.print_accurate();
    }
}
#endif