//
// Created by AMagicPear on 2023/3/13.
//

#ifndef CINEMA_BASIC_INFORMATION_H
#define CINEMA_BASIC_INFORMATION_H

#include <utility>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;
//基本信息初始化
//#define ARRANGE_NUM 10
//#define FILM_NUM 5
#define HALL_NUM 3
//Film* film_list=new Film[FILM_NUM];
//vector<Film> film_list;
//auto* arrangement_list=new Arrangement[ARRANGE_NUM]{};
//vector<Arrangement> arrangement_list;

#define films_txt "data/films.txt"
#define films_json "data/films.json"
#define arrangements_json "data/arrangements.json"
#define seats_folder "data/halls"
#define user_folder "data/users"
#define user_info "data/users/userinfo.txt"
using namespace std;
// 定义Hall类型为bool类型的二维vector表示座位表
typedef vector<vector<bool>> Seats;
// 定义一个打印Hall座位表的函数
void show_seats(const Seats& hall) {
    cout<<"----------"<<endl;
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
    cout<<"----------"<<endl;
}
//定义一个影厅对象
class Hall{
public:
    int ID; //影厅号
    Seats seats; //座位表
    //打印座位表函数
    void print_seats() const{
        show_seats(seats);
    }
};

// 影厅座位表构造函数
Seats create_hall(int row, int col) {
    // 使用std::vector的构造函数，创建一个row行col列的全部初始化为false的Hall对象
    Seats hall(row, vector<bool>(col, false));
    // 返回Hall对象
    return hall;
}
//定义预制的影厅对象
Hall hall_default[HALL_NUM]={{1, create_hall(4,5)},
                      {2, create_hall(5,5)},
                      {3, create_hall(15,15)}};
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
        cout << year << "/" <<setw(2)<<setiosflags(ios::right)<<setfill('0')<< month << "/" <<setw(2)<<setfill('0')<< day;
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
    //以"时:分"格式输出，时分均为两位数字
    void print_accurate() const {
        cout << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute;
    }
    //输出日期
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
    Hall hall;          //该场排片的影厅
    Film film;          //排哪部片
    Time begin_time{};  //开始时间
    void set(int hall_ID_set, Film film_set, Time begin_time_set);

    //构造函数
    Arrangement(int hall_ID_set = 0, Film film_set = Film(), Time begin_time_set = Time()) {
        hall = hall_default[hall_ID_set - 1];
        film = film_set;
        begin_time = begin_time_set;
    }
};
//设置一次排片的参数
void Arrangement::set(int hall_ID_set, Film film_set, Time begin_time_set) {
    film = std::move(film_set);
    hall = hall_default[hall_ID_set];
    begin_time = begin_time_set;
}
//排片构成的向量表示现在所有排片
typedef vector<Arrangement> Arrangements;
//座位的行和列结构
struct SeatLocation{
    unsigned int row;
    unsigned int col;
};
//一张票
class Ticket {
public:
    Film film;
    Time begin_time;
    int Hall_ID;
    SeatLocation seatLocation{};
    //传入排片来购票，同时会修改排片的座位表
    Ticket(Arrangement& ar_set,SeatLocation seat_set){
        ar_set.hall.seats[seat_set.row][seat_set.col]=true;
        film=ar_set.film;
        begin_time=ar_set.begin_time;
        seatLocation=seat_set;
        Hall_ID=ar_set.hall.ID;
    }
    //直接定义一张票的内容
    Ticket(Film film_set,Time begin_time_set,int hall_set,SeatLocation seat_set){
        film=film_set;
        begin_time=begin_time_set;
        Hall_ID=hall_set;
        seatLocation=seat_set;
    }
};

//保存座位表到文件
void save_seats(const Seats& seats, const std::string& file_path){
    // 打开一个二进制文件
    std::ofstream outfile(file_path, std::ios::out | std::ios::binary);
    // 遍历每个子向量
    for (const auto& vb : seats){
        // 把子向量的大小写入文件
        size_t size = vb.size();
        outfile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        // 把子向量的数据写入文件
        for (size_t i = 0; i < size; i++){
            bool b = vb[i];
            outfile.write(reinterpret_cast<const char*>(&b), sizeof(bool));
        }
    }
    // 关闭文件
    outfile.close();
}
//从文件读取座位表
Seats load_seats(const std::string& file_path){
    // 创建一个空的vector<vector<bool>>对象
    std::vector<std::vector<bool>> seats;
    // 打开一个二进制文件
    std::ifstream infile(file_path, std::ios::in | std::ios::binary);
    // 判断文件是否打开成功
    if (infile.is_open()){
        // 读取文件直到结束
        while (!infile.eof()){
            // 读取子向量的大小
            size_t size = 0;
            infile.read(reinterpret_cast<char*>(&size), sizeof(size));
            // 判断是否读取成功
            if (infile.gcount() == sizeof(size)){
                // 创建一个空的子向量
                std::vector<bool> vb;
                // 遍历每个bool元素
                for (size_t i = 0; i < size; i++){
                    // 读取bool元素的值
                    bool b = false;
                    infile.read(reinterpret_cast<char*>(&b), sizeof(bool));
                    // 把bool元素添加到子向量中
                    vb.push_back(b);
                }
                // 把子向量添加到对象中
                seats.push_back(vb);
            }
        }
        // 关闭文件
        infile.close();
    }else{
        cerr<<"无法打开座位表！"<<endl;
    }
    // 返回对象
    return seats;
}

