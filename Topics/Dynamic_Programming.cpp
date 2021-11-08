// 5. Longest Palindromic Substring
// dp[i,j]: substring from i to j (inclusive) is palindromic
// dp[i,j]	= 1									if j == i
//			= (s[j] == s[i])					if j = i + 1
//			= (s[j] == s[i]) && dp[i+1, j-1]	if j > i + 1
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int n = s.size(), start = 0, len = 1;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i <= j; ++i) {	// i <= j
                dp[i][j] = (s[i] == s[j]) &&
                        (j - i < 2 || dp[i + 1][j - 1]); // dp
                if (dp[i][j] && (len < j - i + 1)) {
                    len = j - i + 1;
                    start = i;
                }
            }
        }
        return s.substr(start, len);
    }
};

// 62. Unique Paths
// dp[i,j]: num of unique paths at position [i,j]
// dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
class Solution {
public:
    int uniquePaths(int m, int n) { // n rows, m columns
        vector<vector<int>> dp(n, vector<int>(m));
        for (int i = 0; i < n; ++i) dp[i][0] = 1;
        for (int i = 0; i < m; ++i) dp[0][i] = 1;
        for (int i = 1; i < n; ++i) 
            for (int j = 1; j < m; ++j)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        return dp[n - 1][m - 1];
    }
};

// 64. Minimum Path Sum
// dp[i,j]: minimum path sum till position [i,j]
// dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1])
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) dp[i][0] = dp[i - 1][0] + grid[i][0];
        for (int i = 1; i < n; ++i) dp[0][i] = dp[0][i - 1] + grid[0][i];
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        return dp[m - 1][n - 1];
    }
};

// 70. Climbing Stairs
// dp[i]: total num of ways climbing to position [i]
// dp[i] = dp[i - 1] + dp[i - 2]
class Solution {
public:
    int climbStairs(int n) {
        if (n == 1) return 1; // must check
        vector<int> dp(n);
        dp[0] = 1; dp[1] = 2; // n = 1; n = 2
        for (int i = 2; i < n; ++i)
            dp[i] = dp[i - 1] + dp[i - 2];
        return dp.back();
    }
};

// 96. Unique Binary Search Trees
// Catalan Number
// dp[i]: number of unique BST that store values 1,..,i
// dp[i] += dp[j] * dp[i -1 - j]
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1); // dp[n] for n
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; ++i)
            for (int j = 0; j < i; ++j)
                dp[i] += dp[j] * dp[i -1 - j]; //
        return dp.back();
    }
};

// 139. Word Break
// dp[i]: substr s[0:i] is breakable
// dp[i] = dp[j] && wordSet.count(s.substr(j, i - j), for 0 <= j < i
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1); // dp[i]: s[0:i] is breakable
        dp[0] = true;
        for (int i = 0; i < dp.size(); ++i) { // dp.size(), not s.size()
            for (int j = 0; j < i; ++j) {
                if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp.back();
    }
};

// 140. Word Break II: return all possible breaked sentences
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string, vector<string>> m; // string--breaked words
        return wordBreak(s, wordDict, m);
    }
    vector<string> wordBreak(string s, vector<string> & wordDict, unordered_map<string, vector<string>> & m) {
        if (m.count(s)) return m[s];
        if (s.empty()) return {""}; // {""}, not ""
        vector<string> res;
        for (string word : wordDict) {
            if (s.substr(0, word.size()) != word) continue; // first substr == word
            vector<string> remain = wordBreak(s.substr(word.size()), wordDict, m); // remaining part
            for (string str : remain) {
                res.push_back(word + (str.empty() ? "" : " ") + str);
            }
        }
        return m[s] = res;
    }
};

// 300. Longest Increasing (can be non-continuous) Subsequence
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1); // longest subsquenece ending up at position i
        int res = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) // or <= when duplicate num exist
                    dp[i] = max(dp[i], dp[j] + 1); // 
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};

