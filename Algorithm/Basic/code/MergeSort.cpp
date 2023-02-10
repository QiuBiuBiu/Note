#include "Common.h"


template <typename T>
void _sort(std::vector<T>& nums, std::vector<T>& copy, int st, int end)
{
    if (st >= end) return;

    int mid = (end - st) / 2 + st;
    _sort(nums, copy, st, mid);
    _sort(nums, copy, mid + 1, end);

    int i = mid, j = end;
    int index = end;
    while (i >= st && j > mid)
    {
        if (nums[i] >= nums[j])
        {
            copy[index--] = nums[i--];
        }
        else
        {
            copy[index--] = nums[j--];
        }
    }
    while (i >= st) copy[index--] = nums[i--];
    while (j > mid) copy[index--] = nums[j--];

    for (int k = st; k <= end; k++)
    {
        nums[k] = copy[k];
    } 
};

template <typename T>
void mergeSort(std::vector<T>& nums)
{
    int n = nums.size();
    if (n == 0) return;

    std::vector<T> copy;
    for (const auto& a : nums)
    {
        copy.emplace_back(a);
    }
    
    _sort(nums, copy, 0, n - 1);
};

int main()
{
    std::vector<int> a {9, 3, 4, 5, 6, 1, 2, 4};
    mergeSort(a);
    traversal(a);
    return 0;
}