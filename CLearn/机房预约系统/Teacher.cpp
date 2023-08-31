#include "Teacher.h"
#include "OrderFile.h"
#include <vector>

Teacher::Teacher()
{
}

Teacher::Teacher(int empId, string name, string pwd)
{
    this->empId = empId;
    this->m_User = name;
    this->m_Pwd = pwd;
}

Teacher::~Teacher()
{
}

void Teacher::openMenu()
{
    cout << "******************************************" << endl;
    cout << "* 欢迎老师：" << this->m_User << "                          *" << endl;
    cout << "******************************************" << endl;
    cout << "*              1.查看预约                *" << endl;
    cout << "*              2.审核预约                *" << endl;
    cout << "*              0.注销登录                *" << endl;
    cout << "******************************************" << endl;
    cout << "请输入你的选择：" << endl;
}

void Teacher::showAllOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
    }
    else
    {
        for (int i = 0; i < of.m_Size; i++)
        {
            cout << "日期：周" << of.m_OrderData[i]["date"] << " ";
            cout << "时间：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
            cout << "学号：" << of.m_OrderData[i]["studentId"] << " ";
            cout << "姓名：" << of.m_OrderData[i]["studentName"] << " ";
            cout << "机房：" << of.m_OrderData[i]["roomId"] << "号 ";
            string status = "状态：";
            string statusCode = of.m_OrderData[i]["status"];
            if (statusCode == "1")
            {
                status += "审核中";
            }
            else if (statusCode == "2")
            {
                status += "预约成功";
            }
            else if (statusCode == "-1")
            {
                status += "预约失败,审核未通过";
            }
            else
            {
                status += "预约已取消";
            }
            cout << status << endl;
        }
    }
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void Teacher::validOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
    }
    else
    {
        vector<int> v;
        int index = 0;
        cout << "待审核的预约记录如下：" << endl;
        for (int i = 0; i < of.m_Size; i++)
        {
            if (of.m_OrderData[i]["status"] == "1")
            {
                v.push_back(i);
                cout << ++index << ".";
                cout << "日期：周" << of.m_OrderData[i]["date"] << " ";
                cout << "时间：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
                cout << "学号：" << of.m_OrderData[i]["studentId"] << " ";
                cout << "姓名：" << of.m_OrderData[i]["studentName"] << " ";
                cout << "机房：" << of.m_OrderData[i]["roomId"] << "号 ";
                string status = "状态：审核中";
                cout << status << endl;
            }
        }
        cout << "请输入要审核的记录,0代表返回" << endl;
        int select;
        int ret;
        while (true)
        {
            cin >> select;
            if (select >= 0 && select <= v.size())
            {
                if (select == 0)
                {
                    break;
                }
                else
                {
                    cout << "请输入审核结果：" << endl;
                    cout << "1.通过" << endl;
                    cout << "2.不通过" << endl;
                    cin >> ret;
                    if (ret == 1)
                    {
                        of.m_OrderData[select - 1]["status"] = "2";
                    }
                    else
                    {
                        of.m_OrderData[select - 1]["status"] = "-1";
                    }

                    of.updateOrder();
                    cout << "审核完毕" << endl;
                    break;
                }
            }
            cout << "输入有误，请重新输入：" << endl;
        }
    }
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}
