#include "WorkManager.h"

WorkManager::WorkManager(/* args */)
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        this->m_EmpNum = 0;
        this->m_EmpAar = NULL;
        this->m_FilIsEmpty = true;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "文件为空" << endl;
        this->m_EmpNum = 0;
        this->m_EmpAar = NULL;
        this->m_FilIsEmpty = true;
        ifs.close();
        return;
    }

    this->load();
}

WorkManager::~WorkManager()
{
    // todo 清理
}

void WorkManager::menu()
{
    cout << "**********************************" << endl;
    cout << "*******欢迎使用职工管理系统*******" << endl;
    cout << "********  1.添加职工信息  ********" << endl;
    cout << "********  2.显示职工信息  ********" << endl;
    cout << "********  3.删除离职职工  ********" << endl;
    cout << "********  4.查找职工信息  ********" << endl;
    cout << "********  5.修改职工信息  ********" << endl;
    cout << "********  6.按照编号排序  ********" << endl;
    cout << "********  7.清空所有文档  ********" << endl;
    cout << "********  0.退出管理程序  ********" << endl;
    cout << "**********************************" << endl;
    cout << endl;
}

void WorkManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpAar[i]->m_Id << " "
            << this->m_EmpAar[i]->m_Name << " "
            << this->m_EmpAar[i]->m_DeptId << endl;
    }
}

void WorkManager::load()
{
    int id;
    string name;
    int dId;

    // 统计人数
    ifstream ifs1;
    ifs1.open(FILENAME, ios::in);
    int count = 0;
    while (ifs1 >> id && ifs1 >> name && ifs1 >> dId)
    {
        count++;
    }
    ifs1.close();
    // 开辟空间
    this->m_EmpNum = count;
    this->m_EmpAar = new Worker *[this->m_EmpNum];

    // 加载成员
    ifstream ifs2;
    ifs2.open(FILENAME, ios::in);
    int index = 0;
    while (ifs2 >> id && ifs2 >> name && ifs2 >> dId)
    {
        Worker *worker = NULL;
        switch (dId)
        {
        case 1:
            worker = new Employee(id, name, dId);
            break;
        case 2:
            worker = new Manager(id, name, dId);
            break;
        case 3:
            worker = new Boss(id, name, dId);
            break;
        default:
            break;
        }
        this->m_EmpAar[index] = worker;
        index++;
    }
    ifs2.close();
}

int WorkManager::isExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpAar[i]->m_Id == id)
        {
            index = i;
            break;
        }
    }

    return index;
}

int WorkManager::isExist(string name)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpAar[i]->m_Name == name)
        {
            index = i;
            break;
        }
    }

    return index;
}

void WorkManager::quit()
{
    cout << "欢迎下次使用" << endl;
    exit(0);
}

void WorkManager::add()
{
    cout << "请输入添加职工的数量：" << endl;
    int addNum;
    cin >> addNum;
    if (addNum > 0)
    {
        int newSize = this->m_EmpNum + addNum;
        Worker **newSpace = new Worker *[newSize];
        if (this->m_EmpAar != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpAar[i];
            }
        }

        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int dId;
            cout << "请输入第" << i + 1 << "个人的编号:" << endl;
            cin >> id;
            cout << "请输入第" << i + 1 << "个人的姓名:" << endl;
            cin >> name;
            cout << "请选择该员工岗位:" << endl;
            cout << "1.员工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> dId;
            Worker *worker = NULL;
            switch (dId)
            {
            case 1:
                worker = new Employee(id, name, dId);
                break;
            case 2:
                worker = new Manager(id, name, dId);
                break;
            case 3:
                worker = new Boss(id, name, dId);
                break;
            default:
                break;
            }

            newSpace[this->m_EmpNum + i] = worker;
        }
        delete[] this->m_EmpAar;
        this->m_EmpAar = newSpace;
        this->m_EmpNum = newSize;

        this->save();
        this->m_FilIsEmpty = false;
        cout << "成功添加" << addNum << "名新员工" << endl;
    }
    else
    {
        cout << "输入有误" << endl;
    }

    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void WorkManager::show()
{
    if (this->m_FilIsEmpty)
    {
        cout << "文件不存在或者为空" << endl;
    }
    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            this->m_EmpAar[i]->showInfo();
        }
        system("read -p 'Press Enter to continue...' var");
        system("clear");
    }
}

