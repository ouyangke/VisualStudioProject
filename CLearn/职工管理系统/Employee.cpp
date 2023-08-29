#include "Employee.h"

Employee::Employee(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

Employee::~Employee()
{
}

void Employee::showInfo()
{
    cout << "职工编号：" << this->m_Id
         << "\t职工姓名：" << this->m_Name
         << "\t职工岗位：" << this->getDeptName()
         << "\t岗位职责：负责干活" << endl;
}

string Employee::getDeptName()
{
    return "员工";
}