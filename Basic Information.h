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

// 定义Hall类型为bool类型的二维vector
typedef vector<vector<bool>> Hall;
typedef vector<vector<vector<bool>>> Halls;
// 定义一个打印Hall座位表的成员函数
void print_hall(const Hall& hall) {
    // 遍历每一行
    for (const auto& row : hall) {
        // 遍历每一列
        for (const auto& seat : row) {
            // 如果座位为true，打印'▣'
            if (seat) {
                cout << "▣";
            }
                // 否则，打印'□'
            else {
                cout << "□";
            }
        }
        // 换行
        cout << "\n";
    }
}

// 定义一个把vector<Hall>存入本地文件的函数
void save_halls(const vector<Hall>& halls, const string& filename) {
    // 打开文件，使用二进制模式和输出模式
    ofstream file(filename, ios::binary | ios::out);
    // 如果文件打开失败，抛出异常
    if (!file.is_open()) {
        throw runtime_error("Failed to open file");
    }
    // 遍历每个Hall对象
    for (const auto& hall : halls) {
        // 获取Hall对象的行数和列数
        size_t rows = hall.size();
        size_t cols = hall.empty() ? 0 : hall[0].size();
        // 写入行数和列数到文件中，使用sizeof运算符获取字节数
        file.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
        file.write(reinterpret_cast<const char*>(&cols), sizeof(cols));
        // 遍历每一行
        for (const auto& row : hall) {
            // 创建一个char数组，大小为cols * sizeof(bool)
            char buffer[cols * sizeof(bool)];
            // 使用std::copy把每一行的数据复制到char数组中
            std::copy(row.begin(), row.end(), buffer);
            // 写入char数组到文件中
            file.write(buffer, cols * sizeof(bool));
        }
    }
    // 关闭文件
    file.close();
}
// 定义一个读取本地文件并返回vector<Hall>的函数
vector<Hall> load_halls(const string& filename) {
    // 创建一个空的vector<Hall>对象
    vector<Hall> halls;
    // 打开文件，使用二进制模式和输入模式
    ifstream file(filename, ios::binary | ios::in);
    // 如果文件打开失败，抛出异常
    if (!file.is_open()) {
        throw runtime_error("Failed to open file");
    }
    // 循环读取文件直到结束
    while (!file.eof()) {
        // 创建一个空的Hall对象
        Hall hall;
        // 声明两个变量用来存储行数和列数
        size_t rows, cols;
        // 尝试从文件中读取行数和列数，如果失败或者没有数据，则跳出循环
        if (!file.read(reinterpret_cast<char*>(&rows), sizeof(rows)) ||
            !file.read(reinterpret_cast<char*>(&cols), sizeof(cols))) {
            break;
        }
        // 调整Hall对象的大小为rows x cols，并初始化为false
        hall.resize(rows, vector<bool>(cols, false));
        // 遍历每一行
        for (auto& row : hall) {
            // 创建一个char数组，大小为cols * sizeof(bool)
            char buffer[cols * sizeof(bool)];
            // 尝试从文件中读取char数组，如果失败，则跳出循环
            if (!file.read(buffer, cols * sizeof(bool))) {
                break;
            }
            // 使用std::copy把char数组复制到每一行中
            std::copy(buffer, buffer + cols * sizeof(bool), row.begin());
        }
        halls.push_back(hall);
    }
    return halls;
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

#define films_txt "data/films.txt"
#define films_json "data/films.json"
#define arrangements_json "data/arrangements.json"

#endif //CINEMA_BASIC_INFORMATION_H