#include<iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    short num1 = 10;
    int  num2 = 20;
    long num3 = 30;
    long long num4 = 40;

    cout << "short:" << sizeof(num1) << endl;
    cout << "int:" << sizeof(num2) << endl;
    cout << "long:" << sizeof(num3) << endl;
    cout << "long long:" << sizeof(num4) << endl;
    

    return 0;
}
