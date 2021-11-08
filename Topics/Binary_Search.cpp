// Binary Search Notes
// int mid = left + (right - left) / 2;
// transition condition
// 		case 1: right = mid - 1; left = mid;
//				then loop: while (left < right - 1)
//				result: left=right
// 		case 2: left = mid + 1; right = mid;
//				then loop: while (left < right)
//				result: check if left or right is correct, see Q981

// 4. Median of Two Sorted Arrays
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        if (len1 > len2)
            return findMedianSortedArrays(nums2, nums1);
        
        int low = 0, high = len1, halfLen = (len1 + len2 + 1) / 2;
        while (low <= high) {
            int cut1 = (low + high) / 2;
            int cut2 = halfLen - cut1;

            if (cut1 > low && nums1[cut1-1] > nums2[cut2]) {
                high = cut1 - 1;    // move toward left in nums1
            }
            else if (cut1 < high && nums2[cut2-1] > nums1[cut1]) {
                low = cut1 + 1;     // move toward right in nums1
            }
            else {
                int maxLeft1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
                int minRight1 = (cut1 == len1) ? INT_MAX : nums1[cut1];

                int maxLeft2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
                int minRight2 = (cut2 == len2) ? INT_MAX : nums2[cut2];
                
                if ((len1 + len2) % 2 == 1)     // total number is odd
                    return max(maxLeft1, maxLeft2);
                else 
                    return (double) (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2;
            }
        }
        
        return 0;
    }
};

// 33. Search in Rotated Sorted Array
// Input: nums = [4,5,6,7,0,1,2], target = 0; 	Output: 4
// (nums[mid] < nums[right]): right part is sorted
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < nums[right]) { // right part is sorted
                if (nums[mid] < target && target <= nums[right]) left = mid + 1;
                else right = mid - 1;
            }
            else { // left part is sorted
                if (nums[left] <= target && target < nums[mid]) right = mid - 1;
                else left = mid + 1;
            }
        }
        return -1;
    }
};

// 81. Search in Rotated Sorted Array II
// nums may contain duplicates
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return true;
            
            if (nums[mid] < nums[right]) { // right part is sorted
                if (nums[mid] < target && target <= nums[right]) left = mid + 1;
                else right = mid - 1;
            }
            else if (nums[mid] > nums[right]) { // left part is sorted
                if (nums[left] <= target && target < nums[mid]) right = mid - 1;
                else left = mid + 1;
            }
            else { // duplicates, nums[mid]==nums[right], [3 1 1] and [1 1 3 1]
                --right;
            }
        }
        return false;
    }
};

// 153. Find Minimum in Rotated Sorted Array
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            // right part is sorted incleasing, search left part
            if (nums[mid] < nums[right]) right = mid;
            else left = mid + 1;
        }
        return nums[left];
    }
};

// 34. Find First and Last Position of Element in Sorted Array
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) return {-1, -1};
        vector<int> res (2, -1);
        int left = 0, right = nums.size();
        // find the leftmost index
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }
        // check if leftindx is within the array bounds and target is in the array
        if (right == nums.size() || nums[right] != target) return res;
        res[0] = right;
        left = 0, right = nums.size();
        // find the rightmost index
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) left = mid + 1;
            else right = mid;
        }
        res[1] = right - 1;
        return res;
    }
};
//
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = firstGreaterEqualto(nums, target);
        // check if leftindx is within the array bounds and target is in the array
        if (left == nums.size() || nums[left] != target) return {-1, -1};
        return {left, firstGreaterEqualto(nums, target + 1) - 1};
    }
    int firstGreaterEqualto(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }
        return right;
    }
};

// 240. Search a 2D Matrix II
// Integers in each row (column) are sorted in ascending from left to right (top to bottom).
// Time: O(M+N)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
		// must check  matrix[0].empty()
        if (matrix.empty() || matrix[0].empty()) return false; 
        int m = matrix.size(), n = matrix[0].size(), x = m - 1, y = 0;
        while (true) { // binary search from the left-bottom coner
            if (matrix[x][y] == target) return true;
            else if (matrix[x][y] > target) --x;
            else ++y;
            if (x < 0 || y >= n) return false;
        }
        return false;
    }
};
class Solution {  // Time optimize ==> O(M + logN) or O(logM + N)
public:
    bool binarySearch (vector<int> & matrix, int target) {
		int left = 0, right = matrix.size() - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;

			if (matrix[mid] == target) return true;
			else if (matrix[mid] > target) right = mid - 1;
			else left = mid + 1;
		}

