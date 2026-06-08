#include <iostream>
#include "plane.h"
#include <string>
#include <fstream>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

static vector<Airline> load_all()
{
    vector<Airline> res;
    ifstream in("plane.csv");
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        res.push_back(Airline::from_line(line));
    }
    return res;
}

static void save_all(const vector<Airline> &list)
{
    ofstream out("plane.csv", ios::trunc);
    for (const auto &a : list) out << a.to_line() << "\n";
}

int main()
{
#ifdef _WIN32
    // 设置控制台为 UTF-8 编码，避免中文在 Windows 控制台乱码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    int choice;
    while (true) {
        cout << "1.预定航班" << endl;
        cout << "2.查看预定信息" << endl;
        cout << "3.修改预定状态" << endl;
        cout << "4.退出系统" << endl;
        cout << "请输入您的选择：";
        if (!(cin >> choice)) { cin.clear(); string dummy; getline(cin, dummy); cout<<"无效输入，请输入数字！"<<endl; continue; }
        switch (choice) {
        case 1: {
            Airline a;
            a.getdetail();
            ofstream out("plane.csv", ios::app);
            out << a.to_line() << "\n";
            break;
        }
        case 2: {
            auto list = load_all();
            Airline tmp;
            tmp.display();
            for (const auto &a : list) a.print();
            break;
        }
        case 3: {
            cout << "请输入要修改的预定号：";
            string prn;
            cin >> prn;
            auto list = load_all();
            bool found = false;
            for (auto &a : list) {
                if (a.getPrn() == prn) {
                    a.setStatue();
                    found = true;
                    break;
                }
            }
            if (found) save_all(list);
            else cout << "未找到对应预定号" << endl;
            break;
        }
        case 4:
            return 0;
        default:
            cout << "无效的选择，请重新输入！" << endl;
        }
    }
    return 0;
}
