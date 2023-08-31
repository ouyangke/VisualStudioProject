#include <iostream>
#include "WorkManager.h"
using namespace std;

void pause()
{
    system("read -p 'Press Enter to continue...' var");
}
void clean()
{
    system("clear");
}

int main(int argc, char const *argv[])
{
    WorkManager wm;
    int choice;
    while (true)
    {
        wm.menu();
        cout << "请输入你的选择：" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            // 添加
            wm.add();
            break;
        case 2:
            // 显示
            wm.show();
            break;
        case 3:
            // 删除
            wm.remove();
            break;
        case 4:
            // 查找
            wm.find();
            break;
        case 5:
            // 修改
            wm.change();
            break;
        case 6:
            // 排序
            wm.sort();
            break;
        case 7:
            // 清空
            wm.clean();
            break;
        case 0:
            // 退出
            wm.quit();
            break;
        default:
            clean();
            break;
        }
    }

    return 0;
}
