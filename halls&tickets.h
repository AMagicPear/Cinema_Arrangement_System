//
// Created by AMagicPear on 2023/3/17.
//

#ifndef CINEMACPP_HALLS_TICKETS_H
#define CINEMACPP_HALLS_TICKETS_H
#include <vector>
using namespace std;
// 定义Hall类型为bool类型的二维vector表示座位表
typedef vector<vector<bool>> Hall_seats;
//定义一个影厅对象
class Hall{
public:
    int ID;
    Hall_seats seats;
};

// 定义一个打印Hall座位表的成员函数
void print_hall_seats(const Hall_seats& hall) {
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
}
// 定义一个函数，形参为int row, int col
Hall_seats create_hall(int row, int col) {
    // 使用std::vector的构造函数，创建一个row行col列的全部初始化为false的Hall对象
    Hall_seats hall(row, vector<bool>(col, false));
    // 返回Hall对象
    return hall;
}

// 定义一个读取本地文件并返回vector<Hall_seats>的函数
vector<Hall_seats> load_halls(const string& filename) {
    // 创建一个空的vector<Hall_seats>对象
    vector<Hall_seats> halls;
    // 打开文件，使用二进制模式和输入模式
    ifstream file(filename, ios::binary | ios::in);
    // 如果文件打开失败，抛出异常
    if (!file.is_open()) {
        throw runtime_error("Failed to open file");
    }
    // 循环读取文件直到结束
    while (!file.eof()) {
        // 创建一个空的Hall对象
        Hall_seats hall;
        // 声明两个变量用来存储行数和列数
        size_t rows, cols;
        // 尝试从文件中读取行数和列数，如果失败或者没有数据，则跳出循环
        if (!file.read(reinterpret_cast<char*>(&rows), sizeof(rows)) ||
            !file.read(reinterpret_cast<char*>(&cols), sizeof(cols))) {
            break;
        }
        // 调整Hall对象的大小为rows x cols，并初始化为false
        hall.resize(rows, vector<bool>(cols, false));
        // 遍历每一行
        for (auto& row : hall) {
            // 创建一个char数组，大小为cols * sizeof(bool)
            char buffer[cols * sizeof(bool)];
            // 尝试从文件中读取char数组，如果失败，则跳出循环
            if (!file.read(buffer, cols * sizeof(bool))) {
                break;
            }
            // 使用std::copy把char数组复制到每一行中
            std::copy(buffer, buffer + cols * sizeof(bool), row.begin());
        }
        halls.push_back(hall);
    }
    return halls;
}

//购票思路：先给用户展示现有的排片。

#endif //CINEMACPP_HALLS_TICKETS_H
