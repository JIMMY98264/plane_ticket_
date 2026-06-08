#include "plane.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

Airline::Airline()
    : prn(), name(), date_departure(), from(), to(), statue('n') {}

void Airline::getdetail()
{
    cout << "请输入预定信息：" << endl;
    cout << "姓名：";
    getline(cin >> ws, name);
    cout << "请输入预定日期：";
    getline(cin >> ws, date_departure);
    cout << "出发地：";
    getline(cin >> ws, from);
    cout << "目的地：";
    getline(cin >> ws, to);
    cout << "预定的航班号：";
    getline(cin >> ws, prn);
    cout << "是否确认预定？（y/n）";
    char c; cin >> c; statue = c; string dummy; getline(cin, dummy);
}

void Airline::display() const
{
    cout << "姓名\t出发日期\t出发地\t目的地\t预定的航班号\t预定状态" << endl;
}

void Airline::print() const
{
    cout << name << "\t" << date_departure << "\t" << from << "\t" << to << "\t" << prn << "\t\t" << statue << endl;
}

const string &Airline::getPrn() const
{
    return prn;
}

void Airline::setStatue()
{
    char c;
    cout << "Canal booking statue(y/n):";
    cin >> c;
    if (c == 'y' || c == 'Y')
        statue = 'f';
    string dummy; getline(cin, dummy);
}

char Airline::getStatue() const
{
    return statue;
}

static string sanitize_field(const string &s)
{
    string r = s;
    for (char &ch : r)
        if (ch == '|') ch = '/';
    return r;
}

string Airline::to_line() const
{
    ostringstream out;
    out << sanitize_field(name) << "|" << sanitize_field(date_departure) << "|" << sanitize_field(from)
        << "|" << sanitize_field(to) << "|" << sanitize_field(prn) << "|" << statue;
    return out.str();
}

Airline Airline::from_line(const string &line)
{
    Airline a;
    vector<string> parts;
    string cur;
    for (char ch : line) {
        if (ch == '|') { parts.push_back(cur); cur.clear(); }
        else cur.push_back(ch);
    }
    parts.push_back(cur);
    if (parts.size() >= 6) {
        a.name = parts[0];
        a.date_departure = parts[1];
        a.from = parts[2];
        a.to = parts[3];
        a.prn = parts[4];
        a.statue = parts[5].empty() ? 'n' : parts[5][0];
    }
    return a;
}