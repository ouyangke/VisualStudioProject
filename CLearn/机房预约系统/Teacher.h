#pragma once
#include <iostream>
#include "Identity.h"
using namespace std;

class Teacher : public Identity
{
private:
    /* data */
public:
    Teacher(/* args */);
    Teacher(int empId, string name, string pwd);
    ~Teacher();
    // 职工号
    int empId;
    // 菜单
    virtual void openMenu();
    // 查看所有预约
    void showAllOrder();
    // 审核预约
    void validOrder();
};
