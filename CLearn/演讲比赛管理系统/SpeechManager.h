#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Speaker.h"
using namespace std;

// 演讲管理类
class SpeechManager
{
private:
    /* data */
public:
    SpeechManager(/* args */);
    ~SpeechManager();

    void menu();

    void quit();

    void start();

    void history();

    void clean();

    void initData();

    void createSpeaker();

    void speechDraw();

    void speechContest();

    void showScore();

    void savaRecord();

    void loadRecord();

    void refreshData();
    
    // 第一轮 编号 12人
    vector<int> v1;
    // 第二轮 编号 6人
    vector<int> v2;
    // 获胜者   3人
    vector<int> victory;
    // 编号对应选手信息
    map<int, Speaker> m_Speaker;
    // 当前轮数
    int m_Index;
    //文件为空标志位
    bool fileIsEmpty;
    //往届记录
    map<int,vector<string>> m_Record;
};