		return false;
	}
	bool searchMatrix (vector<vector<int>> &matrix, int target) {
		if (matrix.empty() || matrix[0].empty()) return false;
		int m = (int)matrix.size(), n = (int)matrix[0].size();
		int i = 0, j = n - 1;

		while (i < m) {
			if (matrix[i][j] == target) return true;
			else if (matrix[i][j] > target) {
				if (binarySearch(matrix[i], target)) return true;
				i++;
			}
			else {
				i++;
			}
		}

		return false;
	}
};

// 287. Find the Duplicate Number
// Array contains n + 1 integers where each integer is between 1 and n (inclusive)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for (int num : nums)
                if (num <= mid) ++cnt;
            if (cnt <= mid) left = mid + 1;
            else right = mid;
        }
        return right;
    }
};

// 300. Longest Increasing (can be non-continuous) Subsequence
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> subs;
        for (int i = 0; i < (int)nums.size(); ++i) {
            int left = 0, right = subs.size();
			// binary search the num in subs larger or equal to nums[i]
            while (left < right) { 
                int mid = left + (right - left) / 2;
                if (nums[i] <= subs[mid]) right = mid;
                else left = mid + 1;
            }
			// nums[i] is larger than any num in subs
            if (right >= subs.size()) subs.push_back(nums[i]); 
            else subs[right] = nums[i];
        }
        return subs.size(); // length of LIS, but subs is not exactly an LIS
    }
};

// 29. Divide two integers without using multiplication, division and mod operator.
// Bit manipulation
class Solution {
public:
    int divide(int dividend, int divisor) {
        // -2147483648
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;
        int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
        long m = labs(dividend), n = labs(divisor), res = 0;
        while (m >= n) { // m is more than one times of n
            long t = n, p = 1;
            // m is at least two times of n
            // m, n, t in long type, in case (t << 1) larger than INT_MAX
            while (m >= (t << 1)) { 
                t <<= 1;
                p <<= 1; // quotient plus two
            }
            m -= t;
            res += p;
        }
        return (sign == 1) ? res : -res;
    }
};

// 264. Find the n-th ugly number (whose prime factors only include 2, 3, 5)
// Input: n = 10; Output: 12; Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12
class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue<long, vector<long>, greater<long>> q; // min heap
        q.push(1);
        for (int i = 1; i < n; ++i) {
            long t = q.top(); q.pop();
            while (!q.empty() && t == q.top()) q.pop(); // remove duplicates
            q.push(t * 2);
            q.push(t * 3);
            q.push(t * 5);
        }
        return q.top();
    }
};