void WorkManager::remove()
{
    if (this->m_FilIsEmpty)
    {
        cout << "文件不存在或者记录为空" << endl;
        return;
    }

    cout << "请输入想要删除的职工的编号：" << endl;
    int id = 0;
    cin >> id;
    int index = this->isExist(id);
    if (index != -1)
    {
        for (int i = 0; i < this->m_EmpNum - 1; i++)
        {
            this->m_EmpAar[i] = this->m_EmpAar[i + 1];
        }
        this->m_EmpNum--;
        this->save();
        cout << "删除成功" << endl;
    }
    else
    {
        cout << "删除失败，未找到该员工" << endl;
    }
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void WorkManager::find()
{
    if (this->m_FilIsEmpty)
    {
        cout << "文件不存在或者记录为空" << endl;
        return;
    }
    cout << "请输入查找方式：" << endl;
    cout << "1.按编号查找" << endl;
    cout << "2.按姓名查找" << endl;
    int findType;
    int index = -1;
    int id;
    string name;
    cin >> findType;
    switch (findType)
    {
    case 1:
        cout << "请输入查找的编号：" << endl;
        cin >> id;
        index = this->isExist(id);
        break;
    case 2:
        cout << "请输入查找的姓名：" << endl;
        cin >> name;
        index = this->isExist(name);
        break;
    default:
        break;
    }

    if (index != -1)
    {
        cout << "查找成功，查到员工：" << endl;
        this->m_EmpAar[index]->showInfo();
    }
    else
    {
        cout << "查找失败，查无此人" << endl;
    }
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void WorkManager::change()
{
    if (this->m_FilIsEmpty)
    {
        cout << "文件不存在或者记录为空" << endl;
        return;
    }
    cout << "请输入要修改的员工编号：" << endl;
    int id;
    cin >> id;
    int index = this->isExist(id);
    if (index != -1)
    {
        delete this->m_EmpAar[index];
        int newId;
        string newName;
        int newDid;
        cout << "请输入新编号：" << endl;
        cin >> newId;
        cout << "请输入新名字：" << endl;
        cin >> newName;
        cout << "请输入新岗位" << endl;
        cout << "1.员工" << endl;
        cout << "2.经理" << endl;
        cout << "3.老板" << endl;
        cin >> newDid;

        Worker *worker = NULL;
        switch (newDid)
        {
        case 1:
            worker = new Employee(newId, newName, newDid);
            break;
        case 2:
            worker = new Manager(newId, newName, newDid);
            break;
        case 3:
            worker = new Boss(newId, newName, newDid);
            break;
        default:
            break;
        }
        this->m_EmpAar[index] = worker;
        this->save();
        cout << "修改成功" << endl;
    }
    else
    {
        cout << "修改失败，查无此人" << endl;
    }
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void WorkManager::sort()
{
    if (this->m_FilIsEmpty)
    {
        cout << "文件不存在或者记录为空" << endl;
        system("read -p 'Press Enter to continue...' var");
        system("clear");
        return;
    }
    cout << "请输入排序方式：" << endl;
    cout << "1.按编号升序排序" << endl;
    cout << "2.按编号降序排序" << endl;
    int sortType;
    cin >> sortType;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        int minOrMax = i;
        for (int j = i + 1; j < this->m_EmpNum; j++)
        {
            if (sortType == 1)
            {
                if (this->m_EmpAar[minOrMax]->m_Id > this->m_EmpAar[j]->m_Id)
                {
                    minOrMax = j;
                }
            }
            else
            {
                if (this->m_EmpAar[minOrMax]->m_Id < this->m_EmpAar[j]->m_Id)
                {
                    minOrMax = j;
                }
            }
        }
        if (i != minOrMax)
        {
            Worker *temp = this->m_EmpAar[i];
            this->m_EmpAar[i] = this->m_EmpAar[minOrMax];
            this->m_EmpAar[minOrMax] = temp;
        }
    }
    cout << "排序成功，排序之后结果为：" << endl;
    this->save();
    this->show();
}

void WorkManager::clean()
{
    cout << "确认清空数据?" << endl;
    cout << "1.确认" << endl;
    cout << "2.取消" << endl;
    int select;
    cin >> select;
    if (select == 1)
    {
        ofstream ofs;
        ofs.open(FILENAME, ios::trunc);
        ofs.close();
        if (this->m_EmpAar != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                delete this->m_EmpAar[i];
                this->m_EmpAar[i] = NULL;
            }
            delete[] this->m_EmpAar;
            this->m_EmpAar = NULL;
            this->m_EmpNum = 0;
            this->m_FilIsEmpty = true;
        }
        cout << "清空数据成功" << endl;
        system("read -p 'Press Enter to continue...' var");
        system("clear");
    }
}
