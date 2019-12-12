class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int H) {
        int left = 1, right = 1e9; // 1 <= piles[i] <= 10^9
        // binary search to find proper eating speed
        while (left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for (int pile : piles) {
                // pile=9, mid=4, cnt=(9 + (4 -1))/4=3
                // cnt += (pile + mid - 1) / mid; 
                cnt += ceil(float(pile) / mid);
            }
            if (cnt > H) left = mid + 1; // eating slow
            else right = mid;
        }
        return right;
    }
};