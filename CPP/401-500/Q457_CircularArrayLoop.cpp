class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        vector<bool> visited(n);
        for (int i = 0; i < n; ++i) {
            if (visited[i]) continue;
            visited[i] = true;
            
            int cur = i; 
            unordered_map<int, int> m; // cur-next
            while (true) {
                int next = ((cur + nums[cur]) % n + n) % n; // %n, %n: nums[cur] large negative
                if (next == cur || nums[next] * nums[cur] < 0) break;
                if (m.count(next)) return true;
                m[cur] = next;
                cur = next;
                visited[next] = true;
            }
        }
        return false;
    }
};
