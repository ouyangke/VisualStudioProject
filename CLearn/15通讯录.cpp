#include <iostream>
#include <string>

#define MAX 1000

using namespace std;

// 联系人
struct Person
{
    // 名字
    string m_Name;
    // 性别:1男 2女
    int m_Sex;
    // 年龄
    int m_Age;
    // 电话
    string m_Phone;
    // 住址
    string m_Address;
};

// 通讯录
struct PhoneBook
{
    struct Person personArray[MAX];
    int m_Size;
};

// 定义菜单函数
void showMenu()
{
    cout << "********************************" << endl;
    cout << "********  1.添加联系人  ********" << endl;
    cout << "********  2.显示联系人  ********" << endl;
    cout << "********  3.删除联系人  ********" << endl;
    cout << "********  4.查找联系人  ********" << endl;
    cout << "********  5.修改联系人  ********" << endl;
    cout << "********  6.清空联系人  ********" << endl;
    cout << "********  0.退出通讯录  ********" << endl;
    cout << "********************************" << endl;
}

// 添加联系人
void addPerson(PhoneBook *pb)
{
    if (pb->m_Size >= MAX)
    {
        cout << "通讯录已满，无法添加！" << endl;
        return;
    }
    else
    {
        // 姓名
        string name;
        cout << "请输入姓名：" << endl;
        cin >> name;
        pb->personArray[pb->m_Size].m_Name = name;
        // 性别
        cout << "请输入性别：" << endl;
        cout << "1.男" << endl;
        cout << "2.女" << endl;
        int sex = 0;
        while (true)
        {
            cin >> sex;
            if (sex == 1 || sex == 2)
            {
                pb->personArray[pb->m_Size].m_Sex = sex;
                break;
            }
            cout << "输入错误，请重新输入" << endl;
        }
        // 年龄
        cout << "请输入年龄：" << endl;
        int age = 0;
        while (true)
        {
            cin >> age;
            if (age > 0 && age < 200)
            {
                pb->personArray[pb->m_Size].m_Age = age;
                break;
            }

            cout << "输入错误，请重新输入" << endl;
        }
        // 电话
        cout << "请输入电话号码：" << endl;
        string phone;
        cin >> phone;
        pb->personArray[pb->m_Size].m_Phone = phone;
        // 住址
        cout << "请输入住址：" << endl;
        string address;
        cin >> address;
        pb->personArray[pb->m_Size].m_Address = address;

        pb->m_Size++;

        cout << "添加用户成功" << endl;
    }
}

int main(int argc, char const *argv[])
{
    PhoneBook pb;
    pb.m_Size = 0;

    int select = 0;

    while (true)
    {
        showMenu();

        cin >> select;

        switch (select)
        {
        case 0:
            // 退出通讯录
            cout << "欢迎下次使用" << endl;
            return 0;
            break;
        case 1:
            // 添加联系人
            addPerson(&pb);
            break;
        case 2:
            // 显示联系人
            break;
        case 3:
            // 删除联系人
            break;
        case 4:
            // 查找联系人
            break;
        case 5:
            // 修改联系人
            break;
        case 6:
            // 清空联系人
            break;
        default:
            // 没有该选项
            break;
        }
    }

    return 0;
}
