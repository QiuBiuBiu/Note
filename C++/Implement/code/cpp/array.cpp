#include <iostream>
using namespace std;

class Array
{
private:
    int * arr = NULL;
    int size = 0;
    int capacity = 0;
public:
    Array()
    {
        cout << "default constructor" << endl;
        capacity = 3;
        size = 0;
        arr = new int[capacity];
    }
    Array(int n)
    {
        cout << "constructor with size" << endl;
        size = n;
        capacity = size * 2;
        arr = new int[capacity];
    }
    Array(int n, int val)
    {
        cout << "constructor with size and init val" << endl;
        size = n;
        capacity = size * 2;
        arr = new int[capacity];
        for (int i = 0; i < size; ++i)
        {
            arr[i] = val;
        }
    }
    Array(const Array & other)
    {
        cout << "copy constructor" << endl;
        if (this != &other)
        {
            if (arr) delete [] arr;

            size = other.size;
            capacity = other.capacity;
            arr = new int[capacity];
            for (int i = 0; i < size; ++i)
            {
                arr[i] = other.arr[i];
            }            
        }
    }
    Array& operator= (const Array & other)
    {
        cout << "operator= " << endl;
        if (this != &other)
        {
            if (arr) delete [] arr;

            size = other.size;
            capacity = other.capacity;
            arr = new int[capacity];
            for (int i = 0; i < size; ++i)
            {
                arr[i] = other.arr[i];
            }            
        }
        return *this;
    }
    Array(Array && other)
    {
        cout << "move constructor" << endl;

        if (arr) delete [] arr;

        size = other.size;
        capacity = other.capacity;
        arr = other.arr;

        other.size = other.capacity = 0;
        other.arr = NULL;
    }
    ~Array()
    {
        if (arr) 
        {
            delete [] arr;
            arr = NULL;
            capacity = size = 0;
        }
    }
    void push_back(int val)
    {
        cout << "push_back val: " << val << endl;
        if (size == capacity)
        {
            int * tmp = arr;
            capacity = capacity * 2;

            arr = new int[capacity];
            for (int i = 0; i < size; ++i)
            {
                arr[i] = tmp[i];
            }

            delete [] tmp;
        }
        arr[size++] = val;
    }
    void print()
    {
        getSize();
        getCapacity();
        cout << "print: ";
        for (int i = 0; i < size; ++i)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    void getSize()
    {
        cout << "Array's size is: " << size << endl;
    }
    void getCapacity()
    {
        cout << "Array's capacity is: " << capacity << endl;
    }
};

int main()
{
    // Array arr1(2, 1);
    // arr1.getSize();
    // arr1.getCapacity();
    // arr1.push_back(3); arr1.push_back(4); arr1.push_back(5);
    // arr1.getSize();
    // arr1.getCapacity();
    // arr1.print();

    // Array arr2(5, 1);
    // Array arr3(std::move(arr2));
    // arr3.print();
    // arr2.print();

    Array arr4(5, 1);
    Array arr5 = arr4;
    arr5.print();
    arr4.print();
    return 0;
}
