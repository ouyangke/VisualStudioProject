#pragma once
#include <iostream>
#include "Worker.h"
using namespace std;

class Employee : public Worker
{
private:
    /* data */
public:
    Employee(int id, string name, int dId);
    ~Employee();
    virtual void showInfo();
    virtual string getDeptName();
};
