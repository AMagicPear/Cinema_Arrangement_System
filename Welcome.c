//
// Created by AMagicPear on 2023/3/13.
//

#include <stdio.h>

//欢迎和用户界面：要求用户选择一个身份，函数返回身份所对应的值，1为观众，2为管理员
int PrintStartScreen_Choice(){
    printf("------欢迎进入模拟影院售票系统-------");//ToDo：优化界面
    printf("请选择您的身份：[1] 观众\t [2] 管理员\n");
    int user_Choice=0;
    while (1) {
        scanf("%d",&user_Choice);
        if(!(user_Choice==1||user_Choice==2)){
            printf("输入有误！请输入1或2以选择：");
            continue;
        }else break;
    }
    return user_Choice;
}