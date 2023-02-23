# vector

## 定义
```c++
    //_Alloc 表示内存分配器，此参数几乎不需要我们关心
    template <class _Ty, class _Alloc = allocator<_Ty>>
    class vector{
        ...
    protected:
        pointer _Myfirst;
        pointer _Mylast;
        pointer _Myend;
    };
```
vector使用 3 个迭代器（可以理解成指针）来表示的：其中，_Myfirst 指向的是 vector 容器对象的起始字节位置；_Mylast 指向当前最后一个元素的末尾字节；_myend 指向整个 vector 容器所占用内存空间的末尾字节。

## vector扩容
当 vector 的大小和容量相等（size==capacity）也就是满载时，如果再向其添加元素，那么 vector 就需要扩容。vector 容器扩容的过程需要经历以下 3 步：
1. 完全弃用现有的内存空间，重新申请更大的内存空间；
2. 将旧内存空间中的数据，按原有顺序移动到新的内存空间中；
3. 最后将旧的内存空间释放。

## vector的元素类型可以是引用吗？
vector的底层实现要求连续的对象排列，引用并不是对象，没有实际地址，因此vector的元素类型不能是引用。

## vector中的reserve和resize的区别？
1. resize(n) 调整容器的长度大小，使其能容纳n个元素。
2. resize(n，t) 多一个参数t，将所有新添加的元素初始化为t。
3. reserve()的用法只有一种reserve(n)，预分配n个元素的存储空间。
4. 注意和reverse(a.begin(), a.end())函数的区别

## 什么情况下vector的迭代器会失效？
1. 在vector容器中间根据指定迭代器删除元素，也就是调用erase函数，此时因为当前位置会被后面的元素覆盖，所以该指定迭代器会失效，不过此时可以通过erase的返回值重新得到当前位置的正确迭代器；
2. 在vector需重新申请内存的时候，比如扩容或者释放未使用的内存等等这些过程中都会发生迭代器失效的问题，因为内存有了变动，此时就需要重新获得迭代器；

## vector怎么迅速的释放内存？
1. reserve(0)？不行，这个函数只有在传入大小比原有内存大时才会有动作，否则不进行任何动作。
2. clear()?不行，这个函数只会对当前已保存在容器中的所有元素进行析构，但对容器本身所在的内存空间是不会进行释放的。
3. 正确的做法是clear() + shrink_to_fit()（在c++11以后增加了这个函数，它的作用是释放掉未使用的内存）