// 1201. Ugly Number III
// Find the n-th ugly number (which are divisible by a or b or c)
// Input: n = 4, a = 2, b = 3, c = 4
// Output: 6
// Explanation: The ugly numbers are 2, 3, 4, 6, 8, 9, 10, 12... The 4th is 6.
class Solution {
public:
    int nthUglyNumber(int n, int A, int B, int C) {
        long a = long(A), b = long(B), c = long(C); // must done for bc in lcm()
        long ab = lcm(a, b), ac = lcm(a, c), bc = lcm(b, c), abc = lcm(a, bc);
        long left = 1, right = INT_MAX;
        while (left < right) {
            long mid = left + (right - left) / 2;
            // num of ugly numbers that are <= mid
            long k = mid / a + mid / b + mid / c 
                    - (mid / ab + mid / ac + mid / bc)
                    + mid / abc;
            if (k >= n) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
/*
Implement lcm (least common multiple) using gcd (greatest common divisor)
int gcd(int a, int b){ 
    if (b == 0) 
        return a;  
    return gcd(b, a % b);  
} 
int lcm(int a, int b) {  
	return (a * b) / gcd(a, b);  
}  
*/

// 50. Pow(x,n)
class Solution {
public:
    double myPow(double x, int n) {
        return n >= 0 ? myPowRec(x, n) : 1.0 / myPowRec(x, n);
    }
    double myPowRec(double x, int n) {
        if (n == 0) return 1;
        // (-1 % 2)==1; (-4 % 2)==0
        return myPowRec(x * x, n / 2) * (n % 2 ? x : 1);
    }
};

// 274. H-Index, sorting, O(nlogn)
// Input: citations = [3,0,6,1,5];	Output: 3 
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end(), greater<int>()); // decreasing order
        for (int i = 0; i < citations.size(); ++i)
            if (citations[i] <= i) return i;
        return citations.size();
    }
};
// 274. H-Index, hash map, O(n)
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        // cnt[i]: num of papers that has at least i citations
        vector<int> cnt(n + 1); 
        for (int c : citations) { // increasing order
            if (c <= n) ++cnt[c]; // record, if <= n
            else ++cnt[n]; // for paper whose citations > n, record in [n]
        }
        // traverse from right to left
        int sum = 0;
        for (int i = n; i >= 0; --i) {
            sum += cnt[i];
            if (i <= sum) return i; 
        }
        return 0;
    }
};
// 275. H-Index II, O(log(n))
// Input: citations = [0,1,3,5,6]; 	Output: 3 
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int len = citations.size(); 
        if (len == 0 || citations[len - 1] <= 0) return 0;
        int left = 0, right = len - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            // citations in increasing order, [0,1,3,5,6], check from right 
            // num of citations of (len-mid)-th paper is less than (len-mid)  
            if (citations[mid] < len - mid) 
                left = mid + 1;
            else // (len-mid)-th paper has at least (len-mid) citations
                right = mid;
        }
        return len - right;
    }
};

// Cut wood array into (>=) k pieces of the same length length
// What is the longest length you can get?
// ref. Q875. Koko Eating Bananas, Binary Search
int cutWoodMaxLen(vector<int> & woods, int k) {
    int left = 1, right = *max_element(woods.begin(), woods.end()); // #include <algorithm>
    while (left < right) {
        int mid = left + (right - left) / 2, cnt = 0;
        for (int wood : woods) {
            cnt += wood / mid; // num of pieces when cutting wood in lenght of mid
        }
		// increasing piece length
        if (cnt > k) left = mid + 1;  // error: if (cnt >= k)
        else right = mid;
    } 
    return right;
}

// 325. Maximum Size Subarray Sum Equals k
// Find the maximum length of a contiuous subarray that sums to k
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int res = 0, sum = 0;
        unordered_map<int, int> m; // sum[0:i]--i
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (sum == k) res = i + 1; // subarray[0:i] sum equals k
            else if (m.count(sum - k)) // subarray[j:i] sum equals k
                res = max(res, i - m[sum - k]);
            
            // to max subarray
            // add m[sum] only if no existed
            if (!m.count(sum)) m[sum] = i;
        }
        return res;
    }
};

// 209. Minimum Size Subarray Sum
// the minimal length of a contiguous subarray of which the sum ≥ s
// sliding window (two pointers): O(n)
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int left = 0, sum = 0, res = INT_MAX;
        for (int i = 0; i < nums.size(); ++i) { 
            sum += nums[i];
            while (left <= i && sum >= s) { // sliding window, two pointers
                res = min(res, i - left + 1);
                sum -= nums[left++];
            }
        }
        // return res; // error, nums=[1,1] s=3, return INT_MAX
        return res == INT_MAX ? 0 : res;
    }
};
// 209, Binary Search -- O(nlogn)
// sums(n+1): sums[i]=nums[0:i-1]
// for i=0..n-1: BS to find the right (i+1 < r < n) such that nums[0:r] >= sums[i]+s
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int res = INT_MAX, len = nums.size();
        vector<int> sums(len + 1, 0); // sums[i]=nums[0:i-1]
        for (int i = 1; i <= len; ++i) sums[i] = sums[i - 1] + nums[i - 1];
        for (int i = 0; i < len; ++i) {
            int left = i + 1, right = len;            
            // find the right indx such that sums[left]>=sums[i]+s
            // then, subarray of length=(left - i)
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (sums[mid] >= sums[i] + s) right = mid - 1;
                else left = mid + 1;
            }           
            if (left == len + 1) break;
            res = min(res, left - i);
        }       
        return res == INT_MAX ? 0 : res;
    }
};

