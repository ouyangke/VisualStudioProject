#include "OrderFile.h"
#include <fstream>
#include "GlobalFile.h"

void insertOrder(string data, map<string, string> &m)
{
    string key;
    string vaule;
    int pos = data.find(":");
    if (pos != -1)
    {
        key = data.substr(0, pos);
        vaule = data.substr(pos + 1, data.size());
        m.insert(make_pair(key, vaule));
    }
}

OrderFile::OrderFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);
    string date;
    string interval;
    string studentId;
    string studentName;
    string roomId;
    string status;
    this->m_Size = 0;
    while (ifs >> date && ifs >> interval && ifs >> studentId && ifs >> studentName && ifs >> roomId && ifs >> status)
    {
        map<string, string> m;
        insertOrder(date, m);
        insertOrder(interval, m);
        insertOrder(studentId, m);
        insertOrder(studentName, m);
        insertOrder(roomId, m);
        insertOrder(status, m);
        this->m_OrderData.insert(make_pair(this->m_Size, m));
        this->m_Size++;
    }
    ifs.close();
}

OrderFile::~OrderFile()
{
}

void OrderFile::updateOrder()
{
    if (this->m_Size == 0)
    {
        return;
    }
    ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
    for (int i = 0; i < this->m_Size; i++)
    {
        ofs << "date:" << this->m_OrderData[i]["date"] << " ";
        ofs << "interval:" << this->m_OrderData[i]["interval"] << " ";
        ofs << "studentId:" << this->m_OrderData[i]["studentId"] << " ";
        ofs << "studentName:" << this->m_OrderData[i]["studentName"] << " ";
        ofs << "roomId:" << this->m_OrderData[i]["roomId"] << " ";
        ofs << "status:" << this->m_OrderData[i]["status"] << endl;
    }
    ofs.close();
}
