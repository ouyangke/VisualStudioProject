#pragma once        // 防止头文件重复包含
#include <iostream> //导入输入输出流
#include <fstream>
#include "Worker.h"
#include "Employee.h"
#include "Manager.h"
#include "Boss.h"
#include <string>
using namespace std; // 使用命名空间

#define FILENAME "empFile.txt"

class WorkManager
{
private:
    /* data */
public:
    int m_EmpNum;
    Worker **m_EmpAar;
    bool m_FilIsEmpty;

    WorkManager(/* args */);
    ~WorkManager();
    // 展示菜单
    void menu();
    // 保存文件
    void save();
    // 加载文件
    void load();
    // 判断是否存在
    int isExist(int id);
    int isExist(string name);
    // 退出系统
    void quit();
    // 添加
    void add();
    // 显示
    void show();
    // 删除
    void remove();
    // 查找
    void find();
    // 修改
    void change();
    // 排序
    void sort();
    // 清空
    void clean();
};
