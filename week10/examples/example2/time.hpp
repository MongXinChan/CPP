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

    MyTime operator+(int m) const
    {
        //此时，用了int m，也就是不引用Mytime，这里我觉得可以用int &m
        //此时出错了，以为并不符合int 类型【也就是说，不能用int &m】
        //因为，int 类型是一个临时变量，在函数结束后，就会被销毁
        //int &m指的是引用了一个已经存在的变量，而不是引用一个临时变量

        /* 
        如果参数是 const int &m，就可以接受临时值。
        因为常量引用可以绑定到临时对象，它会延长临时对象的生命周期，
        使其在引用的生命周期内保持有效。不过在当前的 operator+ 函数中，
        不需要修改传入的 int 值，所以使用值传递 int m 就足够了，
        既简单又能避免不必要的复杂性。
        */
        MyTime sum;
        sum.minutes = this->minutes + m;
        sum.hours = this->hours;
        sum.hours +=  sum.minutes / 60;
        sum.minutes %= 60;
        return sum;
    }
    MyTime & operator+=(int m) 
    {
        this->minutes += m;
        this->hours +=  this->minutes / 60;
        this->minutes %= 60;
        return *this;
    }

    MyTime operator+(const std::string str) const
    {
        MyTime sum = *this;
        if(str=="one hour")
            sum.hours = this->hours + 1;
        else
            std::cerr<< "Only \"one hour\" is supported." << std::endl;
        return sum;
    }
    
    std::string getTime() const
    {
        return std::to_string(this->hours) + " hours and " 
                + std::to_string(this->minutes) + " minutes.";
    }
};
