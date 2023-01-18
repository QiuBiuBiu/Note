class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        multiset<int, greater<int> > s; // set按从大到小的顺序排列
        vector<int> res;
        if (k == 0) return res;

        for (auto a : arr)
        {
            if (s.size() < k) s.insert(a);
            else
            {
                if (a < *s.begin()) // set里的第一个元素即最大值
                {
                    s.erase(s.begin());
                    s.insert(a);
                }
            }
        }
        
        for (auto it = s.begin(); it != s.end(); it++)
        {
            res.push_back(*it);
        }
        return res;
    }
};