//向arrangements.json内保存arrangements的信息
void save_arrangements_json(const Arrangements &arrangements, const string &file_dst) {
    json j;
    for (int i = 0; i < size(arrangements); ++i) {
        j.push_back({{"No",         i},
                     {"hall_ID",    arrangements[i].hall.ID},
                     {"film",       {
                                            {"name", arrangements[i].film.name},
                                            {"type", arrangements[i].film.type},
                                            {"time_during", arrangements[i].film.time_during}
                                    }},
                     {"begin_time", {
                                            {"date", {
                                                             {"year", arrangements[i].begin_time.date.year},
                                                             {"month", arrangements[i].begin_time.date.month},
                                                             {"day", arrangements[i].begin_time.date.day}
                                                     }},
                                            {"hour", arrangements[i].begin_time.hour},
                                            {"minute",      arrangements[i].begin_time.minute}
                                    }}
                    });
    }
    ofstream file(file_dst);
    file << j.dump(4);
    file.close();
}
//向halls文件夹内保存每个arrangement的影厅数据
//注意：halls文件夹内的文件名代表vector<arrangement>的序号
void save_halls(const Arrangements &arrangements,const std::string& folder_path){
    //遍历所有的排片
    for (int i = 0; i < size(arrangements); ++i) {
        //获取当前排片的座位表
        const Seats& seats = arrangements[i].hall.seats;
        //构造文件名，使用对象的序号作为文件名
        std::string file_path=folder_path+"/"+std::to_string(i)+".bin";
        save_seats(seats, file_path);
    }
}
//同时执行上面两个函数
void save_arrangements(const Arrangements &arrangements){
    save_arrangements_json(arrangements,arrangements_json);
    save_halls(arrangements,seats_folder);
    cout<<"已保存排片数据！"<<endl;
}

//保存vector<Film>中的电影数据到文件
void save_films(const Films &films, const string &file_dst) {
    ofstream fin(file_dst);
    json j;
    for (const auto &i: films) {
        j.push_back({
                            {"film", {
                                    {"name", i.name},
                                    {"type", i.type},
                                    {"time_during", i.time_during}
                            }}
                    });
    }
    fin<<j.dump(4);
    fin.close();
}

//从arrangements.json和hall文件夹内读取排片的信息并return
Arrangements load_arrangements(const string& file_dst,const std::string& folder_path) {
    vector<Arrangement> arrangements;
    //从json中读取管理员排片的基本信息
    ifstream file(file_dst);
    json json;
    file >> json;
    for (const auto& i : json) {
        Film film(i["film"]["name"], i["film"]["type"], i["film"]["time_during"]);
        Date date(i["begin_time"]["date"]["year"], i["begin_time"]["date"]["month"], i["begin_time"]["date"]["day"]);
        Time begin_time(date,i["begin_time"]["hour"],i["begin_time"]["minute"]);
        Arrangement arrangement(i["hall_ID"],film,begin_time);
        arrangements.push_back(arrangement);
    }
    file.close();
    //从二进制文件内读取各个排片的座位表信息
    for (int i = 0; i < size(arrangements); ++i) {
        string file_path=folder_path+"/"+ to_string(i)+".bin";
        arrangements[i].hall.seats= load_seats(file_path);
    }
    return arrangements;
}
//从films.json内读取films的信息并return给vector
Films load_films(const string& file_dst){
    vector<Film> films;
    ifstream file(file_dst);
    json json;
    file >> json;
    for(const auto& i:json){
        Film film(i["film"]["name"],i["film"]["type"],i["film"]["time_during"]);
        films.push_back(film);
    }
    file.close();
    return films;
}

