#pragma once
#include <iostream>
#include <string>
using namespace std;

class Worker
{
private:
    /* data */
public:
    Worker(/* args */);
    ~Worker();
    // 显示个人信息
    virtual void showInfo() = 0;
    // 获取岗位名称
    virtual string getDeptName() = 0;

    int m_Id;      // 职工编号
    string m_Name; // 职工名
    int m_DeptId;  // 所在部门编号
};