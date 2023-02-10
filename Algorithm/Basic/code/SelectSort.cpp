#include "Common.h"

template <typename T>
void selectSort(std::vector<T>& a)
{
    int n = a.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[minIndex])
            {
                minIndex = j;
            }
        }
        std::swap(a[i], a[minIndex]);
    }
};

int main()
{
    std::vector<int> a {9, 3, 4, 5, 6, 1, 2, 4};
    selectSort(a);
    traversal(a);
    return 0;
}