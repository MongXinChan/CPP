# operator type()
- Overloaded type conversion:convert the current type to another type
- The function is called when the type conversion is performed.
- The function must return the converted value.
- The function must have one parameter.
## Implicit conversion
```cpp
//implicit conversion
operator int()const{
    return this->hours*60+this->minutes;
}
//explicit conversion

explicit operator float()const{
    return this->hours*60+this->minutes;
}
//添加了explicit关键字，就不能进行隐式转换了，只能进行显式转换

explicit operator int()const{
    return this->hours*60+this->minutes;
}
```

Such as:
```cpp
Mytime t1(1,20);
int minutes=t1;//implicit conversion
float f=float(t1);//explicit conversion
```

## Converting constructor
- Convert another type to the current type.
```cpp
MyTime(int m):hours(0),minutes(m){
    this->hours+=this->minutes/60;
    this->minutes%=60;
}
```

```cpp
MyTime t2=100;//converting constructor
```

## Assignment operator overloading
- convert another type to the current type.
```cpp
MyTime& operator=(int m){
    this->hours=0;
    this->minutes=m;
    this->hours+=this->minutes/60;
    this->minutes%=60;
    return *this;  
}
```

```cpp
MyTime t3;
t3=80;//assignment operator overloading
```

## Be careful
- What is the difference in creating object between t2 and t3?
```cpp
MyTime t2=100;//converting constructor
//初始化

MyTime t3;
t3=80;//assignment operator overloading
//赋值
```
这个意思就是说，虽然说结果一样，但是其过程可能是不一样的。
详见[example-main.cpp](./main.cpp)