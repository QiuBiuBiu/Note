# lock

## std::lock_guard
```c++
    std::mutex mutex;
    void print(int cnt)
    {
        std::lock_guard<std::mutex> lock(mutex);
        cout << std::this_thread::get_id() << " " << cnt << endl;
    }
```
1. lock来管理mutex锁，当输出完毕后，lock的生命周期结束，则自动把mutex给unlock()解锁，用起来很方便。
2. 不过他是在创建lock对象（构造函数）的时候，就已经把mutex给锁住了（RAII），且我们不能手动解锁，只能等生命周期消失（析构函数）才会自动解锁。这样的会就会出现一些问题：如果在一个函数方法中，需要保持线程安全的地方较多，总不能创建多个lock_guard对象吧，这个时候我们可以使用unique_lock对象来进行锁的管理。

## std::unique_lock
1. unique_lock对于锁的管理比较灵活。它不像lock_guard一样，必须要求他管理的锁在他初始化的时候必须加锁，而是可以自己灵活的，想加锁就加锁（调用lock()方法），解锁的时候调用unlock来解锁。
2. unique_lock灵活但是资源消耗也大一些，速度也比lock_grard慢

## std::scoped_lock (C++ 17)
scoped_lock可以对多个互斥量进行上锁