//输出一个vector<Arrangement>内的所有排片
void show_arrangements(Arrangements arrangements) {
    cout << " ====================================================================================== " << endl;
    cout <<setfill(' ')<< setw(7)<<setiosflags(ios::left)<<"|序号"
    <<setw(27) << "|       影片名称"
    <<setw(9)<<"| 类型"
    <<setw(9)<<"| 时长"
    <<setw(17)<<"|  放映日期" //2023/01/23
    <<setw(15)<<"| 放映时间"
    <<setw(9)<<"| 影厅"<<"|"<<endl; //todo 可增加余票显示
    Film film;
    cout<< setiosflags(ios::right);
    for(int i=0;i<arrangements.size();++i){
        cout <<setfill(' ')
        << "|  "<<i<<" "
                <<"|"<<setw(25)<<arrangements[i].film.name
             <<"| "<<arrangements[i].film.type<<" "
             <<"| "<<setw(3)<<arrangements[i].film.time_during<<" "
             <<"| "; arrangements[i].begin_time.print_date(); cout<<" "
             <<"|  "; arrangements[i].begin_time.print_accurate();cout<<"  ";
             cout<<"|  "<<arrangements[i].hall.ID<<"  |"<<endl;
    }
    cout << " ====================================================================================== " << endl;
//    cout<<"以下是现有的排片数据："<<endl;
//    cout << "序号\t影片名称\t类型\t时长\t影厅号\t开始时间" << endl;
//    Film film;
//    for (int i = 0; i < arrangements.size(); ++i) {
//        film = arrangements[i].film;
//        cout << i << "\t" << film.name << "\t" << film.type << "\t" << film.time_during << "\t" << arrangements[i].hall.ID
//             << "\t";
//        arrangements[i].begin_time.print_accurate();
//    }
//    cout<<"---------"<<endl;
}

////从films.txt内读取films的信息并return给vector
//Films load_films_old(const string& file_dst){
//    vector<Film> films;
//    //打开目标文件
//    ifstream fin(file_dst);
//    if(!fin){
//        cerr<<"无法打开"<<file_dst<<endl;
//        return {};
//    }
//    //读取文件并push_back到vector中
//    string line;
//    while (getline(fin,line)){
//        istringstream iss(line);
//        //需要读取的信息，若Film增加信息只需要概这里即可
//        string name,type;
//        int time_during;
//        iss>>name>>type>>time_during;
//        Film film(name,type,time_during);
//        films.push_back(film);
//    }
//    fin.close();
//    return films;
//}

//输出vector<Film>中的电影数据
void show_films(Films films){
    cout<<"以下是现有电影的数据："<<endl;
    for (int i = 0; i < films.size(); i++) {
        cout<<"["<< i << "] " << films[i].name << " " << films[i].type << " " << films[i].time_during<<"min"<< endl;
    }
    cout<<"------------"<<endl;
}

/*//为避免信息定位困难，排片的排序仅在输出时进行！文件内容不变！
// 定义一个函数，用来比较两个Arrangement对象的begin_time先后
bool compare_begin_time(const Arrangement& a1, const Arrangement& a2) {
    // 如果a1的begin_time的日期早于a2的begin_time的日期，就返回true
    if (a1.begin_time.date < a2.begin_time.date) {
        return true;
    }
        // 如果a1的begin_time的日期等于a2的begin_time的日期，就比较它们的小时和分钟
    else if (a1.begin_time.date == a2.begin_time.date) {
        // 如果a1的begin_time的小时早于a2的begin_time的小时，就返回true
        if (a1.begin_time.hour < a2.begin_time.hour) {
            return true;
        }
            // 如果a1的begin_time的小时等于a2的begin_time的小时，就比较它们的分钟
        else if (a1.begin_time.hour == a2.begin_time.hour) {
            // 如果a1的begin_time的分钟早于或等于a2的begin_time分钟，就返回true
            if (a1.begin_time.minute <= a2.begin_time.minute) {
                return true;
            }
        }
    }

    // 其他情况都返回false
    return false;
}
// 定义一个函数，传入一个vector<Arrangement>对象，并根据其中每个元素（Arrangement对象）中包含有关开始时间（Time对象）中包含有关日期（Date对象）中包含有关年月日（int类型）以及开始时间（Time对象）中包含有关时分（int类型）来对这个Vector排序
void sort_arrangements(Arrangements& arrangements) {
    // 使用algorithm库中提供sort函数，并传入自定义compare_begin_tim函数作为比较规则来对vector进行排序
    sort(arrangements.begin(), arrangements.end(), compare_begin_time);
}*/


#endif //CINEMA_BASIC_INFORMATION_H