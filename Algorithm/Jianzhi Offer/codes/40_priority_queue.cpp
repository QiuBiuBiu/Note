class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        priority_queue<int, vector<int>, less<int> > q; // 最大堆
        vector<int> res;
        if (k == 0) return res;

        for (auto a : arr)
        {
            if (q.size() < k) q.push(a); // size小于k，直接放入堆中
            else
            {
                if (a < q.top()) // 当新元素比堆顶元素小，则将堆顶元素(堆中的最大值)弹出，将新元素放入堆中
                {
                    q.pop();
                    q.push(a);
                }
            }
        }
        
        while (!q.empty()) 
        {
            res.push_back(q.top());
            q.pop();
        }

        return res;
    }
};