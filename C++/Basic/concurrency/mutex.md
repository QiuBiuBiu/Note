# mutex
互斥量

## std::mutex
std::mutex 是C++11 中最基本的互斥量，std::mutex 对象提供了独占所有权的特性

## std::recursive_mutex
std::recursive_mutex 则可以递归地对互斥量对象上锁，即std::recursive_mutex 允许同一个线程对互斥量多次上锁（即递归上锁），来获得对互斥量对象的多层所有权。