//
// Created by AMagicPear on 2023/3/16.
//

#ifndef CINEMACPP_ARRANGEMENTS_H
#define CINEMACPP_ARRANGEMENTS_H

#include "Basic Information.h"

//定义一个函数，用于向文件"data/arrangements.txt"中写入Arrangement对象的信息
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

//定义一个函数，用于从文件"data/arrangements.txt"中读取Arrangement对象的信息并显示在屏幕上
void read_arrangements(const string& file) {
    ifstream infile;//创建一个输入流对象
    infile.open(file);//打开文件"data/arrangements.txt"
    if (!infile) {//检查文件是否打开成功
        cout << "无法打开文件" << endl;
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
#endif //CINEMACPP_ARRANGEMENTS_H
