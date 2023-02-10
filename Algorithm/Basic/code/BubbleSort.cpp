#include "Common.h"

template <typename T>
void bubbleSort(std::vector<T>& a)
{
    int n = a.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 1; j < n - i; j++)
        {
            if (a[j] < a[j - 1])
            {
                std::swap(a[j], a[j - 1]);
            }
        }
    }
};

int main()
{
    std::vector<int> a {9, 3, 4, 5, 6, 1, 2, 4};
    bubbleSort(a);
    traversal(a);
    return 0;
}