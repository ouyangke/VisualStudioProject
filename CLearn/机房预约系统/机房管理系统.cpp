#include <iostream>
using namespace std;
#include "Identity.h"
#include <fstream>
#include "GlobalFile.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"

/**
 * 管理员菜单
 */
void managerMenu(Identity *&identity)
{
    while (true)
    {
        identity->openMenu();
        Admin *admin = (Admin *)identity;
        int select;
        cin >> select;
        switch (select)
        {
        case 1:
            // 添加账号
            admin->addUser();
            break;
        case 2:
            // 查看账号
            admin->showUser();
            break;
        case 3:
            // 查看机房
            admin->showRoom();
            break;
        case 4:
            // 清空预约
            admin->clearOrder();
            break;
        default:
            delete identity;
            cout << "注销成功" << endl;
            system("read -p 'Press Enter to continue...' var");
            system("clear");
            break;
        }
    }
}

/**
 * 学生菜单
 */
void studentMenu(Identity *&identity)
{
    while (true)
    {
        identity->openMenu();
        Student *student = (Student *)identity;
        int select;
        cin >> select;
        switch (select)
        {
        case 1:
            // 申请预约
            student->applyOrder();
            break;
        case 2:
            // 查看预约
            student->showOrder();
            break;
        case 3:
            // 查看所有
            student->showAllOrder();
            break;
        case 4:
            // 取消预约
            student->cancelOrder();
            break;
        default:
            delete identity;
            cout << "注销成功" << endl;
            system("read -p 'Press Enter to continue...' var");
            system("clear");
            break;
        }
    }
}

/**
 * 老师菜单
 */
void teacherMenu(Identity *&identity)
{
    while (true)
    {
        identity->openMenu();
        Teacher *teacher = (Teacher *)identity;
        int select;
        cin >> select;
        switch (select)
        {
        case 1:
            // 查看所有预约
            teacher->showAllOrder();
            break;
        case 2:
            // 审核预约
            teacher->validOrder();
            break;
        default:
            delete identity;
            cout << "注销成功" << endl;
            system("read -p 'Press Enter to continue...' var");
            system("clear");
            break;
        }
    }
}

/**
 * 登录
 */
void loginIn(string fileName, int type)
{
    Identity *user = NULL;

    ifstream ifs;
    ifs.open(fileName, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    int id = 0;
    string name;
    string pwd;

    // 录入编号
    switch (type)
    {
    case 1:
        // 学生登录
        cout << "请输入学号：" << endl;
        cin >> id;
        break;
    case 2:
        // 老师登录
        cout << "请输入职工号：" << endl;
        cin >> id;
        break;
    case 3:
        // 管理员登录
        break;
    default:
        break;
    }

    // 录入账号密码
    cout << "请输入用户名：" << endl;
    cin >> name;
    cout << "请输入密码：" << endl;
    cin >> pwd;

    // 验证密码
    if (type == 1)
    {
        // 学生登录
        int fId;
        string fName;
        string fPwd;
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "学生登录成功" << endl;
                system("read -p 'Press Enter to continue...' var");
                system("clear");
                user = new Student(id, name, pwd);
                // 进入学生界面
                studentMenu(user);
                return;
            }
        }
    }
    else if (type == 2)
    {
        // 老师登录
        int fId;
        string fName;
        string fPwd;
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "老师登录成功" << endl;
                system("read -p 'Press Enter to continue...' var");
                system("clear");
                user = new Teacher(id, name, pwd);
                // 进入老师界面
                teacherMenu(user);
                return;
            }
        }
    }
    else if (type == 3)
    {
        // 管理员登录
        string fName;
        string fPwd;
        while (ifs >> fName && ifs >> fPwd)
        {
            if (fName == name && fPwd == pwd)
            {
                cout << "管理员登录成功" << endl;
                system("read -p 'Press Enter to continue...' var");
                system("clear");
                user = new Admin(name, pwd);
                // 进入管理员界面
                managerMenu(user);
                return;
            }
        }
    }
    cout << "验证登录失败" << endl;
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

int main(int argc, char const *argv[])
{
    int select;
    while (true)
    {
        cout << "********** 欢迎来到机房预约系统 **********" << endl;
        cout << "* 请选择你的身份：                       *" << endl;
        cout << "******************************************" << endl;
        cout << "*              1.学    生                *" << endl;
        cout << "*              2.老    师                *" << endl;
        cout << "*              3.管 理 员                *" << endl;
        cout << "*              0.退    出                *" << endl;
        cout << "******************************************" << endl;
        cout << "请输入你的选择：" << endl;

        cin >> select;
        switch (select)
        {
        case 0:
            // 退出
            cout << "欢迎下次使用" << endl;
            system("read -p 'Press Enter to continue...' var");
            return 0;
            break;
        case 1:
            // 学生
            loginIn(STUDENT_FILE, 1);
            break;
        case 2:
            // 老师
            loginIn(TEACHER_FILE, 2);
            break;
        case 3:
            // 管理员
            loginIn(ADMIN_FILE, 3);
            break;
        default:
            cout << "输入有误，请重新输入！" << endl;
            system("read -p 'Press Enter to continue...' var");
            system("clear");
            break;
        }
    }

    return 0;
}
