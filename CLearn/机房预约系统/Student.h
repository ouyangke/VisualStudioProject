#pragma once
#include <iostream>
#include "Identity.h"
using namespace std;
#include <vector>
#include "Room.h"

class Student : public Identity
{
private:
    /* data */
public:
    Student(/* args */);
    Student(int id, string name, string pwd);
    ~Student();

    // 学号
    int m_Id;
    // 机房容器
    vector<Room> vRoom;
    // 菜单
    virtual void openMenu();
    // 申请预约
    void applyOrder();
    // 查看预约
    void showOrder();
    // 查看所有预约
    void showAllOrder();
    // 取消预约
    void cancelOrder();
    // 加载机房数据
    void loadRoomData();
};