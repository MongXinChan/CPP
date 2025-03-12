# Increment or decrement operators

## Two operators:prefix increment and postfix increment
```cpp
//prefix increment
/***
 * the character '&' means that the return value is a reference
 * to the object itself
***/
MyTime& operator++(){
    this->minutes++;
    this->hours+=this->minutes/60;
    this->minutes%=60;
    return *this;
}
//postfix increment
MyTime operator++(int){
/***
 * int is a dummy parameter,just to distinguish 
 * prefix and postfix increment
 * Its speciality is that it can't return a reference
 * because the object is not modified
***/
    MyTime old=*this;//keep the old value
    operator++();//prefix increment
    return old; 
}

```

Here is the Operators which can be overloaded:

| 运算符     | 运算符名称             | 是否可作为非成员函数重载 | 示例           |
| ---------- | ---------------------- | ------------------------ | -------------- |
| `+`        | 加法运算符             | 是                       | `a + b`        |
| `-`        | 减法运算符             | 是                       | `a - b`        |
| `*`        | 乘法运算符             | 是                       | `a * b`        |
| `/`        | 除法运算符             | 是                       | `a / b`        |
| `%`        | 取模运算符             | 是                       | `a % b`        |
| `++`       | 自增运算符             | 否                       | `a++` 或 `++a` |
| `--`       | 自减运算符             | 否                       | `a--` 或 `--a` |
| `==`       | 相等比较运算符         | 是                       | `a == b`       |
| `!=`       | 不等比较运算符         | 是                       | `a != b`       |
| `<`        | 小于比较运算符         | 是                       | `a < b`        |
| `>`        | 大于比较运算符         | 是                       | `a > b`        |
| `<=`       | 小于等于比较运算符     | 是                       | `a <= b`       |
| `>=`       | 大于等于比较运算符     | 是                       | `a >= b`       |
| `&&`       | 逻辑与运算符           | 是                       | `a && b`       |
| `||`       | 逻辑或运算符           | 是                       | `a || b`       |
| `!`        | 逻辑非运算符           | 是                       | `!a`           |
| `&`        | 按位与运算符           | 是                       | `a & b`        |
| `|`        | 按位或运算符           | 是                       | `a | b`        |
| `^`        | 按位异或运算符         | 是                       | `a ^ b`        |
| `~`        | 按位取反运算符         | 是                       | `~a`           |
| `<<`       | 左移运算符             | 是                       | `a << b`       |
| `>>`       | 右移运算符             | 是                       | `a >> b`       |
| `+=`       | 加法赋值运算符         | 是                       | `a += b`       |
| `-=`       | 减法赋值运算符         | 是                       | `a -= b`       |
| `*=`       | 乘法赋值运算符         | 是                       | `a *= b`       |
| `/=`       | 除法赋值运算符         | 是                       | `a /= b`       |
| `%=`       | 取模赋值运算符         | 是                       | `a %= b`       |
| `&=`       | 按位与赋值运算符       | 是                       | `a &= b`       |
| `|=`       | 按位或赋值运算符       | 是                       | `a |= b`       |
| `^=`       | 按位异或赋值运算符     | 是                       | `a ^= b`       |
| `<<=`      | 左移赋值运算符         | 是                       | `a <<= b`      |
| `>>=`      | 右移赋值运算符         | 是                       | `a >>= b`      |
| `[]`       | 下标运算符             | 否                       | `a[b]`         |
| `()`       | 函数调用运算符         | 否                       | `a(b)`         |
| `->`       | 成员访问运算符         | 否                       | `a->b`         |
| `*`        | 解引用运算符           | 否                       | `*a`           |
| `,`        | 逗号运算符             | 是                       | `a, b`         |
| `new`      | 动态内存分配运算符     | 否                       | `new T`        |
| `delete`   | 动态内存释放运算符     | 否                       | `delete p`     |
| `new[]`    | 数组动态内存分配运算符 | 否                       | `new T[n]`     |
| `delete[]` | 数组动态内存释放运算符 | 否                       | `delete[] p`   |

There're Operators which can not be overloaded:

1. **作用域解析运算符**：`::`
   - 用于指定标识符的作用域，不能重载。
2. **成员选择运算符**：`.*` 和 `->*`
   - 用于通过指针访问类或结构体的成员，不能重载。
3. **sizeof 运算符**：`sizeof`
   - 用于获取类型或对象的大小，不能重载。
4. **typeid 运算符**：`typeid`
   - 用于获取类型信息，不能重载。
5. **类型转换运算符**：`const_cast`、`dynamic_cast`、`reinterpret_cast`、`static_cast`
   - 这些用于类型转换的关键字不能重载。
6. **三元条件运算符**：`? :`
   - 用于条件表达式，不能重载。
7. **成员访问运算符**：`.*` 和 `->`
   - 用于访问类或结构体的成员，不能重载。
