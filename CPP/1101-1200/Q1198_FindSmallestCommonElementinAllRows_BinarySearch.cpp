class Solution {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {
        for (int val : mat[0]) {
            bool flg = true;
            for (int i = 1; i < mat.size(); ++i) {
                if (!validate(mat[i], val)) {
                    flg = false; break;
                }
            }
            if (flg) return val;
        }
        return -1;
    }
    bool validate(vector<int> & nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return true;
            else if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return false;
    }
};