#include "Manager.h"

Manager::Manager(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

Manager::~Manager()
{
}

void Manager::showInfo()
{
    cout << "职工编号：" << this->m_Id
         << "\t职工姓名：" << this->m_Name
         << "\t职工岗位：" << this->getDeptName()
         << "\t岗位职责：负责管理员工" << endl;
}

string Manager::getDeptName()
{
    return string("经理");
}