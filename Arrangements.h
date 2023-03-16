//
// Created by AMagicPear on 2023/3/16.
//

#ifndef CINEMACPP_ARRANGEMENTS_H
#define CINEMACPP_ARRANGEMENTS_H

#include "Basic Information.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//直接向文件"data/arrangements.txt"中覆写Arrangement对象的信息
void write_arrangements(const string& file) {
    ofstream outfile;//创建一个输出流对象
    outfile.open(file);//打开文件"data/arrangements.txt"
    if (!outfile) {//检查文件是否打开成功
        cout << "无法打开文件" << endl;
        return;
    }
    int n;//输入要写入的Arrangement对象的个数
    cout << "请输入要写入的排片个数：" << endl;
    cin >> n;//从键盘读入n
    for (int i = 0; i < n; i++) {//循环输入每个Arrangement对象的信息并写入到输出流中
        Arrangement a;//创建一个Arrangement对象
        cout << "请输入第" << i + 1 << "个排片的影厅编号：" << endl;
        cin >> a.hall_ID;//从键盘读入影厅编号并赋值给a.hall_ID
        cout << "请输入第" << i + 1 << "个排片的电影名称：" << endl;
        cin >> a.film.name;//从键盘读入电影名称并赋值给a.film.name
        cout << "请输入第" << i + 1 << "个排片的电影类型：" << endl;
        cin >> a.film.type;//从键盘读入电影类型并赋值给a.film.type
        cout << "请输入第" << i + 1 << "个排片的电影时长（分钟）：" << endl;
        cin >> a.film.time_during;//从键盘读入电影时长并赋值给a.film.time_during
        cout << "请输入第" << i + 1 << "个排片的开始日期（年-月-日）：" << endl;
        cin >> a.begin_time.date.year >> a.begin_time.date.month
            >> a.begin_time.date.day;//从键盘读入开始日期并赋值给a.begin_time.date.year,a.begin_time.date.month,a.begin_time.date.day
        cout << "请输入第" << i + 1 << "个排片的开始时间（时:分）：" << endl;
        cin >> a.begin_time.hour >> a.begin_time.minute;//从键盘读入开始时间并赋值给a.begin_time.hour,a.begin_time.minute
        ostringstream oss;//创建一个字符串流对象
        oss << a.hall_ID << " " << a.film.name << " " << a.film.type << " " << a.film.time_during << " "
            << a.begin_time.date.year << "-" << a.begin_time.date.month << "-" << a.begin_time.date.day << " "
            << a.begin_time.hour << ":" << a.begin_time.minute << endl;//将Arrangement对象的信息写入到字符串流中，每个信息之间用空格隔开，每个对象占一行
        outfile << oss.str();//将字符串流中的内容写入到输出流中
    }
    outfile.close();//关闭文件
    cout << "写入成功！" << endl;
}
// 遍历Vector<Arrangement>中的每个对象，并把它们的hall_ID和film属性（包括name, type和time_during）以及begin_time属性（包括date, hour和minute）按照一定格式写入到文件中
void write_arrangements(const string& file,const vector<Arrangement>& arrangements){
    fstream infile(file);
    if (!infile) {
        cerr << "无法打开文件"<<file<< endl;
        return;
    }
    for (auto & arrangement : arrangements) {
        infile << arrangement.hall_ID << " " << arrangement.film.name << " " << arrangement.film.type << " "
               << arrangement.film.time_during << " "
               << arrangement.begin_time.date.year << "/"
               << arrangement.begin_time.date.month<< "/"
               << arrangement.begin_time.date.day<< " "
               << arrangement.begin_time.hour<< ":"
               << arrangement.begin_time.minute<< endl;
    }
}

//从文件"data/arrangements.txt"中读取Arrangement对象的信息并显示在屏幕上
void show_arrangements(const string& file) {
    ifstream infile;//创建一个输入流对象
    infile.open(file);//打开文件"data/arrangements.txt"
    if (!infile) {//检查文件是否打开成功
        cerr << "无法打开排片文件" << endl;
        return;
    }
    while (!infile.eof()) {//循环读取输入流中的每一行，直到文件结束
        Arrangement a;//创建一个Arrangement对象
        string line;//创建一个字符串变量，用于存储每一行的内容
        getline(infile,line);//从输入流中读取一行并赋值给line
        if(line.empty()) break;//如果读取到空行，则跳出循环
        istringstream iss(line);//创建一个字符串流对象，用于解析line中的内容
        iss>>a.hall_ID>>a.film.name>>a.film.type>>a.film.time_during;//从字符串流中读取影厅编号，电影名称，电影类型和电影时长，并赋值给对应的属性
        char ch;//创建一个字符变量，用于跳过分隔符"-"
        iss>>a.begin_time.date.year>>ch>>a.begin_time.date.month>>ch>>a.begin_time.date.day;//从字符串流中读取开始日期，并赋值给对应的属性，同时跳过分隔符"-"
        ch = ' ';//将字符变量赋值为空格，用于跳过分隔符":"
        iss>>a.begin_time.hour>>ch>>a.begin_time.minute;//从字符串流中读取开始时间，并赋值给对应的属性，同时跳过分隔符":"
        cout<<"影厅编号："<<a.hall_ID<<endl;//显示影厅编号
        cout<<"电影名称："<<a.film.name<<endl;//显示电影名称
        cout<<"电影类型："<<a.film.type<<endl;//显示电影类型
        cout<<"电影时长（分钟）："<<a.film.time_during<<endl;//显示电影时长
        cout<<"开始日期："<<a.begin_time.date.year<<"-"<<a.begin_time.date.month<<"-"<<a.begin_time.date.day<<endl;//显示开始日期
        cout<<"开始时间："<<a.begin_time.hour<<":"<<a.begin_time.minute<<endl;//显示开始时间
        cout<<"----------------------"<<endl;//输出一条分隔线
    }
    infile.close();//关闭文件
}


