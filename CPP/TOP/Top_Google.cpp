// 981. Time Based Key-Value Store
class TimeMap {
public:
    TimeMap() {
    }
    
    void set(string key, string value, int timestamp) {
        data[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        if (!data.count(key)) return "";
        
        auto it = data[key].upper_bound(timestamp); // upper_bound: the first larger than timestamp
        if (it == data[key].begin()) return "";
        --it; // return value of timestamp_prev <= timestamp
        return it->second;
    }
private:
    unordered_map<string, map<int, string>> data; // key-[time, value]
};

// 1048. Longest String Chain
// Input: words = ["a","b","ba","bca","bda","bdca"]; Output: 4
// Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        auto cmp = [] (string & a, string & b) {
            return a.size() < b.size(); // sort increasing
        };
        sort(words.begin(), words.end(), cmp);
        
        int n = words.size(), res = 1;
        unordered_map<string, int> mp; // word-#longestStrChain if including word
        
        for (string word : words) {
            mp[word] = 1;
            for (int i = 0; i < (int)word.size(); i++) {
                string pre = word.substr(0, i) + word.substr(i + 1);  
                if (mp.count(pre)) { // if it is predecessor 
                    mp[word] = max(mp[word], mp[pre] + 1);
                    res = max(res, mp[word]);
                }
            }
        }
        
        return res;
    }
};

// 735. Asteroid Collision
// Input: asteroids = [10,2,-5]; Output: [10]
// Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;
        vector<int> res;
        
        for (int a : asteroids) {
            if (st.empty() || a > 0 ) {
                st.push(a);
            }
            else {
                while (!st.empty() && 0 < st.top() && st.top() < abs(a)) st.pop();
                
                if (!st.empty() && st.top() == abs(a)) {
                    st.pop(); // both explode
                }
                else if (st.empty() || st.top() < 0) {
                    st.push(a);
                }
            }
        }
        
        while (!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        
        reverse(res.begin(), res.end());
        
        return res;
    }
};

// 562. Longest Line of Consecutive One in Matrix
class Solution {
public:
    int longestLine(vector<vector<int>>& mat) {
        if (mat.empty()) return 0;
        
        int m = mat.size(), n = mat[0].size(), res = 0;
        
        // horizontal
        for (int i = 0; i < m; i++) { 
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        // vertical
        for (int j = 0; j < n; j++) { 
            int cnt = 0;
            for (int i = 0; i < m; i++) {
                if (mat[i][j] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        // upper diagonal, starting from [x=0][y=j], then x++,y++
        for (int j = 0; j < n; j++) {
            int cnt = 0;
            for (int x = 0, y = j; x < m && y < n; x++, y++) {
                if (mat[x][y] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        // lower diagonal, starting from [x=1][y=0], then x++,y++
        for (int i = 1; i < m; i++) {
            int cnt = 0;
            for (int x = i, y = 0; x < m && y < n; x++, y++) {
                if (mat[x][y] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        // upper anti-diagonal, starting from [x=0][y=n-j-1], then x++,y--
        for (int j = 0; j < n; j++) {
            int cnt = 0;
            for (int x = 0, y = n - j - 1; x < m && y >= 0; x++, y--) {
                if (mat[x][y] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        // lower anti-diagonal, starting from [x=i][y=n-1], then x++,y--
        for (int i = 1; i < m; i++) {
            int cnt = 0;
            for (int x = i, y = n - 1; x < m && y >= 0; x++, y--) {
                if (mat[x][y] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        return res;
    }
};
























































