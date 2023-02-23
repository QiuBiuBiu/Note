# decltype
decltype 是 C++11 新增的一个关键字，它和 auto 的功能一样，都用来在编译时期进行自动类型推导。

## decltype 和 auto的区别
1. 推导类型的方式不一样
```c++
    int value = 0;
    auto varname = value;

    int exp = value + 100; // int exp = 100;
    decltype(exp) varname = value;
```
`auto` 根据 = 右边的初始值 value 推导出变量的类型，而 `decltype` 根据 exp 表达式推导出变量的类型，跟 = 右边的 value 没有关系。

2. auto 要求变量必须初始化，而 decltype 不要求。(这很容易理解，auto 是根据变量的初始值来推导出变量类型的，如果不初始化，变量的类型也就无法推导了。decltype 可以写成下面的形式：)
```c++
    decltype(exp) varname;
```

3. 编译器推断出来的auto类型有时候和初始值的类型并不完全一样，编译器会适当地改变结果类型使其更符合初始化规则。例如，auto一般会忽略顶层const，而把底层const保留下来。与之相反，decltype会保留变量的顶层const。

## decltype 推导规则
当使用 decltype(exp) 获取类型时，编译器将根据以下三条规则得出结果：
1. 如果 exp 是一个不被括号( )包围的表达式，或者是一个类成员访问表达式，或者是一个单独的变量，那么 decltype(exp) 的类型就和 exp 一致，这是最普遍最常见的情况。
2. 如果 exp 是函数调用，那么 decltype(exp) 的类型就和函数返回值的类型一致。
3. 如果 exp 是一个左值，或者被括号( )包围，那么 decltype(exp) 的类型就是 exp 的引用；假设 exp 的类型为 T，那么 decltype(exp) 的类型就是 T&。