# function pointer

## 函数指针

### 概念
函数指针就是指向函数的指针变量。每一个函数都有一个入口地址，该入口地址就是函数指针所指向的地址。

### 定义：
```c++
    int func(int a);  
    int (*f)(int a);  
    f = &func;  
```
### 应用
函数指针的应用场景：回调（callback）。我们调用别人提供的 API函数(Application Programming Interface,应用程序编程接口)，称为Call；如果别人的库里面调用我们的函数，就叫Callback。
```c++
    // 以库函数qsort排序函数为例，它的原型如下：
    void qsort(void *base, // void*类型，代表原始数组
               size_t nmemb,
               size_t size,
               int (*compar)(const void *, const void *) // 第四个参数是函数指针
    );
    // 第四个参数告诉qsort，应该使用哪个函数来比较元素，即只要我们告诉qsort比较大小的规则，它就可以帮我们对任意数据类型的数组进行排序。在库函数qsort调用我们自定义的比较函数，这就是回调的应用。

    int num[100];
    int cmp_int(const void* _a , const void* _b){ // 参数格式固定
        int* a = (int*)_a;    // 强制类型转换
        int* b = (int*)_b;
        return *a - *b;　　
    }
    qsort(num, 100, sizeof(num[0]), cmp_int); // 回调
```
