# 怎么避免死锁？

## 死锁的概念
当两个线程为了保护两个不同的共享资源而使用了两个互斥锁，**那么这两个互斥锁应用不当的时候，可能会造成两个线程都在等待对方释放锁**，在没有外力的作用下，这些线程会一直相互等待，就没办法继续运行，这种情况就是发生了死锁。死锁只有同时满足以下四个条件才会发生：
1. 互斥条件；
2. 持有并等待条件；
3. 不可剥夺条件；
4. 环路等待条件；
总结：**死锁问题的产生是由两个或者以上线程并行执行的时候，争夺资源而互相等待造成的。死锁只有同时满足互斥、持有并等待、不可剥夺、环路等待这四个条件的时候才会发生**。

### 互斥条件
互斥条件是指多个线程不能同时使用同一个资源。

### 持有并等待条件
持有并等待条件是指，当线程 A 已经持有了资源 1，又想申请资源 2，而资源 2 已经被线程 C 持有了，所以线程 A 就会处于等待状态，**但是线程 A 在等待资源 2 的同时并不会释放自己已经持有的资源 1**。

### 不可剥夺条件
不可剥夺条件是指，当线程已经持有了资源 ，在自己使用完之前不能被其他线程获取

### 环路等待条件
环路等待条件指的是，在死锁发生的时候，两个线程获取资源的顺序构成了环形链。


## 利用工具排查死锁问题
在 Linux 下，我们可以使用 pstack + gdb 工具来定位死锁问题：
- pstack 命令可以显示每个线程的栈跟踪信息（函数调用过程），它的使用方式也很简单，只需要 ```pstack <pid>``` 就可以了。
- 使用gdb工具进一步确认，即```gdb -p <pid>``` ：
    - 通过 ```info thread``` 打印了所有的线程信息
    - 通过 `thread 2`，将切换到第 2 个线程
    - 通过 `bt`，打印线程的调用栈信息
    - 通过 `frame 3`，打印调用栈中的第三个帧的信息
    - 通过 `p mutex_A`，打印互斥锁 A 对象信息

## 避免死锁问题的发生
1. 产生死锁的四个必要条件是：互斥条件、持有并等待条件、不可剥夺条件、环路等待条件。

2. 那么避免死锁问题就只需要破环其中一个条件就可以，最常见的并且可行的就是**使用资源有序分配**法，来破环环路等待条件。
