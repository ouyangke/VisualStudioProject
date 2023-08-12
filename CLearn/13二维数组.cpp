#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int arr[3][3] = {
        {11, 12, 13},
        {21, 22, 23},
        {31, 32, 33}};
        
    cout << arr[0][0] << endl;
    cout << arr[0][1] << endl;
    cout << arr[0][2] << endl;
    cout << arr[1][0] << endl;
    cout << arr[1][1] << endl;
    cout << arr[1][2] << endl;
    cout << arr[2][0] << endl;
    cout << arr[2][1] << endl;
    cout << arr[2][2] << endl;
    return 0;
}
