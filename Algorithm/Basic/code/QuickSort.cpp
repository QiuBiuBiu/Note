#include "Common.h"

template <typename T>
int _partition(std::vector<T>& nums, int st, int end)
{
    int index = st;
    std::swap(nums[st], nums[end]);
    
    int i = st - 1;
    for (int j = st; j < end; j++)
    {
        if (nums[j] < nums[end])
        {
            if (j != i)
            {
                ++i;
                std::swap(nums[i], nums[j]);
            }
        }
    }
    ++i;
    std::swap(nums[i], nums[end]);
    return i;
};

template <typename T>
void _sort(std::vector<T>& nums, int st, int end)
{
    if (st >= end) 
        return;

    int k = _partition(nums, st, end);
    _sort(nums, st, k);
    _sort(nums, k + 1, end);
};

template <typename T>
void quickSort(std::vector<T>& nums)
{
    int n = nums.size();
    if (n == 0) return;

    _sort(nums, 0, n - 1);
};

int main()
{
    std::vector<int> a {9, 3, 4, 5, 6, 1, 2, 4};
    quickSort(a);
    traversal(a);
    return 0;
}