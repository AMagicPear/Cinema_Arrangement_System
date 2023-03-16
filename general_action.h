//#include "Audience Info.h"
#include "Basic Information.h"
#include <iostream>
#include <fstream>
#include <sstream>
//
// Created by AMagicPear on 2023/3/16.
//
void get_arrangements(Arrangement* ar) {
    fstream arrangement_film;
    string line;
    arrangement_film.open("data/arrangement.txt");
    if(!arrangement_film){
        cerr<<"无法打开文件"<<endl;
    }
    while (getline(arrangement_film, line)) {
        std::stringstream word(line);
        string film, type;
        int time_during, hall, year, month, day, hour, minute;
        word >> film >> type >> time_during >> hall >> year >> month >> day >> hour >> minute;
        cout << film << type << time_during << hall << year << month << day << hour << minute;
        cout << "DEBUG!";
//        Arrangement arr = {{film, type, time_during}, hall, {{year, month, day}, hour, minute}};
//        ar.push_back(arr);
    }
}