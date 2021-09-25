class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int n = letters.size(), left = 0, right = n - 1;
        if (target < letters[0] || target >= letters[n - 1]){ // '>='
            return letters[0];
        }
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (letters[mid] <= target) left = mid + 1;
            else right = mid - 1;
        }
        
        // loop ends at left = right + 1
        return letters[left];
    }
};