#include<iostream>
using namespace std;
//宏常量不可修改
#define DAY 7

int main(int argc, char const *argv[])
{
    cout << "一周有："<< DAY << "天" << endl;

    const int week = 2;
    cout << "一个月有："<< week << "周"<<endl;
    return 0;
}


