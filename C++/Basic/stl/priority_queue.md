# 优先队列

## 大根堆 小根堆
C++用优先队列来表示堆，定义时传入比较函数`std::less<int>`或者`std::greater<int>`来说明是大根堆还是小根堆。
```c++
    priority_queue<int, vector<int>, less<int>> maxHeap; // 等同于 priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
```
但这里传入的比较函数跟最终得到的堆似乎是相反的，因为通常我们是这么使用的：
```c++
    vector<int> nums{5, 4, 3, 2, 1};
    sort(nums.begin(), nums.end(), less<int>()); // 等同于sort(nums.begin(), nums.end());
    // 结果为: 1, 2, 3, 4, 5
    // less<int>()：从小到达排序，没问题。
```
其实是priority_queue设计的问题，传入`std::less<int>`会按从小到大排序，所以小的优先级高，弹出时最后弹出，所以是大根堆。