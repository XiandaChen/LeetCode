class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        for (auto num : nums) {
            q.push(num);
            if (q.size() > k) q.pop();
        }
        K = k;
    }
    
    int add(int val) {
        q.push(val);
        if (q.size() > K) q.pop();
        return q.top();
    }
private:
    priority_queue<int, vector<int>, greater<int>> q; // minHeap: only maintain top k elements
    int K; 
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */