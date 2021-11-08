// 53. Maximum (continuous) Subarray
// Greedy: O(n)
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN, curSum = 0;
        for (int num : nums) {
            curSum = max(curSum + num, num);
            res = max(res, curSum);
        }
        return res;
    }
};
// DC : O(logn)
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) return 0;
        return maxSubArray_DC(nums, 0, (int)nums.size() - 1);
    }
    int maxSubArray_DC(vector<int>& nums, int left, int right) {
		//only check (left == right) results in runtime error 
        if (left >= right) return nums[left];
        int mid = left + (right - left) / 2;
        int leftmax = maxSubArray_DC(nums, left, mid - 1);
        int rightmax = maxSubArray_DC(nums, mid + 1, right);
        int midmax = nums[mid], tmp = midmax;
        for (int i = mid - 1; i >= left; i--) {
            tmp += nums[i];
            midmax = max(midmax, tmp);
        }
        tmp = midmax;
        for (int i = mid + 1; i <= right; i++) {
            tmp += nums[i];
            midmax = max(midmax, tmp);
        }
        return max(midmax, max(leftmax, rightmax));
    }
};

// 148. Sort a linked list in O(n log n) time using constant space complexity.
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode * slow = head, * fast = head, * mid = head;
        while (fast && fast->next) { // slow at middle when fast hits the end
            mid = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        mid->next = NULL; // divide the list, and conquer (merge)
        return mergeTwoSortedLists(sortList(head), sortList(slow));
    }
    ListNode * mergeTwoSortedLists(ListNode * l1, ListNode * l2) {
        ListNode * dummyHead = new ListNode(-1);
        ListNode * cur = dummyHead;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            }
            else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        if (!l1) cur->next = l2;
        if (!l2) cur->next = l1;
        return dummyHead->next;
    }
};

// 215. Kth Largest Element in an Array
// Input: [3,2,3,1,2,4,5,5,6] and k = 4; Output: 4
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) { // Divide and Conquer
            int pos = findKthLargest(nums, left, right);
            if (pos == k - 1) return nums[pos];
            else if (pos > k - 1) right = pos - 1;
            else left = pos + 1;
        }
    }
	// quick sort partition: decreasing
    int findKthLargest(vector<int> & nums, int left, int right) { 
        int pivot = nums[left], l = left + 1, r = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot)
                swap(nums[l++], nums[r--]);
            if (nums[l] >= pivot) l++;	// decreasing
            if (nums[r] <= pivot) r--;	// decreasing
        }
        swap(nums[left], nums[r]);
        return r;
    }
};

// 95. Unique Binary Search Trees II
// Given an integer n, generate all structurally unique BST's that store values 1 ... n.
// DC, similar to Q241
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return generateTrees(1, n);
    }
    vector<TreeNode*> generateTrees(int start, int end) {
        if (start > end) return {nullptr};  // vector {nullptr}
        vector<TreeNode*> res;
        for (int i = start; i <= end; ++i) {
            vector<TreeNode*> left = generateTrees(start, i - 1);   // divide
            vector<TreeNode*> right = generateTrees(i + 1, end);
            for (auto a : left) {   // conque
                for (auto b : right) {
                    TreeNode* node = new TreeNode(i);
                    node->left = a;
                    node->right = b;
                    res.push_back(node);
                }
            }
        }
        return res;
    }
};

// 241. Different Ways to Add Parentheses
// DC
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        if (input.empty()) return {};
        vector<int> res;
        for (int i = 0; i < input.size(); ++i) {    // divide and conquer at position i
            if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
                vector<int> left = diffWaysToCompute(input.substr(0, i)); // calculate left substring
                vector<int> right = diffWaysToCompute(input.substr(i + 1)); // calculate right substring
                for (int j = 0; j < left.size(); ++j) {     // conquer
                    for (int k = 0; k < right.size(); ++k) {
                        if (input[i] == '+') res.push_back(left[j] + right[k]);
                        else if (input[i] == '-') res.push_back(left[j] - right[k]);
                        else res.push_back(left[j] * right[k]);
                    }
                }
            }
        }
        if (res.empty()) res.push_back(stoi(input));    // input only includes a number
        return res;
    }
};

// 315. Count of Smaller Numbers After Self
// Input: nums = [5,2,6,1]; Output: [2,1,1,0]
class Solution {    
public:
    vector<int> countSmaller(vector<int>& nums) {        
        int n = nums.size();
        if (n == 0) return {};
        
        vector<int> sortedNums = nums;        
        vector<int> counts(n,0);
        DivideConque(nums,sortedNums, counts, 0, n - 1); 
        return counts;
    }
    
    void DivideConque(vector<int>& nums, vector<int>& sortedNums, 
                      vector<int>& counts, int start, int end){
        if (start == end) return;
        
        // divide: sort each part
        int mid = start + (end - start) / 2;
        DivideConque(nums, sortedNums, counts, start, mid);
        DivideConque(nums, sortedNums, counts, mid + 1, end);
        
        // since nums[start, mid] and nums[mid + 1, end] are sorted
        // for each num in [start, mid], we know how many num in [mid + 1, end] less than it
        for (int i = start; i <= mid; i++) {
            auto pos = lower_bound(sortedNums.begin() + mid + 1, 
                                   sortedNums.begin() + end + 1, nums[i]);            
            counts[i] += pos - (sortedNums.begin() + mid + 1);
        }
        
        // here use sort(), but implemented as mergesort can be more faster        
        sort(sortedNums.begin() + start, sortedNums.begin() + end + 1);  
    }
};

// 327. Count of Range Sum
// Input: nums = [-2,5,-1], lower = -2, upper = 2
// Output: 3; ranges: 0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.
// Time: O(nlog(n)); Space: O(n)
class Solution {
public:
    // function counts the ranges with sum greater than or equal to k
    int countAndSort(vector<long>::iterator begin, vector<long>::iterator end, int k) {
	    // if subarray contains a single element
        if(begin + 1 == end) return (*begin >= k);
        
        auto mid = begin + (end - begin) / 2;
        int res = countAndSort(begin, mid, k) + countAndSort(mid, end, k);
        
        for(auto i = begin, j = mid; i != mid; ++i) {
            // we know that if the value of (j - i) >= k, 
            // then for all greater values of j this condition will hold until
            // i is increased, as both the arrays are sorted
            while(j != end && (long)*j - (long)*i < (long)k)
                j++;
            res += (end - j);
        }
        inplace_merge(begin, mid, end);

        return res;
    }
    
	// calling the main function with a copy of sums array
    int countGreaterThanK(vector<long> nums, int k) {
        return countAndSort(nums.begin(), nums.end(), k);
    }
    
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long> sums(n, 0);
        sums[0] = nums[0];
        // generating sums sum array
        for(int i = 1; i < n; ++i)
            sums[i] += sums[i - 1] + nums[i];
			
        return countGreaterThanK(sums, lower) - countGreaterThanK(sums, upper + 1);
    }
};









