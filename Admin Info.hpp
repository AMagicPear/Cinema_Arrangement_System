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
vector<Arrangement> edit_arrangements(Arrangements &arrangements, vector<Film> films) {
//    show_films(films);
//    vector<Arrangement> arrangements;
    restart:
    int c1 = 0;
    do {
        cout << "[1]增加排片 [2]删除排片：";
        cin >> c1;
    } while (c1 != 1 && c1 != 2);
    if (c1 == 1) {
        restart1:
        show_films(films);
        cout << "请输入影厅号（1-" << HALL_NUM << "）：";
        int hall_ID;
        cin >> hall_ID;
        while (hall_ID < 1 || hall_ID > HALL_NUM) {
            cout << "影厅号无效，请重新输入（1-" << HALL_NUM << "）：";
            cin >> hall_ID;
        }
        cout << "请选择电影（输入序号或者名称）：";
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
            cout << "没有这部电影，请重新选择：";
            goto restart1;
        }
        // 询问用户输入排片的开始时间
        cout << "请输入排片的开始日期（年/月/日）：";
        string date_input;
        cin >> date_input;
        int year, month, day;
        Date date;
        /*if (date_input == "today") {
            // 如果用户输入"today"，就用系统时间来设置年月日
            time_t now = time(nullptr);
            tm *ltm = localtime(&now);
            year = 1900 + ltm->tm_year;
            month = 1 + ltm->tm_mon;
            day = ltm->tm_mday;
        } else */{
            // 如果用户输入其他字符串，就用istringstream来分割并转换为整数
            istringstream iss(date_input);
            char slash1, slash2;
            iss >> year >> slash1 >> month >> slash2 >> day;
            date.set(year, month, day);
        }
        // 检查用户输入的日期是否合法
        while (year < 2023 || year > 2024 || month < 1 || month > 12 || day < 1 || day > 31) {
            cout << "日期无效，请重新输入（年/月/日）：";
            cin >> date_input;
            /*if (date_input == "today") {
                // 如果用户输入"today"，就用系统时间来设置年月日
                date.set("today");
            } else */{
                // 如果用户输入其他字符串，就用istringstream来分割并转换为整数
                istringstream iss(date_input);
                char slash1, slash2;
                iss >> year >> slash1 >> month >> slash2 >> day;
                date.set(year, month, day);
            }
        }
        cout << "请输入排片的开始时间（时:分）：";
        int hour, minute;
        char colon;
        cin >> hour >> colon >> minute;
        // 检查用户输入的时间是否合法
        while (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            cout << "时间无效，请重新输入（时:分）：";
            cin >> hour >> colon >> minute;
        }
        // 创建一个Time对象
        Time begin_time(date, hour, minute);
        // 用用户输入的信息来构造一个Arrangement对象，并把它push_back到Vector<Arrangement>中
        Arrangement arrangement(hall_ID, film_found, begin_time);
        arrangements.push_back(arrangement);
    } else if(c1==2){
        int to_delete;
        cout<<"请输入要删除的排片序号：";
        cin>>to_delete;
        arrangements.erase(arrangements.begin()+to_delete);
        show_arrangements(arrangements);
    }
    // 询问用户是否要继续更改排片
    show_arrangements(arrangements);
    cout << "是否要继续更改排片？（y/n）" << endl;
    char choice;
    cin >> choice;
    while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
        cout << "输入无效，请重新输入（y/n）：" << endl;
        cin >> choice;
    }
    if (choice == 'y' || choice == 'Y') goto restart;
//    save_halls(arrangements, seats_folder);
//    cout<<"排片已保存！"<<endl;
    return arrangements;
}

//要求用户修改电影数据并return
vector<Film> edit_films(vector<Film> films) {
    int choice=1;
    while (choice == 1) {
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
        } else if(choice==2){
            cout<<"请输入要删除的电影序号或名称：";
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
            cin>>choice;
            continue;
        }
        // 询问用户是否要继续编辑电影
        cout << "[1]继续编辑 [2]提交操作：";
        cin>>choice;
        while (choice != 1 && choice != 2) {
            cout << "输入无效，请重新输入（y/n)" << endl;
            cin>>choice;
        }
    }
    cout<<"提交成功！"<<endl;
    return films;
}

class Admin {
public:
    static void check();
    static void main();
    static void sale();
};
void Admin::check() {
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
void Admin::sale() {
    vector<Arrangement> arrangements=load_arrangements(arrangements_json,seats_folder);
    show_arrangements(arrangements);
    cout<<"请输入你要查看的场次的座位表:";
    int choice;
    cin>>choice;
    show_seats(arrangements[choice].hall.seats);
}
void Admin::main() {
    re_start:
    int choice{};
    vector<Film> films = load_films(films_json);
    vector<Arrangement> arrangements = load_arrangements(arrangements_json,seats_folder);
    cout << "【欢迎来到影院管理员界面】\n[1]查看&编辑当前所有电影数据" << endl
         << "[2]查看每个场次的售票情况" << endl
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
            //查看每个排片的购票情况
            sale();
            goto re_start;
        } else if (choice == 3) {
            //进入排片系统
            show_arrangements(arrangements);
            save_arrangements(edit_arrangements(arrangements,films));
            show_arrangements(arrangements);
            goto re_start;
        } else if(choice==4){
            ::exit(4);
        }
        else {
            cout << "输入有误！请输入1~3：";
        }
    }
}
#endif //CINEMACPP_ADMIN_INFO_HPP