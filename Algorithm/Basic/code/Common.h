#include <iostream>
#include <vector>

template <typename T>
 void traversal(std::vector<T>& nums)
 {
    for (const auto& a : nums)
    {
        std::cout << a << " ";
    }
    std::cout << std::endl;
 };