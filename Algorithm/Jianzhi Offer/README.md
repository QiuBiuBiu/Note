# 剑指Offer

## 40.最小的k个数
[LeetCode 题目连接](https://leetcode.cn/problems/zui-xiao-de-kge-shu-lcof/)
Topk问题的几种解法：
1. 直接排序，T=O(nlogn)
2. 维护一个大小为k的最大堆，当新元素加入时：
    - 若堆内元素的size小于k时，直接插入新元素
    - 否则，若新元素比堆顶元素还小时，则移除堆顶元素而插入新元素
    - 否则，忽略新元素
    - 用C++中的priority_queue来解决这个问题：
        - priority_queue底层是基于heap的一系列算法构成的，我们可以用O(1)的时间获得k个元素的最大值，但需要O(logk)的时间完成删除和插入
        - 故总的时间复杂度为T=O(nlogk)
        - [code](codes/40_priority_queue.cpp)
    - 用C++中的multiset来解决这个问题：
        - multiset(和set)底层都是由红黑树来实现的，在红黑树中的查找、删除和插入都只需要O(logk)的时间
        - 故总的时间复杂度为T=O(nlogk)
        - [code](codes/40_multiset.cpp)
3. 基于快排算法的Partition函数
    - Partition函数每次从数组中选择一个数，然后将数组分成两部分，比选择的数小的数字移到数组的左边，大的则移到它的右边
    - 当基于数组的第k个数来调整时，就获得了最小的k个数字(这k个数字不一定是排序的)
    - 时间负责度为T=O(n)
    - [code](40_partition.cpp)
