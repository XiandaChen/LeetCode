using ll = long long;

class Solution {
public:
    long long wonderfulSubstrings(string word) {
        // substring is encoded as bitmask state
        // ith bit of bitmask is 1/0 -> ith char present odd/even times
        unordered_map<int, ll> mp; // substring state - count
        
        mp[0] = 1; // NOTE, must
        ll state = 0, res = 0;  // NOTE, ll, not int
        
        for (char & c : word) {
            // state for substring [0,i]
            state ^= (1 << (c - 'a')); // flip ith bit of state for substring [0,i-1]
            
            // case 1: all chars between substring [j+1, i] present even times 
            // that is, find pos j such that state[0,j] == state[0,i]
            res += mp[state];
            
            // case 2: only one char between substring [j+1, i] presents odd times
            // that is, find pos j such that state[0,j] only diff from state[0,i] at one bit
            // for example, for 'a', state[0,j]='0101010101', state[0,i]='0101010100'
            for (char p = 'a'; p <= 'j'; p++) {
                int tmp_state = state ^ (1 << (p - 'a'));
                res += mp[tmp_state];
            }
            
            mp[state]++;
        }
        
        return res;
    }
};