// 定义一个函数，用来读取"data/arrangement.txt"文件，并返回一个Vector<Arrangement>对象
vector<Arrangement> read_arrangements() {
    // 创建一个空的Vector<Arrangement>对象
    vector<Arrangement> arrangements;

    // 用ifstream打开文件"data/arrangements.txt"
    ifstream fin("data/arrangements.txt");
    if (!fin) {
        cerr << "无法打开文件data/arrangements.txt" << endl;
        return arrangements;
    }
    // 用一个循环来读取文件中的每一行，并把它们转换为对应的属性值
    string line;
    while (getline(fin, line)) {
        // 用istringstream来分割每一行的字符串
        istringstream iss(line);
        int hall_ID;
        string film_name;
        string film_type;
        int film_time_during;
        int year, month, day, hour, minute;
        char slash1, slash2, colon;

        // 读取每个属性值
        iss >> hall_ID >> film_name >> film_type >> film_time_during
            >> year >> slash1 >> month >> slash2 >> day
            >> hour >> colon >> minute;
        // 创建一个Film对象和一个Date对象和一个Time对象
        Film film(film_name, film_type, film_time_during);
        Date date(year, month, day);
        Time begin_time(date, hour, minute);

        // 用这些属性值来构造一个Arrangement对象，并把它push_back到Vector<Arrangement>中
        Arrangement arrangement(hall_ID, film, begin_time);
        arrangements.push_back(arrangement);
    }

    // 关闭文件
    fin.close();

    // 返回Vector<Arrangement>对象
    return arrangements;
}

//根据现有的电影创建排片
void create_arrangements() {
    // 创建一个空的Vector<Film>对象
    vector<Film> films;

    // 用ifstream打开文件"data/films.txt"
    ifstream fin("data/films.txt");
    if (!fin) {
        cout << "无法打开文件data/films.txt" << endl;
        return;
    }

    // 用一个循环来读取每一行，并用istringstream来分割每一行的字符串，并用这些字符串来构造一个Film对象，并把它push_back到Vector中
    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        string name, type;
        int time_during;
        iss >> name >> type >> time_during;
        Film film(name, type, time_during);
        films.push_back(film);
    }

    // 关闭文件
    fin.close();

    // 输出Vector中的电影数据给用户
    cout << "以下是现有电影的数据：" << endl;
    for (int i = 0; i < films.size(); i++) {
        cout << i + 1 << ". " << films[i].name << " " << films[i].type << " " << films[i].time_during << endl;
    }

    // 创建一个空的Vector<Arrangement>对象
    vector<Arrangement> arrangements;

    // 用一个循环来询问用户是否要继续添加排片，并在每次循环中让用户输入一个有效的影厅号，并从Vector<Film>中选择一个电影（比如通过输入序号或者名称），并用这些信息来构造一个Arrangement对象，并把它push_back到Vector<Arrangement>中
    char choice = 'y';

    while (choice == 'y' || choice == 'Y') {
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
        if (date_input == "today") {
            // 如果用户输入"today"，就用系统时间来设置年月日
            time_t now = time(0); // 获取当前系统时间
            tm *ltm = localtime(&now); // 转换为本地时间结构体
            year = 1900 + ltm->tm_year; // 获取年份
            month = 1 + ltm->tm_mon; // 获取月份
            day = ltm->tm_mday; // 获取日期
        } else {
            // 如果用户输入其他字符串，就用istringstream来分割并转换为整数
            istringstream iss(date_input);
            char slash1, slash2;
            iss >> year >> slash1 >> month >> slash2 >> day;
        }
        // 检查用户输入的日期是否合法
        Date date;
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

    // 用ofstream打开文件"data/arrangements.txt"
    ofstream fout("data/arrangements.txt",ios::app);
    if (!fout) {
        cerr << "无法打开文件data/arrangements.txt" << endl;
        return;
    }

    // 用一个循环来遍历Vector<Arrangement>中的每个对象，并把它们的hall_ID和film属性（包括name, type和time_during）以及begin_time属性（包括date, hour和minute）按照一定格式写入到文件中
    for (auto & arrangement : arrangements) {
        fout << arrangement.hall_ID << " " << arrangement.film.name << " " << arrangement.film.type << " "
             << arrangement.film.time_during << " "
             << arrangement.begin_time.date.year << "/"
             << arrangement.begin_time.date.month<< "/"
             << arrangement.begin_time.date.day<< " "
             << arrangement.begin_time.hour<< ":"
             << arrangement.begin_time.minute<< endl;
    }

    // 关闭文件
    fout.close();

    // 提示用户排片已经完成
    cout << "排片已经完成，感谢使用。" << endl;
}


// 定义一个函数，用来比较两个Arrangement对象的begin_time属性
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

#endif //CINEMACPP_ARRANGEMENTS_H
