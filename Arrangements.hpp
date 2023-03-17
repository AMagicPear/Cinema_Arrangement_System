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
    file.close();
}

//保存vector<Film>中的电影数据到文件
void save_films(const vector<Film> &films, const string &file_dst) {
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

//从arrangements.json内读取arrangements的信息并return
vector<Arrangement> load_arrangements(const string& file_dst) {
    vector<Arrangement> arrangements;
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
    return arrangements;
}

//从films.json内读取films的信息并return给vector
vector<Film> load_films(const string& file_dst){
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
void show_arrangements(vector<Arrangement> arrangements) {
    cout << "序号\t影片名称\t类型\t时长\t影厅号\t开始时间" << endl;
    Film film;
    for (int i = 0; i < arrangements.size(); ++i) {
        film = arrangements[i].film;
        cout << i+1 << "\t" << film.name << "\t" << film.type << "\t" << film.time_during << "\t" << arrangements[i].hall_ID
             << "\t";
        arrangements[i].begin_time.print_accurate();
    }
}

//从films.txt内读取films的信息并return给vector
vector<Film> load_films_old(const string& file_dst){
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
        cout << i + 1 << ". " << films[i].name << " " << films[i].type << " " << films[i].time_during<<"min"<< endl;
    }
    cout<<"------------"<<endl;
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
