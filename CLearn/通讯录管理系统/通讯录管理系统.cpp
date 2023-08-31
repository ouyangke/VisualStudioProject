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
        system("read -p 'Press Enter to continue...' var");
        system("clear");
    }
}

// 显示联系人
void showPerson(PhoneBook *pb)
{
    if (pb->m_Size <= 0)
    {
        cout << "当前记录为空" << endl;
    }
    else
    {
        for (int i = 0; i < pb->m_Size; i++)
        {
            cout << "姓名：" << pb->personArray[i].m_Name << "\t";
            cout << "性别：" << (pb->personArray[i].m_Sex == 1 ? "男" : "女") << "\t";
            cout << "年龄：" << pb->personArray[i].m_Age << "\t";
            cout << "电话：" << pb->personArray[i].m_Phone << "\t";
            cout << "住址：" << pb->personArray[i].m_Address << endl;
        }
    }
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

// 检测联系人是否存在
int isExist(PhoneBook *pb, string name)
{
    for (int i = 0; i < pb->m_Size; i++)
    {
        if (pb->personArray[i].m_Name == name)
        {
            return i;
        }
    }
    return -1;
}

// 删除联系人
void deletePerson(PhoneBook *pb)
{
    cout << "请输入联系人姓名：" << endl;
    string name;
    cin >> name;
    int ret = isExist(pb, name);
    if (ret < 0)
    {
        cout << "查无此人" << endl;
    }
    else
    {
        for (int i = ret; i < pb->m_Size; i++)
        {
            pb->personArray[i] = pb->personArray[i + 1];
        }
        pb->m_Size--;
        cout << "删除联系人成功" << endl;
    }
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

// 查找联系人
void findPerson(PhoneBook *pb)
{
    cout << "请输入要查找的联系人姓名：" << endl;
    string name;
    cin >> name;
    int ret = isExist(pb, name);
    if (ret < 0)
    {
        cout << "查无此人" << endl;
    }
    else
    {
        cout << "姓名：" << pb->personArray[ret].m_Name << "\t";
        cout << "性别：" << (pb->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t";
        cout << "年龄：" << pb->personArray[ret].m_Age << "\t";
        cout << "电话：" << pb->personArray[ret].m_Phone << "\t";
        cout << "住址：" << pb->personArray[ret].m_Address << endl;
    }
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

// 修改联系人
void changePerson(PhoneBook *pb)
{
    cout << "请输入要修改的联系人姓名：" << endl;
    string name;
    cin >> name;
    int ret = isExist(pb, name);
    if (ret < 0)
    {
        cout << "查无此人" << endl;
    }
    else
    {
        // 姓名
        string name;
        cout << "请输入姓名：" << endl;
        cin >> name;
        pb->personArray[ret].m_Name = name;
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
                pb->personArray[ret].m_Sex = sex;
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
                pb->personArray[ret].m_Age = age;
                break;
            }

            cout << "输入错误，请重新输入" << endl;
        }
        // 电话
        cout << "请输入电话号码：" << endl;
        string phone;
        cin >> phone;
        pb->personArray[ret].m_Phone = phone;
        // 住址
        cout << "请输入住址：" << endl;
        string address;
        cin >> address;
        pb->personArray[ret].m_Address = address;
        cout << "修改用户成功" << endl;
    }
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

// 清空联系人
void clearPerson(PhoneBook *pb)
{
    pb->m_Size = 0;
    cout << "通讯录已清空" << endl;
    system("read -p 'Press Enter to continue...' var");
    system("clear");
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
            showPerson(&pb);
            break;
        case 3:
            // 删除联系人
            deletePerson(&pb);
            break;
        case 4:
            // 查找联系人
            findPerson(&pb);
            break;
        case 5:
            // 修改联系人
            changePerson(&pb);
            break;
        case 6:
            // 清空联系人
            clearPerson(&pb);
            break;
        default:
            // 没有该选项
            break;
        }
    }

    return 0;
}
