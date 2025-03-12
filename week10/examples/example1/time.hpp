#pragma once
#include <iostream>

class MyTime
{
    int hours;
    int minutes;
  public:
    MyTime(): hours(0), minutes(0){}
    MyTime(int h, int m): hours(h), minutes(m){}

    MyTime operator+(const MyTime & t) const
    {
        //当一个成员函数被 const 修饰时，意味着这个函数是一个常量成员函数。
        //这表明在函数内部，不会修改调用该函数的对象的任何成员变量。
        //也就是说，在这个函数中，this 指针被隐式地转换为一个指向常量对象的指针，即 const MyTime*。
        
        //先创建临时变量sum
        MyTime sum;
        sum.minutes = this->minutes + t.minutes;
        sum.hours = this->hours + t.hours;

        sum.hours +=  sum.minutes / 60;
        sum.minutes %= 60;
        
        return sum;
    }
    MyTime & operator+=(const MyTime & t) 
    {
        this->minutes += t.minutes;
        this->hours += t.hours;

        this->hours +=  this->minutes / 60;
        this->minutes %= 60;
        
        return *this;
    }
    std::string getTime() const
    {
        return std::to_string(this->hours) + " hours and " 
                + std::to_string(this->minutes) + " minutes.";
    }
};
