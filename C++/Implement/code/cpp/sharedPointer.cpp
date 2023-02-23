#include <iostream>
#include <mutex>

template <typename T>
class sharedPointer
{
private:
    T *ptr = nullptr;
    int *refCount = nullptr;
    std::mutex *mMutex = nullptr;

public:
    sharedPointer(T* Ptr = nullptr) : ptr(Ptr), refCount(new int(1)), mMutex(new std::mutex()) 
    {
        std::cout << "~default constructor~" << std::endl;
    };

    sharedPointer(const sharedPointer<T>& cPtr) : ptr(cPtr.ptr), refCount(cPtr.refCount), mMutex(cPtr.mMutex)
    {
        std::cout << "~copy constructor~" << std::endl;
        increseRefCount();
    };

    sharedPointer<T>& operator= (const sharedPointer<T>& ptr)
    {
        std::cout << "~copy = constructor~" << std::endl;
        if (this->ptr != ptr.ptr)
        {
            decreseRefCount();
            this->ptr = ptr.ptr;
            this->refCount = ptr.refCount;
            this->mMutex = ptr.mMutex;
            increseRefCount();
        }
        return *this;
    };

    void increseRefCount()
    {
        mMutex->lock();
        ++(*refCount);
        std::cout << "increseRefCount!!! now the count is " << *refCount << std::endl; 
        mMutex->unlock();
    };

    void decreseRefCount()
    {
        bool deleteFlag = false;

        mMutex->lock();
        --(*refCount);
        std::cout << "decreseRefCount!!! now the count is " << *refCount << std::endl; 
        if (*refCount == 0)
        {
            std::cout << " ref count is 0 " << std::endl;
            delete ptr;
            delete refCount;
            deleteFlag = true;
        }
        mMutex->unlock();

        if (deleteFlag)
            delete mMutex;

    };

    int getRefCount()
    {
        return *refCount;
    }

    ~sharedPointer()
    {
        std::cout << "~destructor~" << std::endl;
        decreseRefCount();
    };
};

int main()
{
    int a = 0;
    sharedPointer<int> ptr;         // 构造
    sharedPointer<int> ptr2(ptr);   // 复制构造，或者 sharedPointer<int> ptr2 = ptr;
    sharedPointer<int> ptr3;
    ptr3 = ptr;                     // 复制赋值构造
    return 0;
}
