//
// Created by AMagicPear on 2023/3/16.
//

#ifndef CINEMACPP_ARRANGEMENTS_HPP
#define CINEMACPP_ARRANGEMENTS_HPP

#include "Basic Information.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
using json = nlohmann::json;

//向arrangements.json内保存arrangements的信息
void save_arrangements(const vector<Arrangement>& arrangements,const string& file_dst) {
    json j;
    for (const auto& a : arrangements) {
        j.push_back({
                            {"hall_ID", a.hall_ID},
                            {"film", {
                                                {"name", a.film.name},
                                                {"type", a.film.type},
                                                {"time_during", a.film.time_during}
                                        }},
                            {"begin_time", {
                                                {"date", {
                                                                 {"year", a.begin_time.date.year},
                                                                 {"month", a.begin_time.date.month},
                                                                 {"day", a.begin_time.date.day}
                                                         }},
                                                {"hour", a.begin_time.hour},
                                                {"minute", a.begin_time.minute}
                                        }}
                    });
    }
    ofstream file(file_dst);
    file << j.dump(4);
}

//从arrangements.json内读取arrangements的信息并return
vector<Arrangement> load_arrangements(const string& file_dst) {
    vector<Arrangement> arrangements;
    ifstream file(file_dst);
    json j;
    file >> j;
    for (const auto& item : j) {
        Arrangement a;
        a.hall_ID = item["hall_ID"];
        a.film.name = item["film"]["name"];
        a.film.type = item["film"]["type"];
        a.film.time_during = item["film"]["time_during"];
        a.begin_time.date.year = item["begin_time"]["date"]["year"];
        a.begin_time.date.month = item["begin_time"]["date"]["month"];
        a.begin_time.date.day = item["begin_time"]["date"]["day"];
        a.begin_time.hour = item["begin_time"]["hour"];
        a.begin_time.minute = item["begin_time"]["minute"];
        arrangements.push_back(a);
    }
    return arrangements;
}

//输出一个vector<Arrangement>内的所有排片
void show_arrangements(vector<Arrangement> arrangements) {
    cout << "序号\t影片名称\t类型\t时长\t影厅号\t开始时间" << endl;
    Film film;
    for (int i = 0; i < arrangements.size(); ++i) {
        film = arrangements[i].film;
        cout << i << "\t" << film.name << "\t" << film.type << "\t" << film.time_during << "\t" << arrangements[i].hall_ID
             << "\t";
        arrangements[i].begin_time.print_accurate();
    }
}

//从films.txt内读取films的信息并return给vector
vector<Film> load_films(const string& file_dst){
    vector<Film> films;
    //打开目标文件
    ifstream fin(file_dst);
    if(!fin){
        cerr<<"无法打开"<<file_dst<<endl;
        return {};
    }
    //读取文件并push_back到vector中
    string line;
    while (getline(fin,line)){
        istringstream iss(line);
        //需要读取的信息，若Film增加信息只需要概这里即可
        string name,type;
        int time_during;
        iss>>name>>type>>time_during;
        Film film(name,type,time_during);
        films.push_back(film);
    }
    fin.close();
    return films;
}

//输出vector<Film>中的电影数据
void show_films(vector<Film> films){
    cout<<"以下是现有电影的数据："<<endl;
    for (int i = 0; i < films.size(); i++) {
        cout << i + 1 << ". " << films[i].name << " " << films[i].type << " " << films[i].time_during << endl;
    }
}

//传入vector<Film>要求用户排片并return最后的排片
vector<Arrangement> creat_arrangements(vector<Film> films){
    show_films(films);
    vector<Arrangement> arrangements;
    char choice='y';
    while(choice=='y'||choice=='Y'){
        cout << "请输入影厅号（1-"<<HALL_NUM<<"）：" << endl;
        int hall_ID;
        cin >> hall_ID;
        while (hall_ID < 1 || hall_ID > HALL_NUM) {
            cout << "影厅号无效，请重新输入（1-"<<HALL_NUM<<"）：" << endl;
            cin >> hall_ID;
        }
        cout << "请选择电影（输入序号或者名称）：" << endl;
        string film_input;
        cin >> film_input;
        // 查找Vector<Film>中是否有对应的电影
        Film film_found("", "", 0); // 创建一个空的Film对象
        bool found = false; // 标记是否找到电影
        for (int i = 0; i < films.size(); i++) {
            if (film_input == films[i].name || film_input == to_string(i + 1)) {
                // 如果输入的是电影名称或者序号，就把对应的Film对象赋值给film_found，并把found设为true
                film_found = films[i];
                found = true;
                break;
            }
        }
        if (!found) {
            // 如果没有找到对应的电影，就提示用户并跳过这次循环
            cout << "没有这部电影，请重新选择。" << endl;
            continue;
        }
        // 询问用户输入排片的开始时间
        cout << "请输入排片的开始日期（年/月/日或者today）：" << endl;
        string date_input;
        cin >> date_input;
        int year, month, day;
        Date date;
        if (date_input == "today") {
            // 如果用户输入"today"，就用系统时间来设置年月日
            date.set("today");
        } else {
            // 如果用户输入其他字符串，就用istringstream来分割并转换为整数
            istringstream iss(date_input);
            char slash1, slash2;
            iss >> year >> slash1 >> month >> slash2 >> day;
            date.set(year,month,day);
        }
        // 检查用户输入的日期是否合法
        while (year < 2023 || year > 2024 || month < 1 || month > 12 || day < 1 || day > 31) {
            cout << "日期无效，请重新输入（年/月/日或者today）：" << endl;
            cin >> date_input;
            if (date_input == "today") {
                // 如果用户输入"today"，就用系统时间来设置年月日
                date.set("today");
            } else {
                // 如果用户输入其他字符串，就用istringstream来分割并转换为整数
                istringstream iss(date_input);
                char slash1, slash2;
                iss >> year >> slash1 >> month >> slash2 >> day;
                date.set(year, month, day);
            }
        }
        cout << "请输入排片的开始时间（时:分）：" << endl;
        int hour, minute;
        char colon;
        cin >> hour >> colon >> minute;
        // 检查用户输入的时间是否合法
        while (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            cout << "时间无效，请重新输入（时:分）：" << endl;
            cin >> hour >> colon >> minute;
        }
        // 创建一个Time对象
        Time begin_time(date, hour, minute);
        // 用用户输入的信息来构造一个Arrangement对象，并把它push_back到Vector<Arrangement>中
        Arrangement arrangement(hall_ID, film_found,begin_time);
        arrangements.push_back(arrangement);
        // 询问用户是否要继续添加排片
        cout << "是否要继续添加排片？（y/n）" << endl;
        cin >> choice;
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
            cout << "输入无效，请重新输入（y/n）：" << endl;
            cin >> choice;
        }
    }
    return arrangements;
}

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
void sort_arrangements(vector<Arrangement>& arrangements) {
    // 使用algorithm库中提供sort函数，并传入自定义compare_begin_tim函数作为比较规则来对vector进行排序
    sort(arrangements.begin(), arrangements.end(), compare_begin_time);
}

#endif //CINEMACPP_ARRANGEMENTS_HPP
