#pragma once
#include <iostream>
#include "Worker.h"
using namespace std;

class Manager : public Worker
{
private:
    /* data */
public:
    Manager(int id, string name, int dId);
    ~Manager();
    virtual void showInfo();
    virtual string getDeptName();
};
