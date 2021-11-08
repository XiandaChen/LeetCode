// 908. Smallest Range I
// Add x to A[i], where -K <= x <= K, to get smallest diff b/w max(B) and min(B)
class Solution {
public:
    int smallestRangeI(vector<int>& A, int K) {
		// max(0, ..)
        return max(0, (*max_element(A.begin(), A.end()) - K) 
		- (*min_element(A.begin(), A.end()) + K));
    }
};
// 910. Smallest Range II
// Add x to A[i], where x = -K or x = K, to get smallest diff b/w max(B) and min(B)
class Solution {
public:
    int smallestRangeII(vector<int>& A, int K) {
        sort(A.begin(), A.end());
        int n = A.size(), res = A[n - 1] - A[0];
        // small nums A[0:i]: add K; large nums A[i+1, n-1]: add -K
        for (int i = 0; i < n - 1; ++i) { // n-1 for A[i+1]
            int mx = max(A[i] + K, A[n - 1] - K);
            int mn = min(A[0] + K, A[i + 1] - K);
            res = min(res, mx - mn);
        }
        return res;
    }
};

// 1353. Maximum Number of Events That Can Be Attended
// Input: events = [[1,4],[4,4],[2,2],[3,4],[1,1]];  Output: 4
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end(), [](vector<int> &a, vector<int> &b) {
           return a[1] < b[1]; // sort increasing by end time 
        });
        int res = 0;
        vector<bool> attend(100001, false); // events.length <= 10^5
        for (auto e : events) {
            for (int i = e[0]; i <= e[1]; ++i) {
                if (attend[i]) continue; // if day i had been for other events
                attend[i] = true;
                ++res;
                break; // must, event e can be attended at day i
            }
        }   
        return res;
    }
};

// 402. Remove K Digits
// Input: num = "10200", k = 1; Output: "200"
class Solution {
public:
    string removeKdigits(string num, int k) {
        string res = "";  // string works as stack: pop_back
        int n = num.size(), keep = n - k;
        for (char c : num) {
            while (k && res.size() && res.back() > c) { // maintain increasing stack
                // remove the last char in res if it is larger than c
                res.pop_back(); --k;
            }
            res.push_back(c);
        }
        res.resize(keep); //must, num='12345', k=2, res='12345', res.resize(5-2)='123'
        // remove leading zero ('0200'), if any
        while (res.size() && res[0] == '0') res.erase(res.begin());
        return res.empty() ? "0" : res;
    }
};

// 738. Monotone Increasing Digits
// Input: N = 332; Output: 299: 332->322->222->299
class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string num = to_string(N);
        int n = num.size(), j = n;
        // traverse from the last to the second
        for (int i = n - 1; i > 0; --i) { 
            if (num[i - 1] <= num[i]) continue; // continue if monotone increasing
            --num[i - 1]; //num[i-1, i]: high-low decreasing
            j = i;
        }
        for (int i = j; i < n; ++i)
            num[i] = '9'; // convert num[j:n] to '9'
        return stoi(num);
    }
};