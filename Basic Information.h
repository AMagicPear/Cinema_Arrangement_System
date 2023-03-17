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
typedef vector<Film> Films;
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
typedef vector<Arrangement> Arrangements;

//影厅对象
class Hall {
public:
    int rows; // 影厅座位行数
    int cols; // 影厅座位列数
    bool** seats; // 座位表

    // 构造函数，初始化影厅座位表
    Hall(int r, int c) : rows(r), cols(c) {
        seats = new bool*[rows];
        for (int i = 0; i < rows; i++) {
            seats[i] = new bool[cols];
            for (int j = 0; j < cols; j++) {
                seats[i][j] = false;
            }
        }
    }

    // 析构函数，释放内存
    ~Hall() {
        for (int i = 0; i < rows; i++) {
            delete[] seats[i];
        }
        delete[] seats;
    }
    void printSeats() { // 定义成员函数
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (seats[i][j]) { // 直接访问类的成员变量
                    std::cout << "▣ ";
                } else {
                    std::cout << "□ ";
                }
            }
            std::cout << "\n";
        }
    }
};
// 将影厅对象数组存储在本地文件中的函数
void saveHallsToFile(Hall* halls[], int numHalls, std::string filename) {
    std::ofstream file(filename);
    if (file.is_open()) { // 如果文件打开成功
        for (int h = 0; h < numHalls; h++) { // 遍历影厅对象数组
            Hall* hall = halls[h];
            file << hall->rows << "," << hall->cols;
            for (int i = 0; i < hall->rows; i++) { // 遍历座位表，将其存储在文件中
                for (int j = 0; j < hall->cols; j++) {
                    file << "," << hall->seats[i][j];
                }
            }
            file << "\n";
        }
        file.close(); // 关闭文件
    } else {
        std::cout << "Unable to open file";
    }
}

//一张票
class Ticket {
public:
    int ID{};
    Arrangement arrangement;
    struct seat {
        int row;
        int col;
    };
};

//基本信息初始化
//Film* film_list=new Film[FILM_NUM];
//vector<Film> film_list;
//auto* arrangement_list=new Arrangement[ARRANGE_NUM]{};
//vector<Arrangement> arrangement_list;
//auto *hall_list = new Hall[HALL_NUM];
#define films_txt "data/films.txt"
#define films_json "data/films.json"
#define arrangements_json "data/arrangements.json"
#endif //CINEMA_BASIC_INFORMATION_H