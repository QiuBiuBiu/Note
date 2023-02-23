# enum
枚举类型，所谓”枚举”是指将变量的值一一列举出来，变量的值只能在列举出来的值的范围内。在C++中，枚举类型分为不限定作用域（enum）和限定作用域（enum class）。


## enum与enum class的区别？
1. 枚举作用域是指枚举类型成员名字的作用域，起自其声明之处，终止枚举定义结束之处。enum与class enum区别在于是否**限定其作用域**。
2. C语言规定，枚举类型（enum）的成员的可见范围被提升至该枚举类型所在的作用域内。这被认为有可能**污染了外部的作用域**，为此，C++11引入了枚举类(enum class)解决此问题。
```c++
    enum Sex
    {
        Girl,  
        Boy 
    };

    enum Student
    {
        Girl // error，编译错误的原因在于Sex与Student都处在同一作用域下，成员变量重定义。
    };
```

**这便体现C++11引入枚举类(enum class)的重要性，enum class能够有效对枚举作用域进行限定，避免了枚举成员的重定义**：
```c++
    enum class Sex
    {
        Girl,  
        Boy 
    };

    enum class Student
    {
        Girl,  
        Boy 
    };

    int main()
    {
        Sex a = Sex::Gril; 
        Student b = Student::Gril;
        // 两者处于不同作用域下，不会重定义
    }
```

3. 定义，声明和使用上的区别
    - enum
    ```c++
        enum Sex    // 定义
        {
            Girl,  
            Boy 
        };
        Sex a = Girl; // 声明
    ```

    - enum class
    ```c++
        enum class Sex
        {
            Girl,  
            Boy 
        };
        Sex a = Sex::Girl; // 声明上的区别

        int main()
        {
            Sex a = Sex::Gril;
            int d1 = a;                 // 错误，无法从“Girl”隐式转换为“int”。
            int d2 = static_cast(a);    // 正确，显示将enum class转换为整数
            return 0;
        }
    ```
