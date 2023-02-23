# push_back() 和 emplace_back() 区别
## 底层实现的机制不同：
1. push_back() 向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）；
2. emplace_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。

```c++
    #include <vector> 
    #include <iostream> 
    using namespace std;

    class testDemo
    {
    public:
        testDemo (int num): num(num) {
            std::cout << "调用构造函数" << endl;
        }
        testDemo (const testDemo& other) : num(other.num) {
            std::cout << "调用拷贝构造函数" << endl;
        }
        testDemo (testDemo&& other) : num(other.num) {
            std::cout << "调用移动构造函数" << endl;
        }
    private:
        int num;
    };
    
    int main()
    {
        cout << "emplace_back:" << endl;
        std::vector<testDemo> demo1;
        demo1.emplace_back(2);  

        cout << "push_back:" << endl;
        std::vector<testDemo> demo2;
        demo2.push_back(2);

        return 0;
    }
    /*
    1. 运行结果为：
    emplace_back:
    调用构造函数
    push_back:
    调用构造函数
    调用移动构造函数

    2. 将 testDemo 类中的移动构造函数注释掉，再运行程序会发现，运行结果变为：
    emplace_back:
    调用构造函数
    push_back:
    调用构造函数
    调用拷贝构造函数
    */
```
## 总结
1. 显然完成同样的操作，push_back() 的底层实现过程比 emplace_back() 更繁琐，换句话说，emplace_back() 的执行效率比 push_back() 高。因此，在实际使用时，建议大家优先选用 emplace_back()。
2. 由此可以看出，push_back() 在底层实现时，会优先选择调用移动构造函数，如果没有才会调用拷贝构造函数。




