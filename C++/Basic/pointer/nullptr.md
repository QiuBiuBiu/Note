# nullptr

## nullptr调用成员函数可以吗？yes
因为在编译时对象就绑定了函数地址，和指针空不空没关系。pAn->breathe();编译的时候，函数的地址就和指针pAn绑定了；调用breath(*this), this就等于pAn。由于函数中没有需要解引用this的地方，所以函数运行不会出错，但是若用到this，因为this=nullptr，运行出错。
```c++
    class animal{
    public:
        void sleep(){ cout << "animal sleep" << endl; }
        void breathe(){ cout << "animal breathe haha" << endl; }
    };
    class fish :public animal{
    public:
        void breathe(){ cout << "fish bubble" << endl; }
    };
    int main(){
        animal *pAn=nullptr;
        pAn->breathe();   // 输出：animal breathe haha
        fish *pFish = nullptr;
        pFish->breathe(); // 输出：fish bubble
        return 0;
    }  
```
