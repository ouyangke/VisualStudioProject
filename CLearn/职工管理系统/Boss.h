#pragma once
#include <iostream>
#include "Worker.h"
using namespace std;

class Boss : public Worker
{
private:
    /* data */
public:
    Boss(int id, string name, int dId);
    ~Boss();
    virtual void showInfo();
    virtual string getDeptName();
};