/*
Leetcode 146: https://leetcode.cn/problems/lru-cache/description/

class LRUCache {
private:
    struct node {
        node *left = NULL;
        node *right = NULL;
        int key, val;
        node(int Key, int Val) : left(NULL), right(NULL), key(Key), val(Val) {};
    };
public:
    unordered_map<int, node*> mp;
    node *dummyHead = NULL;
    node *dummyTail = NULL;
    int size;
    int capacity;

    LRUCache(int capacity) {
        this->capacity = capacity;
        size = 0;
        dummyHead = new node(-1, -1);
        dummyTail = new node(-1, -1);
        dummyHead->right = dummyTail;
        dummyTail->left = dummyHead;
    }
    
    int get(int key) {
        if (mp.find(key) != mp.end())
        {
            int val = mp[key]->val;
            erase(mp[key]);
            mp[key] = insertFront(key, val);
            return val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (mp.find(key) != mp.end())
        {
            erase(mp[key]);
        }
        else
        {
            if (size == capacity)
            {
                mp.erase(dummyTail->left->key);
                removeBack();
            }
            else
            {
                ++size;
            }
        }
        mp[key] = insertFront(key, value);
    }

private:
    node* insertFront(int key, int val)
    {
        node *tmp = new node(key, val);
        tmp->right = dummyHead->right;
        tmp->left = dummyHead;
        dummyHead->right->left = tmp;
        dummyHead->right = tmp;
        return tmp;
    }
    void removeBack()
    {
        node *tmp = dummyTail->left;
        dummyTail->left = tmp->left;
        tmp->left->right = dummyTail;
        delete tmp;
    }
    void erase(node* cur)
    {
        node *pre = cur->left;
        node *nex = cur->right;
        pre->right = nex;
        nex->left = pre;
        delete cur;
    }
};
*/
