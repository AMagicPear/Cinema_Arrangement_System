//
// Created by AMagicPear on 2023/3/15.
//
//管理员界面
#ifndef CINEMACPP_ADMIN_INFO_HPP
#define CINEMACPP_ADMIN_INFO_HPP
#include "Basic Information.hpp"

//定义管理员密码
const std::string admin_password = "ampc";

using namespace std;

//传入vector<Film>要求用户排片并return最后的排片
vector<Arrangement> creat_arrangements(vector<Film> films) {
    show_films(films);
    vector<Arrangement> arrangements;
    char choice = 'y';
    while (choice == 'y' || choice == 'Y') {
        cout << "请输入影厅号（1-" << HALL_NUM << "）：" << endl;
        int hall_ID;
        cin >> hall_ID;
        while (hall_ID < 1 || hall_ID > HALL_NUM) {
            cout << "影厅号无效，请重新输入（1-" << HALL_NUM << "）：" << endl;
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
            date.set(year, month, day);
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
        Arrangement arrangement(hall_ID, film_found, begin_time);
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

//要求用户修改电影数据并return
vector<Film> edit_films(vector<Film> films) {
    int choice='y';
    while (choice == 'y' || choice == 'Y') {
        cout << "选择操作：[1]增加电影 [2]删除电影\n";
        cin >> choice;
        if(choice==1){
            cout<<"请输入要增加的电影的数据：\n";
            Film film_input;
            cout<<"名称：";
            cin>>film_input.name;
            cout<<"类型：";
            cin>>film_input.type;
            cout<<"时长：";
            cin>>film_input.time_during;
            films.push_back(film_input);
            cout<<"增加完成！";
            return films;
            break;
        } else if(choice==2){
            cout<<"请输入要删除的电影序号或名称";
            string film_input;
            cin>>film_input;
            // 查找Vector<Film>中是否有对应的电影
            bool found = false; // 标记是否找到电影
            for (int i = 0; i < films.size(); i++) {
                if (film_input == films[i].name || film_input == to_string(i + 1)) {
                    // 如果输入的是电影名称或者序号，就把对应的Film对象赋值给film_found，并把found设为true
                    films.erase(films.begin()+i-1);
                    found = true;
                    break;
                }
            }
            if (!found) {
                // 如果没有找到对应的电影，就提示用户并跳过这次循环
                cout << "没有这部电影，请重新选择。" << endl;
                continue;
            }
        } else{
            cout<<"输入有误！请重新输入：";
            continue;
        }
        // 询问用户是否要继续编辑电影
        cout << "继续添加排片/提交操作（y/n）" << endl;
        cin >> choice;
        while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
            cout << "输入无效，请重新输入（y/n）：" << endl;
            cin >> choice;
        }
    }
    cout<<"提交成功！"<<endl;
    return films;
}

class Admin {
public:
    static void welcome() {
        cout << "====管理员====" << endl;
        string password_input;
        cout << "请输入管理员密码：";
        while (true) {
            cin >> password_input;
            if (password_input != admin_password) {
                printf("输入有误！重新输入：");
                continue;
            } else break;
        }
        cout << "管理员登录成功！" << endl;
    }

    static void main() {
        vector<Film> films = load_films(films_json);
        vector<Arrangement> arrangements = load_arrangements(arrangements_json,seats_folder);
        int choice{};
        re_start:
        cout << "【欢迎来到影院管理员界面】\n[1]查看&编辑当前所有电影数据" << endl
             << "[2]查看当前影厅座位信息" << endl
             << "[3]进入排片系统" << endl
             <<"[4]退出"<<endl
             << "选择一项功能：";
        cin >> choice;
        while (true) {
            if (choice == 1) {
                //查看&编辑当前所有电影数据
                show_films(films);
                films = edit_films(films);
                save_films(films,films_json);
                goto re_start;
            } else if (choice == 2) {
                //查看当前影厅的座位信息
                cin>>choice;
                break;
            } else if (choice == 3) {
                //进入排片系统
                show_arrangements(arrangements);
                show_films(films);
                creat_arrangements(films);
                break;
            } else if(choice==4){
                ::exit(3);
            }
            else {
                cout << "输入有误！请输入1~3：";
            }
        }
    }
};

#endif //CINEMACPP_ADMIN_INFO_HPP