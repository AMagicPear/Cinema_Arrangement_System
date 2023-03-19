//
// Created by AMagicPear on 2023/3/19.
//
#include <iostream>
using namespace std;

int main_menu(){
    cout <<endl;
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "┃                                      ┃\t\n";
    cout << "┃             [1] 用    户             ┃\t\n";
    cout << "┃                                      ┃\t\n";
    cout << "┃             [2] 管 理 员             ┃\t\n";
    cout << "┃                                      ┃\t\n";
    cout << "┃             [0] 退    出             ┃\t\n";
    cout << "┃                                      ┃\t\n";
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
    cout << endl;
    int choice = -1;
    cout<<"【系统提示】请输入你的选择项（0-2）：";
    cin>>choice;
    return choice;
}