// 1027. Longest Arithmetic Sequence
// Input: [9,4,7,2,10]; Output: 3; Explanation: [4,7,10].
// dp[diff][i]: longest arithmetic sequence at position i with the diff value_comp
// dp[diff][i] = max(dp[diff][j] + 1, dp[diff][i]); // int diff = A[i] - A[j]
class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        if (A.size() <= 1) return A.size();
        unordered_map<int, unordered_map<int, int>> dp;
        int res = 0;
        for (int i = 0; i < (int)A.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                int diff = A[i] - A[j];
                if(!dp[diff].count(i)) dp[diff][i] = 2;
                dp[diff][i] = max(dp[diff][j] + 1, dp[diff][i]);
                res = max(res, dp[diff][i]);
            }
        }
        return res;
    }
};

// 123. Best Time to Buy and Sell Stock III
// You may complete at most two transactions.
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int n = prices.size(), k = 3; // k = 3 for two transactions
        vector<vector<int>> global(n, vector<int>(k, 0)), local(n, vector<int>(k, 0));
        for (int i = 1; i < n; ++i) {
            int diff = prices[i] - prices[i - 1];
            for (int j = 1; j < k; ++j) {
                local[i][j] = max(global[i - 1][j - 1], local[i - 1][j]) + diff;
                global[i][j] = max(local[i][j], global[i - 1][j]);
            }
        }
        return global.back().back();
    }
};

// 718. Maximum Length of Repeated Subarray (continuous)
// Input: A: [1,2,3,2,1]; B: [3,2,1,4,7]; Output: 3 [3,2,1]
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int res = 0, m = A.size(), n = B.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = A[i - 1] == B[j - 1] ? dp[i - 1][j - 1] + 1 : 0;
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }
};
// Longest common subsquenece (non-continuous)
int LCS(string s1, string s2, int n1, int n2) {
    int res = 0;
    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            dp[i][j] = s1[i - 1] == s2[j - 1] ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
            res = max(res, dp[i][j]);
        }
    }
    return dp[n1][n2];
}

// 1320. Minimum Distance to Type a Word Using Two Fingers
// Input: word = "CAKE"; Output: 3
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
            int now = word[i] - 'A', to = word[i + 1] - 'A';          
            sum += dist(now, to);              
            for (int j = 0; j < 26; ++j)
                dp[now] = max(dp[now], dp[j] + dist(now, to) - dist(j, to));            
            save = max(save, dp[now]);
        }       
        return sum - save;
    }
};

// 871. Minimum Number of Refueling Stops
// station[i][0]: dist to the starting position, station[i][1]: liters of gas.
// DP: O(n^2)
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        const int n = stations.size();
        // dp[i]: max distance to go with i stops
        vector<long> dp(n + 1, startFuel);
        // for each station
        for (int i = 0; i < n; ++i) {
            // for j stops, start from high to low to avoid reusing station i
            for (int j = i + 1; j >= 1; --j)
                // if we can reach station i with j - 1 stops,
                // we can reach dp[j] + station[i][1] with j stops
                if (dp[j - 1] >= stations[i][0])
                    dp[j] = max(dp[j], dp[j - 1] + stations[i][1]);
        }
        for (int i = 0; i < dp.size(); ++i)
            if (dp[i] >= target) return i;
        return -1;
    }
};
// Heap: O(nlogn)
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int cur = startFuel, stops = 0, i = 0;
        priority_queue<int> q; // gas (high to low) of reachable stations
        while (true) {
            if (cur >= target) return stops; // currently reachable distance >= target
            while (i < stations.size() && stations[i][0] <= cur)
                q.push(stations[i++][1]); // max heap: all reachable stations
            if (q.empty()) break; // cur dist not reach target, and no stations available
            cur += q.top(); // fuel at the station with highest gas
            q.pop();
            ++stops;
        }
        return -1;
    }
};

