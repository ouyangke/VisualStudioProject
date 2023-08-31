#include <iostream>
#include "SpeechManager.h"

int main(int argc, char const *argv[])
{
    srand((unsigned int)time(NULL));
    SpeechManager sm;

    while (true)
    {
        sm.menu();
        cout << "请输入你的选择：" << endl;
        int select;
        cin >> select;

        switch (select)
        {
        case 1:
            sm.start();
            break;
        case 2:
            sm.history();
            break;
        case 3:
            sm.clean();
            break;
        case 0:
            sm.quit();
            break;
        default:
            system("clear");
            break;
        }
    }
    return 0;
}
