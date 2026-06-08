#ifndef PLANE_H
#define PLANE_H

#include <string>

class Airline
{
public:
    Airline();
    void getdetail(); // 接受用户预定信息
    static Airline from_line(const std::string &line); // 从文本行解析（使用'|'分隔）
    std::string to_line() const; // 转为文本行
    void display() const; // 打印标题栏
    void print() const; // 打印预定信息
    const std::string &getPrn() const;
    void setStatue();
    char getStatue() const;

private:
    std::string prn; // 预定号
    std::string name; // 姓名
    std::string date_departure; // 出发日期
    std::string from; // 出发地
    std::string to; // 目的地
    char statue; // 预定状态
};

#endif
