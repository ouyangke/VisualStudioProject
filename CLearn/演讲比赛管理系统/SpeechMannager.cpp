#include "SpeechManager.h"
#include <algorithm>
#include <map>
#include <deque>
#include <numeric>
#include <fstream>

SpeechManager::SpeechManager(/* args */)
{
    this->refreshData();
}

SpeechManager::~SpeechManager()
{
}

void SpeechManager::menu()
{
    cout << "*******************************" << endl;
    cout << "*******欢迎参加演讲比赛********" << endl;
    cout << "********1.开始演讲比赛*********" << endl;
    cout << "********2.查看往届记录*********" << endl;
    cout << "********3.清空比赛记录*********" << endl;
    cout << "********0.退出比赛程序*********" << endl;
    cout << "*******************************" << endl;
}

void SpeechManager::quit()
{
    cout << "欢迎下次使用" << endl;
    system("read -p 'Press Enter to continue...' var");
    exit(0);
}

void SpeechManager::start()
{
    cout << "开始演讲比赛" << endl;
    // 第一轮比赛
    // 1.抽签
    this->speechDraw();
    // 2.比赛
    this->speechContest();
    // 3.显示晋级结果
    this->showScore();
    // 第二轮比赛
    this->m_Index++;
    // 1.抽签
    this->speechDraw();
    // 2.比赛
    this->speechContest();
    // 3.显示最终结果
    this->showScore();
    // 保存分数到文件
    this->savaRecord();
    // 更新数据
    this->refreshData();
    cout << "本届比赛完毕" << endl;
    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void SpeechManager::history()
{
    if (this->fileIsEmpty)
    {
        cout << "文件为空或者文件不存在" << endl;
    }
    else
    {
        for (int i = 0; i < m_Record.size(); i++)
        {
            cout << "第" << i + 1 << "届"
                 << "冠军编号：" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << " "
                 << "亚军编号：" << this->m_Record[i][2] << "得分：" << this->m_Record[i][3] << " "
                 << "季军编号：" << this->m_Record[i][4] << "得分：" << this->m_Record[i][5] << endl;
        }
    }

    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void SpeechManager::clean()
{
    cout << "确认清空?" << endl;
    cout << "1.确认" << endl;
    cout << "2.取消" << endl;

    int select;
    cin >> select;
    if (select == 1)
    {
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();
        this->refreshData();
        cout << "清空成功" << endl;
    }

    system("read -p 'Press Enter to continue...' var");
    system("clear");
}

void SpeechManager::initData()
{
    this->v1.clear();
    this->v2.clear();
    this->victory.clear();
    this->m_Speaker.clear();
    this->m_Index = 1;
    this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); i++)
    {
        string name = "选手";
        name += nameSeed[i];

        Speaker sp;
        sp.m_Name = name;

        for (int j = 0; j < 2; j++)
        {
            sp.m_Score[j] = 0;
        }

        this->v1.push_back(10001 + i);
        this->m_Speaker.insert(make_pair(10001 + i, sp));
    }
}

void SpeechManager::speechDraw()
{
    cout << "第" << this->m_Index << "轮比赛选手正在抽签..." << endl;
    cout << "-------------------------------------------" << endl;
    cout << "抽签结果如下：" << endl;
    if (this->m_Index == 1)
    {
        random_shuffle(v1.begin(), v1.end());
        for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
        {
            cout << *it << "  ";
        }
        cout << endl;
    }
    else
    {
        random_shuffle(v2.begin(), v2.end());
        for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
        {
            cout << *it << "  ";
        }
        cout << endl;
    }
    cout << "-------------------------------------------" << endl;
    system("read -p 'Press Enter to continue...' var");
}

void SpeechManager::speechContest()
{
    cout << "第" << this->m_Index << "轮比赛正式开始..." << endl;
    // 不同分数对应的选手编号
    multimap<double, int, greater<double>> groupScore;
    // 记录人员数
    int num = 0;
    // 比赛人员容器
    vector<int> v_src;
    if (this->m_Index == 1)
    {
        v_src = v1;
    }
    else
    {
        v_src = v2;
    }

    for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
    {
        num++;
        deque<double> d;
        for (int i = 0; i < 10; i++)
        {
            // 600-1000
            double score = (rand() % 401 + 600) / 10.0f;
            d.push_back(score);
        }
        // 排序
        sort(d.begin(), d.end(), greater<double>());
        // 去掉最小
        d.pop_front();
        // 去掉最大
        d.pop_back();

        double sum = accumulate(d.begin(), d.end(), 0);
        double avg = sum / (double)d.size();
        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

        groupScore.insert(make_pair(avg, *it));

        // 每6个人为一组输出
        if (num % 6 == 0)
        {
            cout << "第" << num / 6 << "小组比赛名次：" << endl;

            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
            {
                cout << "编号：" << it->second << "姓名：" << this->m_Speaker[it->second].m_Name << "平均分：" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
            }

            int count = 0;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
            {
                if (this->m_Index == 1)
                {
                    v2.push_back((*it).second);
                }
                else
                {
                    victory.push_back((*it).second);
                }
            }

            groupScore.clear();
        }
    }
    cout << "----------------第" << this->m_Index << "轮比赛完毕----------------" << endl;
    system("read -p 'Press Enter to continue...' var");
}

void SpeechManager::showScore()
{
    cout << "第" << this->m_Index << "轮晋级选手如下：" << endl;
    vector<int> v;
    if (this->m_Index == 1)
    {
        v = v2;
    }
    else
    {
        v = victory;
    }

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "选手编号：" << *it << "姓名：" << this->m_Speaker[*it].m_Name << "得分：" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
    }
    cout << endl;
    system("read -p 'Press Enter to continue...' var");
    system("clear");
    this->menu();
}

void SpeechManager::savaRecord()
{
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);

    for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++)
    {
        ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";
    }
    ofs << endl;

    ofs.close();

    this->fileIsEmpty = false;
    cout << "记录已保存" << endl;
}

void SpeechManager::loadRecord()
{
    ifstream ifs;
    ifs.open("speech.csv", ios::in);
    if (!ifs.is_open())
    {
        this->fileIsEmpty = true;
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        this->fileIsEmpty = true;
        cout << "文件为空" << endl;
        ifs.close();
        return;
    }

    this->fileIsEmpty = false;

    ifs.putback(ch);

    string data;
    int index = 0;
    while (ifs >> data)
    {
        vector<string> v;
        int pos = -1;
        int start = 0;

        while (true)
        {
            pos = data.find(",", start);
            if (pos == -1)
            {
                break;
            }
            string temp = data.substr(start, pos - start);
            v.push_back(temp);
            start = pos + 1;
        }

        this->m_Record.insert(make_pair(index, v));
        index++;
    }
    ifs.close();
}

void SpeechManager::refreshData()
{
    this->initData();
    this->createSpeaker();
    this->loadRecord();
}