// 658. Find K Closest Elements
// O(n)
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res = arr;
        while (res.size() > k) {
            if (abs(res.front() - x) <= abs(res.back() - x)) res.pop_back();
            else res.erase(res.begin());
        }
        return res;
    }
};
// 658. Binary Search, O(logn)
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0, right = arr.size() - k; // "- k"
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (abs(arr[mid] - x) > abs(arr[mid + k] - x)) left = mid + 1;
            else right = mid;
        }
        return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};

// 973. K Closest Points to Origin, sorting -- O(nlogn)
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        auto cmp = [](vector<int> &a, vector<int> &b) {
            // decreasing distance, '<'
            return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1]; 
        };
        sort(points.begin(), points.end(), cmp);
        return vector<vector<int>> (points.begin(), points.begin() + K);
    }
};
// 973. min heap -- O(n)
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        auto cmp = [](vector<int> &a, vector<int> &b) {
            // min heap, '>'
            return a[0] * a[0] + a[1] * a[1] > b[0] * b[0] + b[1] * b[1]; 
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        vector<vector<int>> res;
        for (auto p : points) q.push(p);
        for (int i = 0; i < K; ++i) {
            res.push_back(q.top());
            q.pop();
        }
        return res;
    }
};

// 1283. Find the Smallest Divisor Given a Threshold. Ref. Q875
// Find the smallest divisor such that the result sum is less than or equal to threshold.
// Result of divison is rounded to int greater than or equal to, e.g., 5/2=3.
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int left = 1, right = * max_element(nums.begin(), nums.end()); // #include <algorithm>
        while (left < right) {
            int mid = left + (right - left) / 2;
            int _sum = 0;
            for (auto num : nums) 
                _sum += (num + (mid - 1)) / mid;  // rounded to int greater than or equal to
            if (_sum > threshold) left = mid + 1; // increase divisor if sum larger than threshold
            else right = mid; // 'else right = mid - 1;' for 'while (left <= right)'
        }
        return left;
    }
};
// Facebook, Cutting woods: Given n pieces of woods and an int k
// Find the longest length to cut the woods, such that more or equal to k pieces 
// ref. Q875. Koko Eating Bananas, Binary Search
int cutWoodMaxLen(vector<int> & woods, int k) {
    int left = 1, right = *max_element(woods.begin(), woods.end()); // #include <algorithm>
    while (left < right) {
        int mid = left + (right - left) / 2, cnt = 0;
        for (int wood : woods) {
            cnt += wood / mid; // num of pieces when cutting wood in lenght of mid
        }
		// increasing piece length
        if (cnt > k) left = mid + 1;  // error: if (cnt >= k)
        else right = mid;
    } 
    return right;
}


// 300. Longest Increasing Subsequence (non-contiguous)
// Input: [10,9,2,5,3,7,101,18], Output:4 ([2,3,7,101])
// DP, O(n^2)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1); // LIS ending at pos i
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) // or <= when duplicate num exist
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};
// 300. Binary Search, O(nlogn)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> subs;
        for (int i = 0; i < nums.size(); ++i) {
            int left = 0, right = subs.size();
            // binary search the num in subs larger or equal to nums[i]
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (subs[mid] < nums[i]) left = mid + 1;
                else right = mid;
            }
            // if nums[i] is larger than any num in subs
            if (right == subs.size()) subs.push_back(nums[i]);
            else subs[right] = nums[i];
        }
        return subs.size();
    }
};

// 240. Search a 2D Matrix II
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // must check  matrix[0].empty()
        if (matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size(), n = matrix[0].size(), x = 0, y = n - 1;
        // binary search from the right-up coner
        while (x < m && y >= 0) {
            if (matrix[x][y] == target) return true;
            else if (matrix[x][y] > target) --y;
            else ++x;
        }
        return false;
    }
};

// 162. Find Peak Element
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        // assume nums[-1] = nums[n] = -inf
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[mid + 1]) left = mid + 1;
            else right = mid;
        }
        return left;
    }
};

