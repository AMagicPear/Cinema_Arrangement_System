//
// Created by AMagicPear on 2023/3/15.
//

#ifndef CINEMACPP_AUDIENCE_INFO_HPP
#define CINEMACPP_AUDIENCE_INFO_HPP
//#define DEBUG
#define USER_NUM 100
#include "Basic Information.hpp"
//定义用户
class User {
public:
    string ID;                     //用户名
//    string password;             //密码
    vector<Ticket> tickets;        //持有的票
    static int welcome();
    static void main();
    static void menu(const string& ID_input);
    static string regi();
    static string login();
    void Buy_Ticket();
    void Return_Ticket();
    void Show_Ticket();
};
//保存用户购票
void save_user(User user) {
    json j;
    string file_path = ((string) user_folder) + "/" + user.ID + ".json";
    for (int i = 0; i < size(user.tickets); ++i) {
        j.push_back({{"film", {
                {"name", user.tickets[i].film.name},
                {"type", user.tickets[i].film.type},
                {"time_during", user.tickets[i].film.time_during}
        }}, {"begin_time", {
                {"date", {
                        {"year", user.tickets[i].begin_time.date.year},
                        {"month", user.tickets[i].begin_time.date.month},
                        {"day", user.tickets[i].begin_time.date.day}
                }},
                {"hour", user.tickets[i].begin_time.hour},
                {"minute", user.tickets[i].begin_time.minute}}
                     },{"seatLocation",{
                         {"row",user.tickets[i].seatLocation.row},
                         {"col",user.tickets[i].seatLocation.col}
                     }

        }});
    }
    ofstream file(file_path);
    file<<j.dump(4);
    file.close();
}
//用户购票
void User::Buy_Ticket(){
    Arrangements arrangements(load_arrangements(arrangements_json,seats_folder));
    show_arrangements(arrangements);
    int choice;
    while (true) {
        cout << "请选择购买哪一场（输入序号）：";
        cin >> choice;
        if (choice < 0 || choice >= size(arrangements)) {
            cout << "输入序号不合法！" << endl;
            continue;
        } else break;
    }
    Arrangement ar_choice = arrangements[choice];
    SeatLocation seatLocation{};
    print_hall_seats(ar_choice.hall.seats);
    cout<<"选择座位（行 列）：";
    cin>>seatLocation.row>>seatLocation.col;
    seatLocation.row--,seatLocation.col--;
    Ticket ticket(ar_choice,seatLocation);
    tickets.push_back(ticket);
    save_user(*this);
}
void User::Return_Ticket() {

}
void User::Show_Ticket() {

}
bool isID_exist(const string&,const string&);

//打印用户菜单界面
void User::menu(const string& ID_input) {
    printf("【系统】欢迎%s！！！\n", ID_input.c_str());
    printf("***************************************************\n");
    printf("**********         欢迎光临！         *************\n");
    printf("**********         1-- 购票           *************\n");
    printf("**********         2-- 退票           *************\n");
    printf("**********         0-- 退出           *************\n");
    printf("【系统】请您选择您要实现的功能（数字）：");
}
//要求用户选择注册或登录，并返回值
int User::welcome(){
    cout<<"====用户===="<<endl;
    printf("1. 注册\t 2. 登录\n");
    int user_Choice=0;
    while (true) {
        cin>>user_Choice;
        if(!(user_Choice==1||user_Choice==2)){
            printf("输入有误！请输入1或2以选择：");
            continue;
        }else break;
    }
    return user_Choice;
}

//用户主函数
void User::main() {
    string userID{};
    re_choose_main:
    //判断注册和登录分支
    int user_Choice = welcome();
    switch (user_Choice) {
        case 1: //进入注册分支
            userID = regi();
        case 2: //进入登录分支
        {
            if(user_Choice==2) userID = login();
            User::menu(userID);
            User user;
            user.ID=userID;
            int user_Choice_menu;
            cin>>user_Choice_menu;

            //进入购票
            if(user_Choice_menu==1)
                user.Buy_Ticket();
            else if(user_Choice_menu==2)
                user.Return_Ticket();
            else break;
        }
        default:
            cerr<<"请输入1或2！"<<endl;
            goto re_choose_main;
    }
}

