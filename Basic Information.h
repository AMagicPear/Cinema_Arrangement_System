//
// Created by AMagicPear on 2023/3/13.
//

#ifndef CINEMA_BASIC_INFORMATION_H
#define CINEMA_BASIC_INFORMATION_H

#include <utility>
#include <string>
#include <ctime>
#include <iomanip>
//#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "nlohmann/json.hpp"

//#define ARRANGE_NUM 10
//#define FILM_NUM 5
#define HALL_NUM 3

using namespace std;

//一部电影
class Film {
public:
    string name;        //名称
    string type;        //类型
    int time_during;  //持续时长（分钟）
    void set(string name_set, string type_set, int time_during_set);

    //构造函数
    Film(string name_set = "", string type_set = "", int time_during_set = 0) {
        name = name_set;
        type = type_set;
        time_during = time_during_set;
    }
};
//设置一部电影的参数函数
void Film::set(string name_set, string type_set, int time_during_set) {
    name = std::move(name_set);
    type = std::move(type_set);
    time_during = time_during_set;
}

//日期和时间格式
struct Date {
    int year;
    int month;
    int day;
    //设置Date为当前系统日期
    void set(const string &str) {
        if (str == "today") {
            time_t now = time(nullptr);
            tm *ltm = localtime(&now);
            year = 1900 + ltm->tm_year;
            month = 1 + ltm->tm_mon;
            day = ltm->tm_mday;
        } else {
            year = 0, month = 0, day = 0;
        }
    }
    //定义一个重载运算符<的函数，用来比较两个Date对象的大小
    bool operator<(const Date& d) const {
        // 如果当前对象的年份小于d的年份，就返回true
        if (year < d.year) {
            return true;
        }
            // 如果当前对象的年份等于d的年份，就比较它们的月份
        else if (year == d.year) {
            // 如果当前对象的月份小于d的月份，就返回true
            if (month < d.month) {
                return true;
            }
                // 如果当前对象的月份等于d的月份，就比较它们的日期
            else if (month == d.month) {
                // 如果当前对象的日期小于或等于d的日期，就返回true
                if (day <= d.day) {
                    return true;
                }
            }
        }
        // 其他情况都返回false
        return false;
    }
    //定义一个重载运算符==的函数，用来判断两个Date对象是否相等
    bool operator==(const Date& d) const{
        if(year==d.year&&month==d.month&&day==d.day) return true;
        else return false;
    }


    //设置Date为自定义日期
    void set(int year_set, int month_set, int day_set) {
        year = year_set;
        month = month_set;
        day = day_set;
    }

    void print() const {
        cout << year << "/" << month << "/" << day << endl;
    }

    //构造函数
    Date(int y = 0, int m = 0, int d = 0) {
        year = y;
        month = m;
        day = d;
    }
    Date(const string &str) {
        if (str == "today") {
            time_t now = time(nullptr);
            tm *ltm = localtime(&now);
            year = 1900 + ltm->tm_year;
            month = 1 + ltm->tm_mon;
            day = ltm->tm_mday;
        } else {
            year = 0, month = 0, day = 0;
        }
    }
};

struct Time {
    struct Date date;
    int hour;
    int minute;

    void print_accurate() const {
        //以"时:分"格式输出，时分均为两位数字
        cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute << endl;
    }

    void print_date() const {
        date.print();
    }

    //构造函数
    Time(Date d = Date(), int h = 0, int m = 0) {
        date = d;
        hour = h;
        minute = m;
    }
};

//一次排片
class Arrangement {
public:
    int hall_ID{};      //在几号厅
    Film film;          //排哪部片
    Time begin_time{};  //开始时间
    void set(int hall_ID_set, Film film_set, Time begin_time_set);

    //构造函数
    Arrangement(int hall_set = 0, Film film_set = Film(), Time begin_time_set = Time()) {
        hall_ID = hall_set;
        film = film_set;
        begin_time = begin_time_set;
    }
};

//设置一次排片的参数
void Arrangement::set(int hall_ID_set, Film film_set, Time begin_time_set) {
    film = std::move(film_set);
    hall_ID = hall_ID_set;
    begin_time = begin_time_set;
}

//影厅对象
class Hall {
private:
    //定义影厅座位的行和列数
    const static int row = 5;
    const static int col = 10;
public:
    //定义座位表，true为已被购买，false为空座
    bool seats[row][col] = {}; //座位表为二维数组
    void Show_Seats() {
        for (auto &seat: seats) {
            for (bool j: seat) {
                cout << j << " ";
            }
            cout << endl;
        }
    }

    //对一个影厅选座操作
    void Select_seat(int row_select, int col_select) {
        seats[row_select][col_select] = true;
    }
};

//一个座位位置
struct seat {
    int row;
    int col;
};

//一张票
class Ticket {
public:
    int ID{};
    Arrangement arrangement;
    struct seat seat{};
};

//基本信息初始化
//Film* film_list=new Film[FILM_NUM];
//vector<Film> film_list;
//auto* arrangement_list=new Arrangement[ARRANGE_NUM]{};
//vector<Arrangement> arrangement_list;
//auto *hall_list = new Hall[HALL_NUM];
#endif //CINEMA_BASIC_INFORMATION_H