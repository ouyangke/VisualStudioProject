#pragma once
#include <iostream>
using namespace std;
#include <map>
#include <string>

class OrderFile
{
private:
    /* data */
public:
    OrderFile(/* args */);
    ~OrderFile();
    // 更新预约记录
    void updateOrder();
    // 预约条数
    int m_Size;
    // 所有预约记录数据容器
    map<int, map<string, string>> m_OrderData;
};