// 1292. Maximum Side Length of a Square with Sum Less than or Equal to Threshold
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        if (mat.empty() || mat[0].empty()) return 0;
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) 
            for (int j = 1; j <= n; ++j) 
                // dp[0][j]=0, dp[i][0]=0, dp[i][j]=..+mat[i-1][j-1]
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mat[i - 1][j -1];
        // auto sumRegion = [] (int x1, int y1, int x2, int y2, vector<vector<int>> & dp) { //func1
        //     return dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 -1][y1 - 1];
        // };
        auto sumRegion = [&] (int x1, int y1, int x2, int y2) { // '&' to use dp variable
            return dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 -1][y1 - 1];
        };
        
		// // brute force, and bounded search
		// int res = 0;
        // for (int x = 1; x <= m; ++x) {
            // for (int y = 1; y <= n; ++y) {
                // // for (int k = 0; x + k <= m && y + k <= n; ++k) { // brute force, O(m*n * min(m,n))
                // for (int k = res; x + k <= m && y + k <= n; ++k) { // bounded search, O(m*n + min(m,n))
                    // // if (sumRegion(x, y, x + k, y + k, dp) > threshold) break; // to use func1
                    // if (sumRegion(x, y, x + k, y + k) > threshold) break;
                    // res = max(res, k + 1);
                // }
            // }
        // }
		
		// binary search
        int res = 0;
        for (int x = 1; x <= m; ++x) {
            for (int y = 1; y <= n; ++y) {
                int left = 0, right = min(m - x, n - y) + 1;
                while (left < right) {
                    int mid = left + (right - left) / 2;
                    // find smallest left such that > threshold
                    if (sumRegion(x, y, x + mid, y + mid) > threshold) right = mid;
                    else left = mid + 1;
                }
                res = max(res, left);
            }
        }
		
        return res;
    }
};

// 528. Random Pick with Weight
// Binary Search, Random (define)
class Solution {
public:
    Solution(vector<int>& w) {
        // sum[0] = w[0]; // error
        sum = w;
        for (int i = 1; i < w.size(); ++i)
            sum[i] = sum[i - 1] + w[i];
    }
    int pickIndex() {
        // w=[1,3,2], sum=[1,4,6], x=rand()%6=[0,~,5]
        // x=0 -> w1; x=[1,2,3] -> w2; x=[4,5] -> w3
        int x = rand() % sum.back();
        int left = 0, right = sum.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (sum[mid] <= x) left = mid + 1; // error '<', sum is 1-indexed, x is 0-indexed
            else right = mid;
        }
        return left;
    }
private:
    vector<int> sum; // accumulative sum
};

// 497. Random Point in Non-overlapping Rectangles, Random
// Randomly and uniformily picks an integer point in the space covered by the rectangles
class Solution {
public:
    Solution(vector<vector<int>>& rects) {
        _rects = rects;
    }
    // randomly select a rect, then generate random point within the selected rect
    vector<int> pick() {
        vector<int> selected;
        int sumarea = 0;
        // srand(time(0)); // error
        // step 1: select random rect
        for (auto rect : _rects) {
            // num of points covered by rect
            int area = (rect[2] - rect[0] + 1) * (rect[3] - rect[1] + 1);
            sumarea += area;
            if (rand() % sumarea < area) {
                selected = rect;
                // break; // error
            }                
        }
        // step 2: generate point
        int x = rand() % (selected[2] - selected[0] + 1) + selected[0];
        int y = rand() % (selected[3] - selected[1] + 1) + selected[1];
        return {x, y};
    }
private:
    vector<vector<int>> _rects;
};

// 436. Find Right Interval, "right": interval j' start is larger than or equal to i' end
// Input: [ [3,4], [2,3], [1,2] ]; Output: [-1, 0, 1]
class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        vector<int> res, starts;
        unordered_map<int, int> m; // start -- indx
        for (int i = 0; i < intervals.size(); ++i) {
            starts.push_back(intervals[i][0]);
            m[intervals[i][0]] = i;
        }
        // sort decreasing, O(nlogn)
        sort(starts.begin(), starts.end(), greater<int>()); 
        // find the first start larger than or equal to each interval's end
        for (auto interval : intervals) {
            // brute force, O(n)
            // int i = 0; 
            // for (; i < starts.size(); ++i)
            //    if (starts[i] < interval[1]) break; // first less than
            // res.push_back((i > 0) ? m[starts[i - 1]] : -1); // indx 'i - 1'
            
            // binary search, O(logn)
            int indx = -1, left = 0, right = starts.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (starts[mid] == interval[1]) { // found same start as interval's end
                    indx = mid; break;
                }
                else if (interval[1] < starts[mid]) { // found start larger than interval's end
                    indx = mid;
                    left = mid + 1; // error, left = mid
                }
                else {
                    right = mid - 1;
                }
            }
            res.push_back(indx == -1 ? -1 : m[starts[indx]]);
            
        }
        return res;
    }
};

