class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int cursum = numbers[left] + numbers[right];
            if (cursum == target) return {left + 1, right + 1};
            else if (cursum > target) --right;
            else ++left;
        }
        return {};
    }
};