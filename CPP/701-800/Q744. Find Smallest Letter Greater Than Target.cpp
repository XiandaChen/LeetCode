class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        if (target < letters[0] || letters[letters.size() - 1] < target) return letters[0];
        int n = letters.size(), left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target < letters[mid]) right = mid - 1;
            else left = mid + 1; // target >= letters[mid]; to find 
        }
        return letters[left % n]; // letters wrap around
    }
};