// 1300. Sum of Mutated Array Closest to Target
// Find the value such that changing all larger integers to the value
// the sum gets as close as possible to the target
class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        // // n * log(M), M=max(arr)
        int left = 0, right = * max_element(arr.begin(), arr.end()); // #include <algorithm>
        while (left < right) {
            int mid = left + (right - left) / 2;
            // sum less than target, increase the value
            if (sum(arr, mid) < target) 
                left = mid + 1;
            else right = mid;
        }
        // '<=': In case of a tie, return the minimum such integer.
        if (abs(sum(arr, left - 1) - target) <= abs(sum(arr, left) - target))
            return left - 1;
        return left;
    }
    int sum (vector<int>& arr, int val) {
        int sum = 0;
        for (int x : arr) 
            sum += min(x, val);
        return sum;
    }
};

// 875. Koko Eating Bananas
// Fing minimum integer K such that she can eat all the bananas within H hours.
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int H) {
        int left = 1, right = *max_element(piles.begin(), piles.end()); // 1 <= piles[i] <= 10^9
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

// 378. Kth Smallest Element in a Sorted Matrix
// The end element of row-(i-1) may not be less than the start element of row-i
// matrix = [[1,5,9], [10,11,13], [12,13,15]], k = 8; return 13.
// max-heap, O(m*n)
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int> q; // max-heap
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                q.push(matrix[i][j]);
                if (q.size() > k) q.pop(); // remove element after kth larger value
            }
        }
        return q.top();
    }
};
// Binary Search, O(nlgn*lgX), X=maxval-minval
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int left = matrix[0][0], right = matrix.back().back();
        while (left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for (int i = 0; i < matrix.size(); ++i)
                // since end of row-(i-1) may not be less than start of row-i
                // num of elements less than mid in each row
                cnt += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
            if (cnt < k) left = mid + 1;
            else right = mid;
        }
        return left;
    }
};

// 215. Kth Largest Element in an Array, Divide and Conquer
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

// 981. Time Based Key-Value Store
// set(string key, string value, int timestamp)
// get(string key, int timestamp)
class TimeMap {
public:
    /** Initialize your data structure here. */
    TimeMap() {
    }    
    void set(string key, string value, int timestamp) {
        m[key].emplace_back(timestamp, value);
    }
    string get(string key, int timestamp) {
        if (m.find(key) == m.end()) return ""; // not exist
        if (m[key][0].first > timestamp) return ""; // all timestamp_prev > timestamp
        // binary search
        int left = 0, right = m[key].size() - 1;
        while (left < right - 1) {
            int mid = left + (right - left) / 2;
            if (m[key][mid].first > timestamp) right = mid - 1;
            else left = mid;
        }
        if (m[key][right].first <= timestamp) return m[key][right].second;
        return m[key][left].second;
    }
private:
    // key-[time, val], time sorted increasing
    map<string, vector<pair<int, string>>> m; 
};

// 1182. Shortest Distance to Target Color
// return the shortest distance between the given index i and the target color c
// Input: colors = [1,1,2,1,3,2,2,3,3], queries[pos,color] = [[1,3],[2,2],[6,1]]; Output: [3,0,3]
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        vector<int> res;
        unordered_map<int, vector<int>> m; // color-positions
        for (int i = 0; i < colors.size(); ++i)
            m[colors[i]].push_back(i);
        for (auto query : queries) {
            if (!m.count(query[1])) { // color not exist
                res.push_back(-1); continue;
            }
            int pos = closest(m[query[1]], query[0]); // pos of color(query[1]) closest to query[0]
            res.push_back(abs(pos - query[0])); // distance
        }
        return res;
    }
    int closest (vector<int> & nums, int target) {
        // lower_bound: an iterator pointing the first element not less than ‘val’
        // upper_bound: an iterator pointing the first element greater than ‘val’
        // nums=[5,5,5,6,6,6,7,7], target=6; lowerpos=3, upperpos=6
        int pos = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        if (pos == 0) return nums[0];
        if (pos == nums.size()) return nums[nums.size() - 1];
        // nums=[4,7,8], target=5, nums[pos]=7, comp(abs(4-5) and abs(7-5))
        if (abs(nums[pos] - target) < abs(nums[pos - 1] - target))
            return nums[pos];
        return nums[pos - 1];
    }
};

