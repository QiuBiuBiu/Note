class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> res(k);
        if (k == 0) return res;

        int start = 0, end = arr.size() - 1;
        int index = partition(arr, start, end);

        while (index != k - 1)
        {
            if (index > k - 1)
            {
                end = index - 1;
            }
            else
            {
                start = index + 1;
            }
            index = partition(arr, start, end);
        }

        for (int i = 0; i < k; i++)
            res[i] = arr[i];
        return res;
    }

/*
    取随机数的通用公式: a + rand() % n；其中的 a 是起始值，n 是整数的范围。

    要取得 [a,b) 的随机整数，使用 (rand() % (b-a)) + a;
    要取得 [a,b] 的随机整数，使用 (rand() % (b-a+1)) + a;
    要取得 (a,b] 的随机整数，使用 (rand() % (b-a)) + a + 1;
*/
    int partition(vector<int>& arr, int start, int end)
    {
        int random_index = (rand() % (end - start + 1)) + start; // 快排算法中这里是随机选择[start, end]中的一个
        swap(arr[random_index], arr[end]);
        int index = start - 1;
        for (int i = start; i < end; i++)
        {
            if (arr[i] < arr[end])
            {
                ++index;
                if (index != i)
                    swap(arr[index], arr[i]);
            }
        }
        ++index;
        swap(arr[index], arr[end]);
        return index;
    }
};