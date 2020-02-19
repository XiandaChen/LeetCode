class Solution {
public:
    int minimumDistance(string word) {
        auto dist = [] (int c1, int c2) {
            return abs(c1 / 6 - c2 / 6) + abs(c1 % 6 - c2 % 6);
        };
        
        int n = word.size();
        int sum = 0; // total dist if using only one finger
        int save = 0;  // total save if using extra finger
        vector<int> dp(27, 0); // dp[i]: max saving till second finger on pos i
        
        for (int i = 0; i < n - 1; ++i) {
            int now = word[i] - 'A';
            int to = word[i + 1] - 'A';
            
            sum += dist(now, to);  
            
            for (int j = 0; j < 26; ++j)
                dp[now] = max(dp[now], dp[j] + dist(now, to) - dist(j, to));
            
            save = max(save, dp[now]);
        }
        
        return sum - save;
    }
};