# condition_variable

## std::condition_variable

## ucf封装
AsyncUtils.h里的spark::condition_wait

## 注意
1. 与条件变量搭配使用的「锁」，必须是 unique_lock，不能用 lock_guard
2. 等待前先加锁。等待时，如果条件不满足，wait 会原子性地解锁并把线程挂起。
3. 条件变量被通知后，挂起的线程就被唤醒，但是唤醒也有可能是假唤醒，或者是因为超时等异常情况，所以被唤醒的线程仍要检查条件是否满足，所以 wait 是放在条件循环里面。cv.wait(lock, [] { return ready; }); 相当于：while (!ready) { cv.wait(lock); }。