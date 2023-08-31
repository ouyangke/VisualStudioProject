#pragma once
#include <iostream>
using namespace std;
// 身份基类
class Identity
{
private:
    /* data */
public:
    Identity(/* args */);
    ~Identity();

    // 用户名
    string m_User;
    // 密码
    string m_Pwd;
    // 菜单
    virtual void openMenu() = 0;
};
