#include <iostream>
#include <vector>
using namespace std;


void fun()
{
    static int a = 0;
    a++;
    cout << a << endl;
}
int main()
{   
    // vector<int> f(10, 0);
    // int a[10];
    // int *ptr = a;
    // int b;
    // cout << sizeof(b) << endl;
    // cout << sizeof(ptr) << endl;
    // cout << sizeof(a) << endl;
    // cout << sizeof(f[0]) << endl;
    // fun();
    // fun();
    // fun();
    // fun();

    // vector<string> res;
    // string str = "abc";
    // res.push_back(std::move(str));
    // cout << res[0] << " " << str << endl;

    int b = 1;
    int *a = &b;
    cout << sizeof(b) << endl;
    cout << sizeof(a) << endl;

    return 0;
}