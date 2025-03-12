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
        MyTime sum;
        sum.minutes = this->minutes + m;
        sum.hours = this->hours;
        sum.hours +=  sum.minutes / 60;
        sum.minutes %= 60;
        return sum;
    }
    //friend MyTime operator+(int m,const MyTime &t);

    //用友元函数来实现，因为友元函数可以访问私有成员变量
    //原本只能实现MyTime + int，现在可以实现int + MyTime。
    //但是，友元函数不能直接访问私有成员变量，所以需要在类中定义一个公有函数来实现。
    friend MyTime operator+(int m, const MyTime & t)
    {
        return t + m;
    }

    std::string getTime() const
    {
        return std::to_string(this->hours) + " hours and " 
                + std::to_string(this->minutes) + " minutes.";
    }

    friend std::ostream & operator<<(std::ostream & os, const MyTime & t)
    {
        std::string str = std::to_string(t.hours) + " hours and " 
                        + std::to_string(t.minutes) + " minutes.";
        os << str;
        return os;
    }
    friend std::istream & operator>>(std::istream & is, MyTime & t)
    {
        is >> t.hours >> t.minutes;
        t.hours +=  t.minutes / 60;
        t.minutes %= 60;
        return is;
    }
};

/*

注意到就算定义在类外，也不需要写friend，以及类名，由于友元函数是全局函数，所以不需要写类名。
但是，友元函数不能直接访问私有成员变量，所以需要在类中定义一个公有函数来实现。

MyTime operator+(int m,MyTime &t){

    return t+m;

}


*/

/*

    Other function definition:
    class MyTime{
        public:
            static void sum(int a,int b);
    };

    MyTime::sum(int a,int b){
        std::cout<<a+b<<std::endl;
    }

*/