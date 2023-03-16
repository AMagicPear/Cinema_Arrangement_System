好的，你可以把结束时间相关的代码删除，以下是修改后的write_arrangements函数和read_arrangements函数：

```c++
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//定义Date类
class Date {
  public:
    int year; //年
    int month; //月
    int day; //日
    //构造函数
    Date(int y = 0, int m = 0, int d = 0) {
      year = y;
      month = m;
      day = d;
    }
};

//定义Time类
class Time {
  public:
    Date date; //日期
    int hour; //小时
    int minute; //分钟
    //构造函数
    Time(Date d = Date(), int h = 0, int m = 0) {
      date = d;
      hour = h;
      minute = m;
    }
};

//定义Film类
class Film {
  public:
    string name; //电影名称
    string type; //类型
    int time_during; //持续时长（分钟）
    //构造函数
    Film(string n = "", string t = "", int td = 0) {
      name = n;
      type = t;
      time_during = td;
    }
};

//定义Arrangement类
class Arrangement {
  public:
    int hall_ID; //影厅编号
    Film film; //电影对象
    Time begin_time; //开始时间

//构造函数
Arrangement(int id=0,Film f=Film(),Time time=Time()){
hall_ID=id;

film=f;

begin\_time=time;

}

};

//定义一个函数，用于向文件"data/arrangements.txt"中写入Arrangement对象的信息

void write\_arrangements(){

ofstream outfile;//创建一个输出流对象

outfile.open("data/arrangements.txt");//打开文件"data/arrangements.txt"

if(!outfile){//检查文件是否打开成功

cout<<"无法打开文件"<<endl;

return;

}

int n;//输入要写入的Arrangement对象的个数

cout<<"请输入要写入的安排个数："<<endl;

cin>>n;//从键盘读入n

for(int i=0;i<n;i++){//循环输入每个Arrangement对象的信息并写入到输出流中

Arrangement a;//创建一个Arrangement对象

cout<<"请输入第"<<i+1<<"个安排的影厅编号："<<endl;

cin>>a.hall_ID;//从键盘读入影厅编号并赋值给a.hall_ID

cout<<"请输入第"<<i+1<<"个安排的电影名称："<<endl;

cin>>a.film.name;//从键盘读入电影名称并赋值给a.film.name

cout<<"请输入第"<<i+1<<"个安排的电影类型："<<endl;

cin>>a.film.type;//从键盘读入电影类型并赋值给a.film.type

cout<<"请输入第"<<i+1<<"个安排的电影时长（分钟）："<<endl;

cin>>a.film.time_during;//从键盘读入电影时长并赋值给a.film.time_during

cout<<"请输入第"<<i+1<<"个安排的开始日期（年-月-日）："<<endl;

cin>>a.begin_time.date.year>>a.begin_time.date.month>>a.begin_time.date.day;//从键盘读入开始日期并赋值给a.begin_time.date.year,a.begin_time.date.month,a.begin_time.date.day

cout<<"请输入第"<<i+1<<"个安排的开始时间（时:分）："<<endl;

cin>>a.begin_time.hour>>a.begin_time.minute;//从键盘读入开始时间并赋值给a.begin_time.hour,a.begin_time.minute

outfile<<a.hall_ID<<" "<<a.film.name<<" "<<a.film.type<<" "<<a.film.time_during<<" "<<a.begin_time.date.year<<"-"<<a.begin_time.date.month<<"-"<<a.begin_time.date.day<<" "<<a.begin_time.hour<<":"<<a.begin_time.minute<<endl;//将Arrangement对象的信息写入到输出流中，每个信息之间用空格隔开，每个对象占一行

}

outfile.close();//关闭文件

cout<<"写入成功！"<<endl;

}

//定义一个函数，用于从文件"data/arrangements.txt"中读取Arrangement对象的信息并显示在屏幕上

void read\_arrangements(){

ifstream infile;//创建一个输入流对象

infile.open("data/arrangements.txt");//打开文件"data/arrangements.txt"

if(!infile){//检查文件是否打开成功

cout<<"无法打开文件"<<endl;

return;

}

while(!infile.eof()){//循环读取输入流中的每一行，直到文件结束

Arrangement a;//创建一个Arrangement对象

infile>>a.hall_ID>>a.film.name>>a.film.type>>a.film.time_during>>a.begin_time.date.year>>a.begin_time.date.month>>a.begin_time.date.day>>a.begin_time.hour>>a.begin_time.minute;//从输入流中读取每个信息并赋值给对应的属性，每个信息之间用空格隔开，每个对象占一行

if(infile.fail()) break;//如果读取失败，则跳出循环

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

//主函数，用于测试write_arrangements和read_arrangements两个函数

int main(){

write_arrangements();//调用write_arrangements函数，向文件"data/arrangements.txt"中写入Arrangement对象的信息

read_arrangements();//调用read_arrangements函数，从文件"data/arrangements.txt"中读取Arrangement对象的信息并显示在屏幕上

return 0;

}
```