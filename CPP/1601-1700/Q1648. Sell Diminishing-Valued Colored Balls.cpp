// // priority_queue sell one by one: O(klogn) time limit exceeded
// // inventory = [1000000000], orders = 1000000000
#define ull unsigned long long
const int mod = 1e9 + 7;
class Solution {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        priority_queue<int> q(inventory.begin(), inventory.end()); // maxHeap
        long res = 0, sameBalls = 1; // sameBalls: num balls having the same max value
        
        while (orders > 0) {
            int t = q.top(); q.pop();
            // except sameBalls, may need other balls to server the orders
            if (!q.empty() && (t - q.top()) * sameBalls <= orders) { // 
                res = (res + summation(q.top() + 1, t) * sameBalls) % mod;
                orders -= (t - q.top()) * sameBalls;
            }
            else { // sameBalls can server the orders
                int x = orders / sameBalls; // each sameBalls serve x orders
                int y = orders % sameBalls;  // remaining orders after serving x*sameBalls orders
                ull b = t - x; // value for each sameBalls after serving x orders
                res = (res + summation(b + 1, t) * sameBalls) % mod; // [t, t-1,..,b+1] for each sameBalls
                res = (res + b * y) % mod; // one ball (value of b) for each orders (y)
                break;
            }
            sameBalls++;
        }
        
        
        return res;
    }
    
    // sum of [b, b+1, ..., e]
    ull summation(ull b, ull e) { // b: begin, e: end of the array
        ull m = b + e, n = e - b + 1;  // m: sum of the begin and end elem, n: num of elems
        return m * n / 2 % mod; // m * n may overflow int
    };
};
