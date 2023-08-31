#include "Admin.h"
#include <fstream>
#include "GlobalFile.h"
#include <algorithm>
using namespace std;

Admin::Admin()
{
}

Admin::Admin(string name, string pwd)
{
    this->m_User = name;
    this->m_Pwd = pwd;

    this->loadUserData();
    this->loadRoomData();
}

Admin::~Admin()
{
}

void Admin::openMenu()
{
    cout << "******************************************" << endl;
    cout << "* 欢迎管理员：" << this->m_User << "                      *" << endl;
    cout << "******************************************" << endl;
    cout << "*              1.添加账号                *" << endl;
    cout << "*              2.查看账号                *" << endl;
    cout << "*              3.查看机房                *" << endl;
    cout << "*              4.清空预约                *" << endl;
    cout << "*              0.注销登录                *" << endl;
    cout << "******************************************" << endl;
    cout << "请输入你的选择：" << endl;
}

void Admin::addUser()
{
    cout << "请输入添加的账号类型：" << endl;
    cout << "1.添加学生" << endl;
    cout << "2.添加老师" << endl;

    string fileName;
    string tip;
    string errorTip;
    ofstream ofs;
    int select;
    cin >> select;
    if (select == 1)
    {
        fileName = STUDENT_FILE;
        tip = "请输入学号：";
        errorTip = "学号重复，请重新输入：";
    }
    else
    {
        fileName = TEACHER_FILE;
        tip = "请输入职工号：";
        errorTip = "职工号重复，请重新输入：";
    }
    ofs.open(fileName, ios::app);
    int id;
    string name;
    string pwd;
    cout << tip << endl;
    while (true)
    {
        cin >> id;
        bool ret = checkRepeat(id, select);
        if (ret)
        {
            cout << errorTip << endl;
        }
        else
        {
            break;
        }
    }

    cout << "请输入用户名：" << endl;
    cin >> name;
    cout << "请输入密码：" << endl;
    cin >> pwd;
    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "添加成功" << endl;
    loadUserData();
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void printStudent(Student &student)
{
    cout << "学号：" << student.m_Id << " 姓名：" << student.m_User << " 密码：" << student.m_Pwd << endl;
}
void printTeacher(Teacher &teacher)
{
    cout << "职工号：" << teacher.empId << " 姓名：" << teacher.m_User << " 密码：" << teacher.m_Pwd << endl;
}
void Admin::showUser()
{
    cout << "请选择要查看的内容：" << endl;
    cout << "1.查看所有学生" << endl;
    cout << "2.查看所有老师" << endl;
    int select;
    cin >> select;
    switch (select)
    {
    case 1:
        for_each(vStudent.begin(), vStudent.end(), printStudent);
        break;
    case 2:
        for_each(vTeacher.begin(), vTeacher.end(), printTeacher);
        break;
    default:
        cout << "未查询到有效内容" << endl;
        break;
    }
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void printRoom(Room &r)
{
    cout << "编号：" << r.m_Id << " 容量：" << r.m_Max << endl;
}

void Admin::showRoom()
{
    cout << "机房信息如下：" << endl;
    for_each(vRoom.begin(), vRoom.end(), printRoom);
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void Admin::clearOrder()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();
    cout << "清空预约成功" << endl;
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void Admin::loadUserData()
{
    vStudent.clear();
    vTeacher.clear();

    ifstream ifs1;
    ifs1.open(STUDENT_FILE, ios::in);
    if (!ifs1.is_open())
    {
        cout << "文件读取失败" << endl;
        return;
    }
    Student s;
    while (ifs1 >> s.m_Id && ifs1 >> s.m_User && ifs1 >> s.m_Pwd)
    {
        vStudent.push_back(s);
    }
    ifs1.close();

    ifstream ifs2;
    ifs2.open(TEACHER_FILE, ios::in);
    if (!ifs2.is_open())
    {
        cout << "文件读取失败" << endl;
        return;
    }
    Teacher t;
    while (ifs2 >> t.empId && ifs2 >> t.m_User && ifs2 >> t.m_Pwd)
    {
        vTeacher.push_back(t);
    }
    ifs2.close();
}

bool Admin::checkRepeat(int id, int type)
{
    if (type == 1)
    {
        for (vector<Student>::iterator it = vStudent.begin(); it != vStudent.end(); it++)
        {
            if (it->m_Id == id)
            {
                return true;
            }
        }
    }
    else
    {
        for (vector<Teacher>::iterator it = vTeacher.begin(); it != vTeacher.end(); it++)
        {
            if (it->empId == id)
            {
                return true;
            }
        }
    }

    return false;
}

void Admin::loadRoomData()
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
