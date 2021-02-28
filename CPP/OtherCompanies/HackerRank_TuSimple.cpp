// 300. Longest Increasing Subsequence (LIS)
// Input: nums = [10,9,2,5,3,7,101,18]; Output: 4, i.e., [2,3,7,101]
// Method 1: DP, O(n^2), dp[i]=LIS ending with nums[i]; 
// for 0<i<n-1, for 0<j<i, if(nums[j]<nums[i]): dp[i]=max(dp[i],dp[j]+1)
// Method 2: Binary Search, O(nlogn)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int> subnums{nums[0]};
        for (int a : nums) {
            if (a < subnums[0]) { // switch the smallest one
                subnums[0] = a;
            }
            else if (a > subnums.back()) { // add larger ones
                subnums.push_back(a);
            }
            else { // change the first num that no-less than a
                int left = 0, right = subnums.size();
                while (left < right) { // binary search
                    int mid = left + (right - left) / 2;
                    if (subnums[mid] < a) left = mid + 1;
                    else right = mid;
                }
                subnums[right] = a;
            }
        }
        return subnums.size();
    }
};

// 818. Race car
// Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)
// Instruction "A" (accelerate): position += speed, speed *= 2.
// Instruction "R" (reverse): if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)
// For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.
// For some target position, find the length of the shortest sequence of instructions to get there.
// Input: target = 6; Output: 5
// Explanation: The shortest instruction sequence is "AAARA".
// Your position goes from 0->1->3->7->7->6.
class Solution {
public:
    int racecar(int target) {
        int res = 0;
        queue<pair<int, int>> q{{{0, 1}}}; // position-speed
        unordered_set<string> visited{{"0,1"}}; // states: "pos,speed"
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                int pos = q.front().first, speed = q.front().second;
                q.pop();
                if (pos == target) return res;

                // instruction accelerate: position += speed, speed *= 2
                int newPos = pos + speed, newSpeed = speed * 2;
                string state = to_string(newPos) + "," + to_string(newSpeed);
                if (!visited.count(state) && 0 < newPos && newPos <= target * 2) {
                    q.push({newPos, newSpeed});
                    visited.insert(state);
                }

                // instruction reverse: position stays the same; 
                // speed is positive then speed = -1 , otherwise speed = 1
                newPos = pos;
                newSpeed = (speed > 0) ? -1 : 1;
                state = to_string(newPos) + "," + to_string(newSpeed);
                if (!visited.count(state) && 0 < newPos && newPos <= target * 2) {
                    q.push({newPos, newSpeed});
                    visited.insert(state);
                }
            }
            ++res;
        }
        return -1;
    }
};