// Facebook, unique number in unsorted array, O(n)
// Input:  ar[] = {7, 3, 5, 4, 5, 3, 4}; Output: 7 
int uniqueNum (vector<int> & nums) {
	if (nums.size() == 0) return -1;
	// Do XOR of all elements
	// return the single occurrence
	int res = nums[0];
	for (int i = 1; i < nums.size(); ++i)
		res ^= nums[i];
	return res;
}
// Unique number in sorted array, O(logn)
// elements before unique num: first occurrence at even index (0,2,..), next at (1,3..)
// Input: arr[] = {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8}; Output:  4
int uniqueNum (vector<int> & nums) {
	if (nums.size() == 0) return -1;	
    int n = nums.size(), left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;       
        // If mid is even and element next to mid is 
        // same as mid, then output element lies on 
        // right side, else on left side 
        if (mid % 2 == 0) { // even pos
            if (mid + 1 < n && nums[mid] ==  nums[mid + 1]) left = mid + 2;
            else right = mid - 2;
        }
        else {
            if (mid - 1 >= 0 && nums[mid] == nums[mid - 1]) left = mid + 1;
            else right = mid - 1;
        }
    }
    return nums[right];
}

// 287. Find the Duplicate Number, O(nlogn)
// nums contains n+1 integers between 1 and n (inclusive). Input: [3,1,3,4,2]; Output: 3
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int left = 1, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for (int num : nums)
                if (num <= mid) ++cnt;
            if (cnt <= mid) left = mid + 1;
            else right = mid;
        }
        return right;
    }
};

// Find the only missing num in sorted array (1 to n with one missing)
// elements before the missing element: nums[i]=i+1; elements after:nums[i]=i+2
// Input: [1, 2, 3, 4, 6, 7, 8]; Output: 5
int missingNum(vector<int> & nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] != mid + 1) { // nums[i]!=i+1
			// the first element that nums[i]!=i+1, that's the missing one
            if (nums[mid - 1] == mid) return mid + 1; 
            else right = mid; // search left part
        }
        else left = mid + 1;
    }
    return -1;
}
// 1060. k-th Missing Element in Sorted Array
// Input: A = [4,7,9,10], K = 3; Output: 8
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        int cnt = missingCount(nums, right);
        // k-th missing num is not within nums[0] and nums[right]
        if (k > cnt) return nums[right] + k - cnt; 
        // the index of the leftmost lower-bound of K
        while (left < right) {
            int mid = left + (right - left) / 2;
            cnt = missingCount(nums, mid);
            if (k > cnt) left = mid + 1;
            else right = mid;
        }
        // the number of missing at index - 1 must less then K
        return nums[left - 1] + k - missingCount(nums, left - 1);
    }
    int missingCount(vector<int> & nums, int indx) {
        return nums[indx] - nums[0] - indx;
    }
};

// 1198. Find Smallest Common Element in All Rows
// Input: mat = [[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]; Output: 5
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

// 287. Find the Duplicate Number, array range [1, n]; Input: nums = [3,1,3,4,2]; Output: 3
// Binary Search: O(NlogN), not modifying the array
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int left = 1, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for (int num : nums) {
                if (num <= mid) ++cnt;
            }
            if (cnt <= mid) left = mid + 1;
            else right = mid;
        }
        return right;
    }
};

// 1539. Kth Missing Positive Number, sorted in a strictly increasing order
// Input: arr = [2,3,4,7,11], k = 5; Output: 9
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int left = 0, right = arr.size();
        while (left < right) { // the smallest index l s.t. arr[l] – l + 1 >= k
            int mid = left + (right - left) / 2;
            if (arr[mid] - (mid + 1) >= k) right = mid;
            else left = mid + 1;
        }
        return left + k;
    }
};