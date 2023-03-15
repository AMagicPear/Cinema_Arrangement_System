
//
// Created by AMagicPear on 2023/3/13.
//

#ifndef CINEMA_BASIC_INFORMATION_H
#define CINEMA_BASIC_INFORMATION_H
#include <utility>
#include <string>
#include <ctime>
#include <iomanip>

#define ARRANGE_NUM 10
#define FILM_NUM 5
#define HALL_NUM 3
using namespace std;

//一部电影
class Film{
public:
    string name; //名称
    string type; //类型
    int time_during{}; //持续时长（分钟）
    void set(string name_set, string type_set, int time_during_set);
};
//设置一部电影的参数函数
void Film::set(string name_set, string type_set, int time_during_set){
    name = std::move(name_set);
    type = std::move(type_set);
    time_during = time_during_set;
}

//日期和时间格式
struct Date{
    int year;
    int month;
    int day;
    //设置Date为当前系统日期
    void set(const string& str){
        if(str=="today"){
            time_t now=time(nullptr);
            tm *ltm = localtime(&now);
            year=1900 + ltm->tm_year;
            month=1+ltm->tm_mon;
            day=ltm->tm_mday;
        } else{
            year=0,month=0,day=0;
        }
    }
    //设置Date为自定义日期
    void set(int year_set,int month_set,int day_set){
        year=year_set;
        month=month_set;
        day=day_set;
    }
    void print() const{
        cout<<year<<"年"<<month<<"月"<<day<<"日\n";
    }
};

struct Time {
    struct Date date;
    int hour;
    int minute;
    void print_accurate() const{
        //以"时:分"格式输出，时分均为两位数字
        cout<<setw(2)<<setfill('0')<<hour<<":"<<setw(2)<<setfill('0')<<minute<<endl;
    }
    void print_date() const{
        date.print();
    }
};

//一次排片
class Arrangement{
public:
    Film film;  //排哪部片
    int hall_ID{};  //在几号厅
    Time begin_time{};  //开始时间
    void set(Film film_set, int hall_ID_set, Time begin_time_set);
};
//设置一次排片的参数
void Arrangement::set(Film film_set, int hall_ID_set, Time begin_time_set) {
    film=std::move(film_set);
    hall_ID=hall_ID_set;
    begin_time=begin_time_set;
}
//影厅对象
class Hall{
private:
    //定义影厅座位的行和列数
    const static int row=5;
    const static int col=10;
public:
    //定义座位表，true为已被购买，false为空座
    bool seats[row][col]={}; //座位表为二维数组
    void Show_Seats(){
        for (auto & seat : seats) {
            for (bool j : seat) {
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }
    void Select_seat(int row_select,int col_select){
        seats[row_select][col_select]= true;
    }
};

//一个座位位置
struct seat{
    int row;
    int col;
};

//一张票
class Ticket{
public:
    int ID{};
    Arrangement arrangement;
    struct seat seat{};
};

#endif //CINEMA_BASIC_INFORMATION_H