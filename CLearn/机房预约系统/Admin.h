#pragma once
#include <iostream>
using namespace std;
#include "Identity.h"
#include <vector>
#include "Student.h"
#include "Teacher.h"
#include "Room.h"

class Admin : public Identity
{
private:
    /* data */
public:
    Admin(/* args */);
    Admin(string name, string pwd);
    ~Admin();
    // 打开菜单
    virtual void openMenu();
    // 添加用户
    void addUser();
    // 查看用户
    void showUser();
    // 查看机房
    void showRoom();
    // 清空预约
    void clearOrder();
    // 加载用户数据
    void loadUserData();
    // 检测用户是否重复
    bool checkRepeat(int id, int type);
    // 学生数据容器
    vector<Student> vStudent;
    // 老师数据容器
    vector<Teacher> vTeacher;
    // 加载机房数据
    void loadRoomData();
    // 机房数据容器
    vector<Room> vRoom;
};
