# nullptr

## nullptr和NULL的区别
NULL在C语言中是(void * )0，在C++中却是整型0。这是因为在C++中void * 类型是不允许隐式转换成其他指针类型的，所以之前C++中用整型0来代表空指针。但是，在重载整型和指针的情况下，会出现匹配错误的情况。所以，C++11加入了nullptr，可以保证在任何情况下都代表空指针。

## nullptr调用成员函数可以吗？yes
因为在编译时对象就绑定了函数地址，和指针空不空没关系。pAn->breathe()编译的时候，函数的地址就和指针pAn绑定了；调用breath(*this), this就等于pAn。由于函数中没有需要解引用this的地方，所以函数运行不会出错，但是若用到this，因为this=nullptr，运行出错。
```c++
    class animal {
    public:
        void sleep() { cout << "animal sleep" << endl; }
        void breathe() { cout << "animal breathe haha" << endl; }
    };

    class fish : public animal {
    public:
        void breathe() { cout << "fish bubble" << endl; }
    };

    int main() {
        animal *pAn = nullptr;
        pAn->breathe();   // 输出：animal breathe haha
        fish *pFish = nullptr;
        pFish->breathe(); // 输出：fish bubble
        return 0;
    }  
```