// 注册函数，返回注册成功的用户名
string User::regi() {
    string username; // 用户名
    string password; // 密码
    while (true) {
        cout<<"====注册===="<<endl;
        cout << "请输入用户名：";
        cin >> username;
        if (isID_exist(username,user_info)) {
            cout <<username<<"已被注册，请重新输入用户名！" << endl;
            continue;
        }
        break;
    }
    cout << "请输入密码：";
    cin >> password;
    // 打开用户信息文件
    ofstream outfile(user_info, ios::app);
    if (!outfile) {
        cerr << "无法打开文件" << endl;
        exit(1);
    }
    // 写入用户名和密码，用空格分隔
    outfile << username << " " << password << endl;
    // 关闭文件
    outfile.close();
    cout <<username<< "注册成功！" << endl;
    return username;
}

// 登录函数，返回登录成功的用户名，如果失败则返回空字符串
string User::login() {
    string username; // 用户名
    string password; // 密码
    string line;     // 文件中的一行
    cout<<"====登录===="<<endl;
    cout << "请输入用户名：";
    cin >> username;

    // 打开用户信息文件
    ifstream infile(user_info);
    if (!infile) {
        cerr << "无法打开文件" << endl;
        exit(1);
    }
    // 逐行读取文件内容
    while (getline(infile, line)) {
        std::stringstream word(line);
        string user,pass;
        word>>user>>pass;
        if (user == username)                // 如果找到匹配的用户名，则比对密码是否正确
        {
            cout << "请输入密码：";
            cin >> password;
            if (pass == password)            // 如果密码正确，则返回该用户名，并关闭文件
            {
                cout << "登录成功！" << endl;
                infile.close();
                return user;
            } else                             // 如果密码错误，则提示用户选择重新输入或注册，并关闭文件
            {
                cout << "密码错误！请选择：" << endl;
                cout << "[1]重新输入 [2]注册账号 [3]退出程序" << endl;
                int choice;
                cin >> choice;
                infile.close();
                switch (choice) {
                    case 1:
                        return login();
                        break;   // 重新调用登录函数
                    case 2:
                        User::regi();
                        break;       // 调用注册函数
                    case 3:
                        exit(0);
                        break;              // 退出程序
                    default:
                        return "";
                        break;           // 返回空字符串
                }
            }
        }
    }
    // 如果没有找到匹配的用户名，则提示用户选择重新输入或注册，并关闭文件
    infile.close();

    cout << "用户名不存在！请选择：" << endl;
    cout << "[1]重新输入 [2]注册账号 [3]退出程序" << endl;
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            return login();
            break;   // 重新调用登录函数
        case 2:
            User::regi();
            break;       // 调用注册函数
        case 3:
            exit(0);
            break;              // 退出程序
        default:
            return "";
            break;           //返回空字符串
    }
    return "";
}


//检查传入的ID是否已被注册，若是则返回true
bool isID_exist(const string& ID_input,const string& filename){
    //打开存储所有用户信息的accounts.txt文件
    fstream accounts_file;
    accounts_file.open(filename,std::ios::in);
    if(!accounts_file.is_open()){
        cerr<<"cannot open the accounts_file!";
        ::exit(0);
    }
    char* line= (char*) ::malloc(sizeof(char*)*USER_NUM);
    while (accounts_file.getline(line, sizeof(char*)*USER_NUM)){
        string get_name;
        std::stringstream word(line);
        word >> get_name;
        if(ID_input==get_name){
            ::free(line);
            accounts_file.close();
            return true;
        }
    }
    ::free(line);
    accounts_file.close();
    return false;
}

#endif //CINEMACPP_AUDIENCE_INFO_HPP