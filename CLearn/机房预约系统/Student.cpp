#include "Student.h"
#include <fstream>
#include "GlobalFile.h"
#include "OrderFile.h"

Student::Student()
{
}

Student::Student(int id, string name, string pwd)
{
    this->m_Id = id;
    this->m_User = name;
    this->m_Pwd = pwd;

    loadRoomData();
}

Student::~Student()
{
}

void Student::openMenu()
{
    cout << "******************************************" << endl;
    cout << "* 欢迎学生：" << this->m_User << "                          *" << endl;
    cout << "******************************************" << endl;
    cout << "*              1.申请预约                *" << endl;
    cout << "*              2.查看预约                *" << endl;
    cout << "*              3.查看所有                *" << endl;
    cout << "*              4.取消预约                *" << endl;
    cout << "*              0.注销登录                *" << endl;
    cout << "******************************************" << endl;
    cout << "请输入你的选择：" << endl;
}

void Student::applyOrder()
{
    cout << "机房开放时间为周一到周五" << endl;
    cout << "请输入预约日期：" << endl;
    cout << "1.周一" << endl;
    cout << "2.周二" << endl;
    cout << "3.周三" << endl;
    cout << "4.周四" << endl;
    cout << "5.周五" << endl;
    int date;
    while (true)
    {
        cin >> date;
        if (date >= 1 && date <= 5)
        {

            break;
        }
        cout << "输入有误，请重新输入：" << endl;
    }

    cout << "请输入预约时间：" << endl;
    cout << "1.上午" << endl;
    cout << "2.下午" << endl;
    int interval;
    while (true)
    {
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {

            break;
        }
        cout << "输入有误，请重新输入：" << endl;
    }

    cout << "请输入选择机房：" << endl;
    for (int i = 0; i < vRoom.size(); i++)
    {
        cout << "机房编号：" << vRoom[i].m_Id << "机房容量：" << vRoom[i].m_Max << endl;
    }
    int roomId;
    while (true)
    {
        cin >> roomId;
        if (roomId >= 1 && roomId <= 3)
        {

            break;
        }
        cout << "输入有误，请重新输入：" << endl;
    }

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "studentId:" << this->m_Id << " ";
    ofs << "studentName:" << this->m_User << " ";
    ofs << "roomId:" << roomId << " ";
    ofs << "status:" << 1 << endl;
    ofs.close();

    cout << "预约成功，审核中..." << endl;

    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void Student::showOrder()
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
            if (this->m_Id == atoi(of.m_OrderData[i]["studentId"].c_str()))
            {
                cout << "日期：周" << of.m_OrderData[i]["date"] << " ";
                cout << "时间：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
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
                    status += "预约失败";
                }
                else
                {
                    status += "预约已取消";
                }
                cout << status << endl;
            }
        }
    }

    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void Student::showAllOrder()
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
                status += "预约失败";
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

void Student::cancelOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
    }
    else
    {
        cout << "审核中或预约成功的记录可以取消，请输入取消的记录：" << endl;
        vector<int> v;
        int index = 1;
        for (int i = 0; i < of.m_Size; i++)
        {
            // 筛选自己的记录
            if (atoi(of.m_OrderData[i]["studentId"].c_str()) == this->m_Id)
            {
                v.push_back(i);
                cout << index++ << ".";
                cout << "日期：周" << of.m_OrderData[i]["date"] << " ";
                cout << "时间：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
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
                cout << status << endl;
            }
        }
        cout << "请输入要取消的记录,0代表返回" << endl;
        int select;

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
                    of.m_OrderData[select - 1]["status"] = "0";
                    of.updateOrder();
                    cout << "已取消预约" << endl;
                    break;
                }
            }
            cout << "输入有误，请重新输入：" << endl;
        }
    }

    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void Student::loadRoomData()
{
    ifstream ifs;
    ifs.open(ROOM_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        return;
    }
    Room r;
    while (ifs >> r.m_Id && ifs >> r.m_Max)
    {
        vRoom.push_back(r);
    }
    ifs.close();
}
