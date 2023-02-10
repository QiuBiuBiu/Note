# Algorithm

## 排序

排序算法 | 平均时间复杂度 | 最差时间复杂度 | 空间复杂度 | 数据对象稳定性
---|---|---|---|---
[冒泡排序](code/BubbleSort.cpp) | O(n<sup>2</sup>)|O(n<sup>2</sup>)|O(1)|稳定
[选择排序](code/SelectSort.cpp) | O(n<sup>2</sup>)|O(n<sup>2</sup>)|O(1)|数组不稳定、链表稳定
[插入排序]() | O(n<sup>2</sup>)|O(n<sup>2</sup>)|O(1)|稳定
[快速排序](code/QuickSort.cpp) | O(n*log<sub>2</sub>n) |  O(n<sup>2</sup>) | O(log<sub>2</sub>n) | 不稳定
[堆排序]() | O(n*log<sub>2</sub>n)|O(n*log<sub>2</sub>n)|O(1)|不稳定
[归并排序](code/MergeSort.cpp) | O(n*log<sub>2</sub>n) | O(n*log<sub>2</sub>n)|O(n)|稳定
[希尔排序]() | O(n*log<sup>2</sup>n)|O(n<sup>2</sup>)|O(1)|不稳定
[计数排序]() | O(n+m)|O(n+m)|O(n+m)|稳定
[桶排序]() | O(n)|O(n)|O(m)|稳定
[基数排序]() | O(k*n)|O(n<sup>2</sup>)| |稳定

> * 均按从小到大排列
> * k：代表数值中的 “数位” 个数
> * n：代表数据规模
> * m：代表数据的最大值减最小值
> * 来自：[wikipedia . 排序算法](https://zh.wikipedia.org/wiki/%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95)