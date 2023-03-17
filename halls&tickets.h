//
// Created by AMagicPear on 2023/3/17.
//

#ifndef CINEMACPP_HALLS_TICKETS_H
#define CINEMACPP_HALLS_TICKETS_H
#include <vector>
using namespace std;
// 定义Hall类型为bool类型的二维vector表示座位表
typedef vector<vector<bool>> Hall_seats;
// 定义一个打印Hall座位表的函数
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

//定义一个影厅对象
class Hall{
public:
    int ID;
    Hall_seats seats;
    void print_seats() const{
        print_hall_seats(seats);
    }
};

// 定义一个函数，形参为int row, int col
Hall_seats create_hall(int row, int col) {
    // 使用std::vector的构造函数，创建一个row行col列的全部初始化为false的Hall对象
    Hall_seats hall(row, vector<bool>(col, false));
    // 返回Hall对象
    return hall;
}
//定义默认的两个影厅对象
Hall hall_default[2]={{1, create_hall(4,5)},
              {2, create_hall(5,5)}};

//购票思路：先给用户展示现有的排片。

#endif //CINEMACPP_HALLS_TICKETS_H
