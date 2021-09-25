//########################### 1. sliding window #################################//
// 340. Longest Substring with At Most K Distinct Characters
	// 159. Longest Substring with At Most Two Distinct Characters 
	// 904. Fruit Into Two Baskets
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> m; 
        int res = 0, left = 0;
        for (int i = 0; i < s.size(); ++i) {
            ++m[s[i]];
            while (m.size() > k) { // shrink window from left side
                if (--m[s[left]] == 0) m.erase(s[left]);
                ++left;
            }
            res = max(res, i - left + 1);
        }
        return res;
    }
};
// 3. Longest Substring Without Repeating Characters
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> m;
        int res = 0, left = 0;
        for (int i = 0; i < s.size(); ++i) {
            ++m[s[i]];
            while (m[s[i]] > 1) {
                if (--m[s[left]] == 0) m.erase(s[left]);
                ++left;
            }
            res = max(res, i - left + 1);
        }
        return res;
    }
};
// 424. Longest Repeating Character after at most K Replacement
class Solution {
public:
    int characterReplacement(string s, int k) {
        // unordered_map<char, int> m;   // method 1
        vector<int> m(26, 0);           // method 2
        int res = 0, left = 0, maxCnt = 0;
        for (int i = 0; i < s.size(); ++i) {
            // max occurrence in sliding window
            // maxCnt = max(maxCnt, ++m[s[i]]); 
            maxCnt = max(maxCnt, ++m[s[i] - 'A']);
            while (i - left + 1 - maxCnt > k) { // at most K changes
                // if (--m[s[left]] == 0) m.erase(s[left]);
                --m[s[left] - 'A'];
                ++left;
            }
            res = max(res, i - left + 1);
        }
        return res;
    }
};
// 1004. Max Consecutive Ones III
class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        vector<int> m(2, 0);
        int res = 0, left = 0, maxOneCnt = 0;
        for (int i = 0; i < A.size(); ++i) {
            ++m[A[i]];
            maxOneCnt = A[i] == 1 ? maxOneCnt + 1 : maxOneCnt;
            while (i - left + 1 - maxOneCnt > K) {
                maxOneCnt = A[left] == 1 ? maxOneCnt - 1 : maxOneCnt;
                --m[A[left]];
                ++left;
            }
            res = max(res, i - left + 1);
        }
        return res;
    }
};
// 567. Permutation in String
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        const int n1 = s1.size(), n2 = s2.size();
        if (n1 > n2) return false;
        
        vector<int> m1(128, 0), m2(128, 0); // not 26, lowercase/uppercase

        for (int i = 0; i < n1; ++i) {
            ++m1[s1[i]]; ++m2[s2[i]];
        }
        if (m1 == m2) return true;
        for (int i = n1; i < n2; ++i) {
            --m2[s2[i - n1]];
            ++m2[s2[i]];
            if (m1 == m2) return true;
        }
        return false;
    }
};
// 438. Find All Anagrams in a String
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        const int ns = s.size(), np = p.size();
        if (ns < np) return {};
        
        vector<int> res, ms(128, 0), mp(128, 0);

        for (int i = 0; i < np; ++i) {
            ++ms[s[i]]; ++mp[p[i]];
        }
        if (ms == mp) res.push_back(0);
        for (int i = np; i < ns; ++i) {
            --ms[s[i - np]];
            ++ms[s[i]];
            if (ms == mp) res.push_back(i - np + 1);
        }
        return res;
    }
};
// 76. Minimum Window Substring
class Solution {
public:
    string minWindow(string s, string t) {
        int cnt = 0, minlen = INT_MAX, minleft = -1;
        vector<int> m (128, 0);
        for (auto a : t) ++m[a];
        for (int winstart = 0, i = 0; i < s.size(); ++i) {
            if (--m[s[i]] >= 0) ++cnt; // s[i] in t
            while (cnt == t.size()) {
                if (minlen > i - winstart + 1) {
                    minlen = i - winstart + 1;
                    minleft = winstart;
                }
                if (++m[s[winstart]] > 0) --cnt;  // remove s[winstart] that is in t
                ++winstart;
            }
        }
        return minleft == -1 ? "" : s.substr(minleft, minlen);
    }
};
// 30. index of Substring with Concatenation of All Words
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if (s.empty() || words.empty()) return {};
        vector<int> res;
        int cnt = words.size(), len = words[0].size();
        unordered_map<string, int> wordCnt;
        for (auto w : words) ++wordCnt[w];
		// must be '<='; and (int): s="a",words=["a","a"]
        for (int i = 0; i <= (int)s.size() - cnt * len; ++i) { 
            unordered_map<string, int> strCnt;
            for (int j = 0; j < cnt; ++j) {
                string word = s.substr(i + j * len, len);
                if (!wordCnt.count(word)) break;  // word not in words
                ++strCnt[word];
                if (strCnt[word] > wordCnt[word]) break;  // word already checked
                
                if (j == cnt - 1) res.push_back(i); // store indx after finding all words
            }
        }
        return res;
    }
};

//########################### 2. two pointers #################################//
// 1. Two Sum (unsorted array)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;  // complement--index
        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];
            if (m.count(complement)) 
                return {i, m[complement]};
            m[nums[i]] = i;
        }
        return {};
    }
};
// 只要是两数之和的题，一定要记得先尝试用HashSet来做
// 653. Two Sum IV - Input is a BST
	// method 2: BST inorder traversal, then two sum in sorted array
	// method 3: level order traversal, complement hashet
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> st;
        return helper(root, k, st);
    }
    bool helper(TreeNode * node, int k, unordered_set<int> & st) {
        if (!node) return false;
        if (st.count(k - node->val)) return true;
        st.insert(node->val);
        return helper(node->left, k, st) || helper(node->right, k, st);
    }
};
// 15. 3Sum, Find all unique triplets: a+b+c=0
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        // a+b+c=0: a,b,c all zeros, or have both positve and negative
        if (nums.empty() || nums.front() > 0 || nums.back() < 0) return {};
        vector<vector<int>> res;
		// set<vector<int>> res;  // method 2: TreeSet to not hold duplicate triplets
        for (int i = 0; i < (int)nums.size() - 2; ++i) { // fix one num, '-2' for three nums
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i - 1]) continue; // skip duplicate triplets
            int left = i + 1, right = (int)nums.size() - 1;
            while (left < right) { // two sum for sorted array
                int target = 0 - nums[i];
                if (nums[left] + nums[right] == target) {
                    res.push_back({nums[i], nums[left], nums[right]});
					// res.insert({nums[i], nums[left], nums[right]});  // method 2
                    // skip duplicate triplets
                    while (left < right && nums[left] == nums[left + 1]) ++left;
                    while (left < right && nums[right] == nums[right - 1]) --right;
                    ++left; --right;  // not forget
                }
                else if (nums[left] + nums[right] < target) ++left;
                else --right;
            }
        }
        return res;
		// return vector<vector<int>> (res.begin(), res.end());  // method 2
    }
};
// 16. 3Sum Closest
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), res = 0, minDiff = INT_MAX;
        for (int i = 0; i < n - 2; ++i) {  // 'n - 2'
            int left = i + 1, right = n - 1;
            while (left < right) {
                int cursum = nums[i] + nums[left] + nums[right];
                int curdiff = abs(target - cursum);
                if (curdiff < minDiff) {
                    res = cursum;
                    minDiff = curdiff;
                }
                if (cursum < target) ++left;
                else --right;
            }
        }
        return res;
    }
};
// 18. 4Sum
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> res;
        for (int i = 0; i < n - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;  // j > i+1
                int left = j + 1, right = n - 1;
                while (left < right) {
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum == target) {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left + 1] == nums[left]) ++left;
                        while (left < right && nums[right - 1] == nums[right]) --right;
                        ++left; --right;
                    }
                    else if (sum < target) ++left;
                    else --right;
                }
            }
        }
        return res;
    }
};
// 259. 3Sum smaller
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), res = 0;
        for (int i = 0; i < n - 2; ++i) { // n - 2
            int left = i + 1, right = n - 1;
            while (left < right) {
                int cursum = nums[i] + nums[left] + nums[right];
                if (cursum < target) {
                    res += right - left; // not: res += 1;
                    ++left;
                }
                else --right;
            }
        }
        return res;
    }
};

// 713. Subarray Product Less Than K
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int res = 0, left = 0, subproduct = 1; // subwindow of product < k
        for (int i = 0; i < (int)nums.size(); ++i) {
            subproduct *= nums[i];
            while (left <= i && subproduc >= k) {
                subproduc /= nums[left++]; // move subwindow to right
            }
            res += i - left + 1; // subwindow length: [5,2,6] => [6],[2,6],[5,2,6]
        }
    }
};

// 26. Remove Duplicates from Sorted Array
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int pre = 0, cur = 0, n = nums.size();
        while (cur < n) {
            if (nums[cur] == nums[pre]) ++cur;
            else nums[++pre] = nums[cur++];
        }
        return pre + 1;
    }
};
// 80. Remove Duplicates from Sorted Array II
// such that duplicates appeared at most twice 
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int pre = 0, cur = 1, n = nums.size();
        bool flag = false;
        while (cur < n) {
            if (nums[pre] == nums[cur]) {
                if (!flag)  { // first time repeating
                    flag = true;
                    nums[++pre] = nums[cur++];
                }
                else ++cur; // repeat more than twice
            }
            else {
                flag = false;
                nums[++pre] = nums[cur++];
            }
        }
        return pre + 1;
    }
};

// 75. Sort Colors, one-pass algorithm, 0's, 1's, 2's
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, right = nums.size() - 1, cur = 0;
        while (cur <= right) { // cur, <=
            if (nums[cur] == 0) 
                swap(nums[left++], nums[cur++]);
            else if (nums[cur] == 2)
				// high-- only, the number at 'i' after the smap can be 0, 1, or 2
                swap(nums[right--], nums[cur]); // not cur++
            else
                ++cur;
        }
    }
};

// 581. Shortest Unsorted Continuous Subarray
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size(), left = 0, right = n - 1;
        // find unsorted subarray
        while (left < n - 1 && nums[left] <= nums[left + 1]) ++left; // n - 1, <=
        if (left == n - 1) return 0;
        while (right >= 0 && nums[right] >= nums[right - 1]) --right; // >=
        int minsub = INT_MAX, maxsub = INT_MIN;
        for (int i = left; i <= right; ++i) {
            minsub = min(minsub, nums[i]);
            maxsub = max(maxsub, nums[i]);
        }
        
        // extent unsorted subarray
        while (left > 0 && nums[left - 1] > minsub) --left;
        while (right < n - 1 && nums[right + 1] < maxsub ) ++right;
        
        return right - left + 1;
    }
};
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> t = nums;
        sort(t.begin(), t.end());
        int n = nums.size(), i = 0, j = n - 1;
        while (i < n && t[i] == nums[i]) ++i;
        while (j > i && t[j] == nums[j]) --j;  // >i, not >=0
        return j - i + 1;
    }
};

//########################### 3. slow fast pointer #################################//
// 141. Linked List Cycle
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode * slow = head;
        ListNode * fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};
// 142. Linked List Cycle II, start point
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode * slow = head;
        ListNode * fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }
        // no cycle
        if (!fast || !fast->next) return NULL;
        // 2*(a+b) = a+b+c+d => a = c
        slow = head;
        while (slow != fast) { // a = c
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};

// 263. Ugly Number
class Solution {
public:
    bool isUgly(int num) {
        while (num >= 2) {
            if (num % 2 == 0) num /= 2;
            else if (num % 3 == 0) num /= 3;
            else if (num % 5 == 0) num /= 5;
            else return false;
        }
        return num == 1;
    }
};
// 264. Ugly Number II, nth ugly
class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue<long, vector<long>, greater<long>> q; // min queue
        q.push(1);
        for (int i = 1; i < n; ++i) {
            long t = q.top(); q.pop();
            while (!q.empty() && t == q.top()) q.pop(); // removde duplicates
            q.push(t * 2);
            q.push(t * 3);
            q.push(t * 5);
        }
        return q.top();
    }
};

// 876. Middle of the Linked List
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode * slow = head;
        ListNode * fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};
// 234. Palindrome Linked List
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        ListNode * slow = head, * fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode * newhead = reverseList(slow); // reverse second half
        while (head && newhead) {
            if (head->val != newhead->val) return false;
            head =  head->next;
            newhead = newhead->next;
        }
        return true;
    }
    ListNode * reverseList(ListNode * head) {
        ListNode * newhead = NULL;
        while (head) {
            ListNode * tmp = head->next;
            head->next = newhead;
            newhead = head;
            head = tmp;
        }
        return newhead;
    }
};
// 143. Reorder List
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return;
        ListNode * slow = head, * fast = head;
        while (fast && fast->next) { // second half
            slow = slow->next;
            fast = fast->next->next; // ->next->next
        }
        ListNode * firsthalf = head;
        ListNode * secondhalf = reverseList(slow); // reverse linkedlist
        while (firsthalf && secondhalf) {
            ListNode * tmp = firsthalf->next;
            firsthalf->next = secondhalf;
            secondhalf = secondhalf->next;
            firsthalf->next->next = tmp;  // link newnode to oldlist
            firsthalf = tmp;                 // move head to oldhead->next
        }
        if (firsthalf) // set last node's next to NULL
            firsthalf->next = NULL;
    }
    
    ListNode * reverseList(ListNode * head) {
        ListNode * newhead = NULL;
        while (head) {
            ListNode * tmp = head->next;
            head->next = newhead;
            newhead = head;
            head = tmp;
        }
        return newhead;
    }
};

// 457. Circular Array Loop
class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        vector<bool> visited(n);
        for (int i = 0; i < n; ++i) {
            if (visited[i]) continue;
            visited[i] = true;
            
            int cur = i; 
            unordered_map<int, int> m; // cur-next
            while (true) {
                int next = ((cur + nums[cur]) % n + n) % n; // %n, %n: nums[cur] large negative
                if (next == cur || nums[next] * nums[cur] < 0) break;
                if (m.count(next)) return true;
                m[cur] = next;
                cur = next;
                visited[next] = true;
            }
        }
        return false;
    }
};


//########################### 4. merge intervals #################################//
// 56. Merge Intervals
	// 252. Meeting Rooms, if attend all meetings
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res{intervals[0]};
        for (int i = 1; i < (int)intervals.size(); ++i) {
            if (res.back()[1] < intervals[i][0]) res.push_back(intervals[i]);
            else res.back()[1] = max(res.back()[1], intervals[i][1]);
        }
        return res;
    }
};
// 57. Insert Interval
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        int n = intervals.size(), cur = 0;
        while (cur < n && intervals[cur][1] < newInterval[0]) { // no-overlapping
            res.push_back(intervals[cur]); 
            ++cur;
        }
        while (cur < n && intervals[cur][0] <= newInterval[1]) { // merge
            newInterval[0] = min(intervals[cur][0], newInterval[0]);
            newInterval[1] = max(intervals[cur][1], newInterval[1]);
            ++cur;
        }
        res.push_back(newInterval);
        while (cur < n) res.push_back(intervals[cur++]);
        return res;
    }
};
// 986. Interval List Intersections
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> res;
        int n = A.size(), m = B.size(), i = 0, j = 0;
        while (i < n && j < m) {
            if (A[i][1] < B[j][0]) ++i; // no-overlapping, A[i] < B[j]
            else if (B[j][1] < A[i][0]) ++j;
            else {  // overlapping
                res.push_back({{max(A[i][0], B[j][0]), min(A[i][1], B[j][1])}});
                if (A[i][1] < B[j][1]) ++i;
                else ++j;
            }
        }
        return res;
    }
};
// 253. Meeting Rooms II; minimum meeting rooms
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end()); // inscending in start time
        priority_queue<int, vector<int>, greater<int>> q; // min queue: end time, first finishing meeting
        for (auto interval : intervals) {
            // room can be reused if previous meeting is done
            if (!q.empty() && q.top() <= interval[0]) q.pop();  // >=
            q.push(interval[1]);
        }
        return q.size();
    }
};
// Find maximum meetings in one room.
	// ref: Q1353. Maximum Number of Events That Can Be Attended
	// 759. Employee Free Time
int maxMeetingRooms(vector<vector<int>> & meetings) {
    if (meetings.size() == 0) return -1;   
    auto cmp = [] (vector<int> & a, vector<int> & b) {
        return a[1] < b[1]; // sort increasing by end time  
    };
    sort(meetings.begin(), meetings.end(), cmp);
	int res = 1;
    int endtime = meetings[0][1];    
    for (int i = 1; i < meetings.size(); ++i) {
        if (meetings[i][0] >= endtime) {
			++res;
			endtime = meetings[i][1];
        }
    }    
	return res;
}
// ref: Q1353. Maximum Number of Events That Can Be Attended
// Time Limit Exceeded: [[1,1],[1,2],[1,3],[1,4],...[1,100000]]
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        auto cmp = [](vector<int> &a, vector<int> &b) {
            return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);    
        };
        sort(events.begin(), events.end(), cmp); // sort inscending by end time
        
        int res = 0, n = events.size();
        vector<bool> attend(events[n - 1][1] + 1, false); 
		// to solve Time Limit Exceeded
        // int prev = 0;  
        for (int i = 0; i < n; ++i) {
        // can attend the event at any dey within [start, end] day
            int start = events[i][0], end = events[i][1];
            // to solve Time Limit Exceeded
			// if (i > 0 && events[i][0] == events[i - 1][0]) start = prev; 
			for (int j = start; j <= end; ++j) {
                if (attend[j]) continue; // already attend other event at day_i 
                attend[j] = true;
                ++res; 
                // prev = j; // to solve Time Limit Exceeded
                break;  // attend this event at day_i
            }
        }
        return res;
    }
};
// 1094. Car Pooling, trip[i] = [num_passengers, start_location, end_location]
	// ref: Q253, minimum meeting rooms
	// similar: Maximum CPU load
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        auto startCmp = [](vector<int> &a, vector<int> &b) {
           return a[1] < b[1] || (a[1] == b[1] && a[2] < b[2]); 
        };
        sort(trips.begin(), trips.end(), startCmp);
        
        auto endCmp = [](vector<int> &a, vector<int> &b) {
            return a[2] > b[2];  // descending in endtime: min queue
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(endCmp)> q(endCmp); //q(endCmp)
        
        int curload = 0, maxload = 0;
        for (auto trip : trips) {
            // remove all trips that have droped off
            while (!q.empty() && q.top()[2] <= trip[1]) {
                curload -= q.top()[0];
                q.pop();
            }
            
            // add cur trip (passengers) onto vehicle
            q.push(trip);
            curload += trip[0];
            maxload = max(maxload, curload);
            
            // check if overloading
            if (maxload > capacity) return false;
        }
        
        return true;
    }
};

// 759. Employee Free Time
// Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]; Output: [[5,6],[7,9]]
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        if (schedule.empty()) return {};
        
        vector<Interval> all, res;
        for (auto s : schedule) {
			all.insert(all.end(), s.begin(), s.end());
		}
        sort(all.begin(), all.end(), [](Interval &a, Interval &b){return a.start < b.start;});
        
        int maxend = all[0].end;
        for (int i = 1; i < (int)all.size(); ++i) {
            if (all[i].start > maxend) { // maxend
                res.push_back({maxend, all[i].start}); // maxend
            }
            maxend = max(maxend, all[i].end);
        }
        return res;
    }
};


//########################### 5. cyclic sort #################################//
// 268. Find the Missing Number; Input: [9,6,4,2,3,5,7,0,1]; Output: 8
//class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int i = 0, n = nums.size();
        while (i < n) { // cyclic sort
            if (nums[i] < n && nums[i] != nums[nums[i]])
                swap(nums[i], nums[nums[i]]);
            else ++i;
        }
        for (int i = 0; i < n; ++i) 
            if (nums[i] != i)
                return i;
        return nums.size();
    }
};
// 448. Find All Missing Numbers in an Array, 1 ≤ a[i] ≤ n
// Input: [4,3,2,7,8,2,3,1]; Output: [5,6]
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> res;
        int n = nums.size(), i = 0;
        while (i < n) { // cyclic sort:[1,2,3,4,3,2,7,8]
            if (nums[i] - 1 < n && nums[i] != nums[nums[i] - 1]) //
                swap(nums[i], nums[nums[i] - 1]);
            else ++i;
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1)
                res.push_back(i+1);
        }
        return res;
    }
};

// 287. Find the Duplicate Number, array range [1, n]; Input: nums = [3,1,3,4,2]; Output: 3
// sort -> find: O(NlogN), modifying the array
// cyclic sort: O(N), modifying the array
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int i = 0, n = nums.size();
        while (i < n) { // cyclic sort
            if (nums[i] != i + 1) {
                if (nums[i] != nums[nums[i] - 1])
                    swap(nums[i], nums[nums[i] - 1]);
                else return nums[i];
            }
            else ++i;
        }
        return -1;
    }
};
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
// 442. Find All Duplicates in an Array 1 ≤ a[i] ≤ n, some elements appear twice 
// Input: [4,3,2,7,8,2,3,1]; -cyclic sort:[1,2,3,4,3,2,7,8]--> Output: [2,3]
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        int i = 0, n = nums.size();
        while (i < n) { // cyclic sort
            if (nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
            else {
                ++i;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1)
                res.push_back(nums[i]);
        }
        return res;
    }
};

// 41. First Missing Positive; Input: [3,4,-1,1]; Output: 2
// O(N) time, O(1) space
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int i = 0, n = nums.size();
        while (i < n) { // cyclic sort, 0<nums[i]<=n
            if (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
            else ++i;
        }
        for (int i = 0; i < n; ++i)
            if (nums[i] != i + 1)
                return i + 1;
        return n + 1;
    }
};
// Find the First K missing positive numvers
// Input: [3, -1, 4, 5, 5], k = 3; Output: [1, 2, 6]
class Solution {
public:
    int firstKMissingPositive(vector<int>& nums, k) {
        int i = 0, n = nums.size();
        while (i < n) { // cyclic sort, 0<nums[i]<=n
            if (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
            else ++i;
        }
		vector<int> res;
		unordered_set<int> largeNum; // nums[i] != i + 1
		for (int i = 0; i < n && res.size() < k; ++i) {
			if (nums[i] != i + 1) {
				res.push_back(i + 1);
				largeNum.insert(nums[i]); // numbers larger than nums.size()
			}
		}
		// add the remaining missing numbers
		for (int i = 1; res.size() < k; ++i) {
			if (!largeNum.count(nums.size() + i))
				res.push_back(nums.size() + i);
		}
		return res;
    }
};

// 1539. Kth Missing Positive Number, sorted in a strictly increasing order
// Time: O(max(arr)) ~ O(1000); Space: O(n)
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        unordered_set<int> s(arr.begin(), arr.end());
        for (int i = 1; i <= (int)arr.back(); ++i) {
            if (!s.count(i)) --k;
            if (k == 0) return i;
        }
        return arr.back() + k;
    }
};
// Binary search: Time: O(logn); Space: O(1)
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

//########################### 6. Reverse a linked list in place #################################//
// 206. Reverse Linked List
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode * newhead = NULL;
        while (head) {
            ListNode * next = head->next;
            head->next = newhead;
            newhead = head;
            head = next;
        }
        return newhead;
    }
};
// 92. Reverse Linked List II, sublist: 1 ≤ m ≤ n ≤ length of list.
// https://www.youtube.com/watch?v=wk8-_M-2fzI
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        // dummy node for pre alwasy exist in case m=1
        ListNode * dummy = new ListNode(-1, head), * pre = dummy; 
        for (int i = 1; i < m; ++i) pre = pre->next;
        ListNode * cur = pre->next;
        for (int i = m; i < n; ++i) {
            ListNode * next = cur->next;
            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }
        return dummy->next;
    }
};
// 25. Reverse Nodes in k-Group, reverse every k-element sublist, 
// left-out nodes in the end (less than K) should remain as it is.
// Input: 1->2->3->4->5, k=3; Output: 3->2->1->4->5
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode * dummy = new ListNode(-1, head), * pre = dummy, * cur = dummy;
        int num = 0;
        while (cur->next) {cur = cur->next; ++num;}  // node#
        while (num >= k) { // less than k left-out node remain the same order
            cur = pre->next;
            for (int i = 1; i < k; ++i) {
                ListNode * next = cur->next;
                cur->next = next->next;
                next->next = pre->next;
                pre->next = next;
            }
            pre = cur; // move to next k-group
            num -= k;
        }
        return dummy->next;
    }
};
// 24. Swap Nodes in Pairs, Input: 1->2->3->4->5, Output: 2->1->4->3->5.
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode * dummy = new ListNode(-1, head), * pre = dummy, * cur = pre->next;
        while (cur && cur->next) {
            ListNode * next = cur->next;
            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
            pre = cur;
            cur = cur->next;
        }
        return dummy->next;
    }
};
// 61. Rotate List to the right by k places
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return NULL;
        int n = 1;
        ListNode * cur = head;
        while (cur->next) { // get node num and the last node
            cur = cur->next;
            ++n;
        }
        cur->next = head;  // construct circular list
        int m = n - k % n;        // no rotation for more than n
        for (int i = 0; i < m; ++i) 
            cur = cur->next;
        // cut off circular list
        ListNode * newhead = cur->next;
        cur->next = NULL;
        return newhead;
    }
};

// 189. Rotate Array, space O(N)
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int> t = nums;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            nums[(i + k) % n] = t[i];
        }
    }
};
// space O(1)
class Solution {
public:
    void rotate(vector<int>& nums, int k) { 
        if (nums.empty() || (k %= nums.size()) == 0) return;
        int n = nums.size();                        // 1 2 3 4 5 6 7
        reverse(nums.begin(), nums.begin() + n - k); // rotate first k: 4 3 2 1 5 6 7
        reverse(nums.begin() + n - k, nums.end());  // rotate remaing n-k: 4 3 2 1 7 6 5
        reverse(nums.begin(), nums.end());          // rotate whole array: 5 6 7 1 2 3 4
    }
};

//########################### 7. Tree BFS #################################//
// 102. Binary Tree Level Order Traversal
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {}; // must
        vector<vector<int>> res;
        queue<TreeNode*> q{{root}};
        while (!q.empty()) {
            vector<int> onelevel;
            for (int i = q.size(); i > 0; --i) {
                TreeNode * t = q.front(); q.pop();
                onelevel.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            res.push_back(onelevel);
			// res.insert(res.begin(), onelevel); // 107. levelOrderBottomUp
        }
        return res;
    }
};
// 103. Binary Tree Zigzag Level Order Traversal
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> res;
        queue<TreeNode *> q {{root}};
        int level = 1;
        while (!q.empty()) {
            vector<int> onelevel;
            for (int i = q.size(); i > 0; --i) {
                TreeNode * t = q.front(); q.pop();
                onelevel.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            if (level % 2 == 0) reverse(onelevel.begin(), onelevel.end());
            res.push_back(onelevel);
            ++level;
        }
        return res;
    }
};
// Level order successor
class Solution {
public:
	TreeNode* levelOrderSeccessor(TreeNode * root, int key){
		if (!root) return NULL;
		queue<TreeNode*> q{{root}};
		while (!q.empty()){
			TreeNode * t = q.front(); q.pop();
			if (t->left) q.push(t->left);
			if (t->right) q.push(t->right);
			if (t->val == key) break;
		}
		return q.front();
	}
};
// 111. Minimum Depth of Binary Tree
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode *> q{{root}};
        int res = 0;
        while (!q.empty()) {
            ++res;
            for (int i = q.size(); i > 0; --i) {
                TreeNode * t = q.front(); q.pop();
                if (!t->left && !t->right) return res;  // minimum depth
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return -1; // return res; // maximum depth
    }
};
// 116. Connect each node with its level order successor
class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return NULL;
        queue<Node*> q{{root}};
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                Node * t = q.front(); q.pop();
                if (i == 1) t->next = NULL;
                else t->next = q.front();
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return root;
    }
};
// 199. Binary Tree Right Side View
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return {};
        vector<int> res;
        queue<TreeNode*> q{{root}};
        while (!q.empty()) {
            vector<int> onelevel;
            for (int i = q.size(); i > 0; --i) {
                TreeNode * cur = q.front(); q.pop();
                onelevel.push_back(cur->val);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            res.push_back(onelevel.back());
        }
        return res;
    }
};
// 993. Cousins in Binary Tree: same level, diff parents
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        if (!root || (!root->left && !root->right)) return false;
        queue<TreeNode *> q{{root}};
        while (!q.empty()) {
            bool foundFirst = false;
            for (int i = q.size(); i > 0; --i) {
                TreeNode * cur = q.front(); q.pop();
                
                if (cur->left && (cur->left->val == x || cur->left->val == y)) {
                    if (!foundFirst) foundFirst = true;
                    else return true;
                }
                else if (cur->right && (cur->right->val == x || cur->right->val == y)) {
                    if (!foundFirst) foundFirst = true;
                    else return true;
                }
                
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
        }
        return false;
    }
};
// 545. Boundary of Binary Tree
class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        if (!root) return {};
        vector<int> res, leftview, rightview, leaves;
        queue<TreeNode *> q{{root}};
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                TreeNode * cur = q.front(); q.pop();
                
                if (!cur->left && !cur->right) continue; // skip leaf nodes
                else if (i == 0) leftview.push_back(cur->val);
                else if (i == n - 1) rightview.insert(rightview.begin(), cur->val);
                
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
        }
        
        findLeaves(root, leaves);
        res.insert(res.end(), leftview.begin(), leftview.end());
        res.insert(res.end(), leaves.begin(), leaves.end());
        res.insert(res.end(), rightview.begin(), rightview.end());
        
        return res;
    }
    
    void findLeaves (TreeNode * node, vector<int> & res) {
        if (!node) return;
        if (!node->left && !node->right) res.push_back(node->val);
        findLeaves(node->left, res);
        findLeaves(node->right, res);
    }
};

//########################### 8. Tree DFS #################################//
// 112. Path Sum: if root-to-leaf path sum exist
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        if (!root->left && !root->right && root->val == sum) return true;
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};
// 113. Path Sum II: find all root-to-leaf paths equal to sum
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (!root) return {};
        vector<vector<int>> res;
        vector<int> out;
        helper(root, sum, res, out);
        return res;
    }
    void helper(TreeNode * node, int sum, vector<vector<int>> & res, vector<int> out) {
        if (!node) return;
        out.push_back(node->val);
        if (!node->left && !node->right && node->val == sum)
            res.push_back(out);
        if (node->left) helper(node->left, sum - node->val, res, out);
        if (node->right) helper(node->right, sum - node->val, res, out);
        out.pop_back();
    }
};
// 437. Path Sum III: Find the number of paths that sum to a given value.
// The path does not need to start or end at the root or a leaf.
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        if (!root) return 0;
        int res = 0;
        vector<TreeNode *> curpath;
        helper(root, sum, res, curpath, 0);
        return res;
    }
    void helper(TreeNode * node, int sum, int & res, vector<TreeNode*> curpath, int cursum) {
        if (!node) return;
        cursum += node->val;
        if (sum == cursum) ++res; //[0,...,cur]
        int tmp = cursum;
        // traverse [1,...,cur], [2,...,cur],..,[cur,cur]
        for (int i = 0; i < (int)curpath.size(); ++i) {
            tmp -= curpath[i]->val;
            if (tmp == sum) ++res;
        }
        curpath.push_back(node); // here, after for()
        helper(node->left, sum, res, curpath, cursum);
        helper(node->right, sum, res, curpath, cursum);
        curpath.pop_back(); // must
    }
};
// 129. Total Sum of all Root-to-Leaf Numbers
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        return helper(root, 0);
    }
    int helper(TreeNode * node, int pathsum) { // not & pathsum
        if (!node) return 0;
        pathsum = pathsum * 10 + node->val;
        if (!node->left && !node->right) return pathsum;
        return helper(node->left, pathsum) + helper(node->right, pathsum);
    }
};
// 257. Binary Tree Paths, in strings
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root) return {};
        vector<string> res;
        helper(root, res, "");
        return res;
    }
    void helper(TreeNode * node, vector<string> & res, string curpath) {
        if (!node) return;
        curpath = curpath + to_string(node->val);
        if (!node->left && !node->right) res.push_back(curpath);
        if (node->left) helper(node->left, res, curpath + "->");
        if (node->right) helper(node->right, res, curpath + "->");
    }
};
// Check if a number sequence is a root-to-leaf path in a tree
class Solution {
public:
    bool checkPath(TreeNode* root, vector<int> & nums) {
        if (!root) return nums.empty();
        return helper(root, nums, 0); // initial index: 0
    }
    bool helper(TreeNode * node, vector<int> & nums, int index) {
        if (!node) return false;
		if (index >= nums.size() || node->val != nums[index]) return false;
		// node is leaf, and it is the end of the sequence
        if (!node->left && !node->right && index = nums.size() - 1) return true;
		return helper(node->left, nums, index + 1) || helper(node->right, nums, index + 1);
    }
};
// 543. Diameter of Binary Tree
// Diameter: the length of the longest path between any two nodes
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int res = 0;
        getHeight(root, res);
        return res;  // diameter: in terms of path's length 
    }
    // height: in terms of num of nodes
    int getHeight(TreeNode * node, int & res) { 
        if (!node) return 0;
        int leftHeight = getHeight(node->left, res);
        int rightHeight = getHeight(node->right, res);
        // update global tree diameter
        res = max(res, leftHeight + rightHeight);
        // height of cur node
        return 1 + max(leftHeight, rightHeight);
    }
};
// 1522. Diameter of N-Ary Tree: the length of the longest path between any two nodes
class Solution {
public:
    int diameter(Node* root) {
        if (!root) return 0;
        int res = 0;
        getHeight(root, res);
        return res;
    }
    int getHeight(Node * node, int & res) {
        if (!node) return 0;
        int firstMax = 0, secondMax = 0;
        for (auto child : node->children) {
            int height = getHeight(child, res);
            if (height >= firstMax) {
                secondMax = firstMax;
                firstMax =  height;
            }
            else if (height > secondMax) {
                secondMax = height;
            }
        }
        res = max(res, firstMax + secondMax);
        return 1 + firstMax;
    }
};

//########################### 9. Two Heaps #################################//
// 295. Find Median from Data Stream
class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {}
    void addNum(int num) {
        if (maxHeap.empty() || maxHeap.top() >= num)
            maxHeap.push(num);
        else
            minHeap.push(num);
        // balance: maxHeap has same numbers (or one more) of elements than minHeap
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    double findMedian() {
        if (maxHeap.size() > minHeap.size())
            return (double) maxHeap.top();
        else 
            return (double)(maxHeap.top() + minHeap.top()) / 2.0;
    }
private:
    priority_queue<int> maxHeap; // maxHeap: nums less than median
    priority_queue<int, vector<int>, greater<int>> minHeap; // minHeap: nums larger than median
};
// 239. Sliding Window Maximum
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        // multiset: ascending sort by default, allow duplicates
        multiset<int, greater<int>> ms; // descending order
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (i >= k) ms.erase(ms.find(nums[i - k])); // ms.erase(nums[i-k]) will erase all duplicates
            ms.insert(nums[i]);
            if (i >= k -1) res.push_back(*ms.begin());
        }
        return res;
    }
};
// 480. Sliding Window Median
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        multiset<int> small, large; // ascending sort
        for (int i = 0; i < (int)nums.size(); ++i) {
            // remove nums[i-k]
            if (i >= k) {
                if (small.count(nums[i - k])) 
                    small.erase(small.find(nums[i - k]));
                else
                    large.erase(large.find(nums[i - k]));
            }
            // insert nums[i]
            if (small.empty() || *small.rbegin() >= nums[i])
                small.insert(nums[i]);
            else
                large.insert(nums[i]);
            // balance
            if (small.size() > large.size() + 1) {
                large.insert(*small.rbegin());
                // small.erase(small.rbegin()); // error
                small.erase(--small.end());
            }
            else if (small.size() < large.size()) {
                small.insert(*large.begin());
                large.erase(large.begin());
            }
            // find median
            if (i >= k - 1) {
                if (small.size() > large.size())
                    res.push_back(*small.rbegin());
                else // ==
                    res.push_back(((double)*small.rbegin() + *large.begin()) / 2.0);
            }
        }
        return res;
    }
};
// 502. IPO: maximize Capital at most k distinct projects 
class Solution {
public:
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
        priority_queue<pair<int, int>> maxHeap; // profit-capital
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; // capital-profit
        for (int i = 0; i < (int)Profits.size(); ++i) {
            minHeap.push(make_pair(Capital[i], Profits[i])); // sort by capital inscending
        }
        for (int i = 0; i < k; ++i) {
            while (!minHeap.empty() && minHeap.top().first <= W) { // projects that available for W capital
                auto t = minHeap.top(); minHeap.pop();
                maxHeap.push(make_pair(t.second, t.first)); // sort by profit descending
            }
            if (maxHeap.empty()) break;
            W += maxHeap.top().first;
            maxHeap.pop(); // at most k distinct projects
        }
        return W;
    }
};



//########################### 10. Subsets #################################//
// 78. Subsets - BFS, Time O(2^N), Space O(2^N)
// Input: nums = [1,2,3]; Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        res.push_back(vector<int>()); // empty set
        for (int num : nums) {
            int n = res.size();
            for (int i = 0; i < n; ++i) {
                vector<int> newset(res[i]); // copy set
                newset.push_back(num); // extend new set
                res.push_back(newset);
            }
        }
        return res;
    }
};
// 90. Subsets II - BFS, Time O(2^N), Space O(2^N)
// Input: nums = [1,2,2]; Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // duplicates are aligned together
        vector<vector<int>> res(1); // empty set
        int n = nums.size(), endIdx = 0;
        for (int i = 0; i < n; ++i) {
            int startIdx = 0;
            if (i > 0 && nums[i] == nums[i - 1]) { // if duplicate
                startIdx = endIdx; // prev end idx
            }
            endIdx = res.size();
            for (int j = startIdx; j < endIdx; ++j) {
                vector<int> newset(res[j]);
                newset.push_back(nums[i]);
                res.push_back(newset);
            }   
        }
        return res;
    }
};
// 47. Permutations II - BFS, Time O(N*N!), Space O(N*N!)
// Input: nums = [1,1,2]; Output: [[1,1,2], [1,2,1],  [2,1,1]]
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        set<vector<int>> res{{}}; // empty set
        for (int num : nums) {
            set<vector<int>> tmp;
            for (auto oldvec : res) {
                int n = oldvec.size();
                // insert to every postion: [1, 3] => [5,1,3],[1,5,3],[1,3,5]
                for (int i = 0; i <= n; ++i) { 
                    vector<int> newvec = oldvec;
                    newvec.insert(newvec.begin() + i, num);
                    tmp.insert(newvec);
                }
            }
            res = tmp;
        }
        return vector<vector<int>> (res.begin(), res.end());
    }
};
// 784. Letter Case Permutation - BFS, Time O(N * 2^N), Space Time O(N * 2^N)
// Input: S = "a1b2"; Output: ["a1b2","a1B2","A1b2","A1B2"]
class Solution {
public:
    vector<string> letterCasePermutation(string str) {
        if (str.empty()) return {};
        vector<string> res{str}; // start with input str
        int n = str.size();
        for (int i = 0; i < n; ++i) { // O(N)
            if (isdigit(str[i])) continue; // skip digit
            
            vector<string> tmp;
            for (string s : res) { // O(2^N)
                tmp.push_back(s); // copy
                if (isupper(s[i])) { // changing char
                    s[i] = tolower(s[i]);
                    tmp.push_back(s);
                }
                else if (islower(s[i])) {
                    s[i] = toupper(s[i]);
                    tmp.push_back(s);
                }
            }
            res = tmp;
        }
        return res;
    }
};
// 22. Generate Parentheses - BFS, Time O(N * 2^N), Space Time O(N * 2^N)
// Input: n = 3; Output: ["((()))","(()())","(())()","()(())","()()()"]
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res(1); // empty string
        for (int i = 0; i < 2*n; ++i) {
            vector<string> tmp;
            for (string str : res) { // O(2^N)
                int lnum = count(str.begin(), str.end(), '(');
                int rnum = count(str.begin(), str.end(), ')');
                if (lnum < n) {
                    tmp.push_back(str + '('); // O(N)
                }
                if (rnum < lnum) {
                    tmp.push_back(str + ')');
                }
            }
            res = tmp;
        }
        return res;
    }
};
// 320. Generalized Abbreviation
// Input: word = "BAT", Output: 3, 2T, 1A1, 1AT, B2, B1T, BA1, BAT
class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> res(1); // empty string

        int n = word.size();
        // iterate n+1 time, 
        for (int i = 0; i <= n; i++) {
            vector<string> tmp;
            for (string str : res) {
                // for the (n+1)th iteration, skip abbraviation, 
				// change "A__" to "A2" to final result
                if (i < n) {
                    // abbrevate ith char
                    tmp.push_back(str + '_');                
                }

                // keep ith char, need to convert #abbrevations to its num
                int index;
                if ((index = str.find("_")) != std::string::npos) { // found "_"
                    int cnt =  str.size() - index;
                    string ss;
                    for (int j = 0; j < index; j++) {
                        ss += str[j];
                    }
                    ss += to_string(cnt);
                    ss += word[i];
                    tmp.push_back(ss);
                }
                else {
                    tmp.push_back(str + word[i]);
                }

            }
            res = tmp;
        }
        return res;
    }
};
// 241. Different Ways to Add Parentheses
// Input: expression = "2-1-1"; Output: [0,2]
// Explanation: ((2-1)-1) = 0;(2-(1-1)) = 2
class Solution {
public:
    // method 2
    // memoization for reduce time complexity
    unordered_map<string, vector<int>> m; 
    
    vector<int> diffWaysToCompute(string input) {
        // input have been already calculated
        if (m.find(input) != m.end()) return m[input]; 
        
        vector<int> res;
        // input is purely a number
        if (input.find("+") == string::npos
           && input.find("-") == string::npos
           && input.find("*") == string::npos) {
            res.push_back(stoi(input)); 
        } 
        else {
            int n = input.size();
            for (int i = 0; i < n; i++) {
                char c = input[i];
                if (!isdigit(c)) {
                    vector<int> lefts = diffWaysToCompute(input.substr(0, i));
                    vector<int> rights = diffWaysToCompute(input.substr(i+1));
                    for (int left : lefts) {
                        for (int right : rights) {
                            if (c == '+') {
                                res.push_back(left + right);
                            }
                            else if (c == '-') {
                                res.push_back(left - right);
                            }
                            else if (c == '*') {
                                res.push_back(left * right);
                            }
                        }
                    }
                }
            }
        }
        
        // update hashmap
        m[input] = res;
        
        return res;
    }
};
// 95. Unique Binary Search Trees II
// Input: n = 3
// Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> res;
        res =  generateTrees(1, n);
        return res;
    }
    vector<TreeNode*> generateTrees(int start, int end) {
        if (start > end) return {nullptr};
        
        vector<TreeNode*> res;
        // root at i
        for (int i = start; i <= end; i++) {
            vector<TreeNode*> lefts = generateTrees(start, i - 1);
            vector<TreeNode*> rights = generateTrees(i + 1, end);
            
            for (auto left : lefts) {
                for (auto right : rights) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};
// 96. Number of Unique Binary Search Trees
class Solution {
public:
    unordered_map<int, int> m; // rootI - #BST
    int numTrees(int n) {
        if (m.count(n)) return m[n];
        if (n <= 1) return 1;

        int res = 0 ;
        for (int i = 1; i <= n; i++) { 
            // make root 'i' of the tree, for example i=4
            // left subtrees: [1, 2, 3]
            int leftTrees = numTrees(i - 1);
            // right subtrees: numTrees of [5, 6, 7, 8] == numTrees of [1, 2, 3, 4]
            int rightTrees = numTrees(n - i);
            res += leftTrees * rightTrees;
        }
        
        m[n] = res;
        
        return res;
    }
};


//########################### 11. Modified Binary Search #################################//
// binary search, 
int search(vector<int>& nums, int target) {
	int left = 0, right = nums.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] == target) return mid;
		else if (nums[mid] < target) left = mid + 1;
		else right = mid - 1;
	}
	return -1; // for normal binary search
}
// Ceiling num: the first larger number in ascending array (no replicate)
int searchCeilingNum(vector<int>& nums, int target) {
	if (target > nums[nums.size() - 1]) return -1;
	int left = 0, right = nums.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] == target) return mid;
		else if (nums[mid] < target) left = mid + 1;
		else right = mid - 1;
	}
	return left;
}
int searchCeilingNum(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left < right) { // "<", end when left==right
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }    
    return (nums[right] >= target) ? right : -1;
}

// 744. Find Smallest Letter Greater Than Target
// Input: letters = ["c","f","j"], target = "c"; Output: "f"
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

// 34. Find First and Last Position of Element in Sorted Array
// Input: nums = [5,7,7,8,8,10], target = 8; Output: [3,4]
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n - 1;
        int resLeft = -1, resRight = -1;
        
        // first num equal to target
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        if (left >= n || nums[left] != target) return {-1, -1};
        
        resLeft = left;
        
        // smallest num larger than target
        left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) left = mid + 1;
            else right = mid - 1;
        }
        resRight = left - 1;
        
        return {resLeft, resRight};
    }
};

// 33. Search in Rotated Sorted Array, distinct elements
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n - 1;
        while (left <= right) { // "<="
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            
			// If allowing duplicates in nums, then skip from both sides
			//if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
            //    ++left; --right;
            //}
            if (nums[left] <= nums[mid]) { // left part is sorted
                if (nums[left] <= target && target < nums[mid]) right = mid - 1;
                else left = mid + 1;
            }
            else { // right part is sorted
                if (nums[mid] < target && target <= nums[right]) left = mid + 1;
                else right = mid - 1;
            }
        }
        return -1;
    }
};

// 153. Find Minimum in Rotated Sorted Array
// Input: nums = [3,4,5,1,2]; Output: 1
// Explanation: The original array was [1,2,3,4,5] rotated 3 times.
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size(), left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
			// min elem: the one smaller than its left
            if ((left < mid) && (nums[mid - 1] > nums[mid])) return nums[mid];
            if ((mid < right) && (nums[mid] > nums[mid + 1])) return nums[mid + 1];
            
            if (nums[left] <= nums[mid]) { // left part is sorted
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        
        return nums[0]; // nums is not rotated
    }
};
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size(), left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[right]) right = mid;
            else left = mid + 1;
        }
        return nums[right]; 
    }
};

// 1060. Missing Element in Sorted Array
// Input: nums = [4,7,9,10], k = 3; Output: 8
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        int cnt = missingCount(nums, right);
        if (cnt < k) {
            return nums[right] + k - cnt;
        }
        
        while(left < right) {
            int mid = left + (right - left) / 2;
            cnt = missingCount(nums, mid);
            if (cnt < k) left = mid + 1;
            else right = mid;
        }
        
        // not nums[right] - 1, not know previous missing before nums[right]
        return nums[right - 1] + k - missingCount(nums, right - 1);
    }
    
    // missing number from 0th to idx-th number
    int missingCount(vector<int>& nums, int idx) {
        return nums[idx] - nums[0] - idx; // [4,7,9]: 9-4-2=3
    }
};

// 378. Kth Smallest Element in a Sorted Matrix
// Time: O(N*logX), X = max-min, Space: O(1)
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int left = matrix[0][0], right = matrix.back().back();
        while (left < right) {
            int mid = left + (right - left) / 2;
            int cnt = less_equal_count(matrix, mid);
            if (cnt < k) left = mid + 1;
            else right = mid;
        }
        return right;
    }
    int less_equal_count(vector<vector<int>>& matrix, int val) {
        // matrix: rows and columns are sorted in ascending order
        // search from bottom-left
        int n = matrix.size(), row = n - 1, col = 0, cnt = 0;
        while (0 <= row && col < n) {
            if (matrix[row][col] <= val) {
                cnt += row + 1;
                col++;
            }
            else {
                row--;
            }
        }
        return cnt;
    }
};


//########################### 12. Bitwist XOR #################################//
// 136. Single Number
// Input: nums = [4,1,2,1,2]; Output: 4
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int num : nums) res ^= num;
        return res;
    }
};
// 137. Single Number II
// Input: nums = [0,1,0,1,0,1,99]; Output: 99
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < 32; i++) { // cnt at each i-th bit position
            int bitCnt = 0;
            for (int num : nums) {
                bitCnt += (num >> i) & 1; // i-th bit in num has value 1
            }
            // set i-th bit in res to 1 if ith bitCnt is 1 not 3
            res |= (bitCnt % 3) << i;  
        }
        return res;
    }
};
// 260. Single Number III
// Input: nums = [1,2,1,3,2,5]; Output: [3,5]
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int n1xn2 = 0;
        for (int num : nums) n1xn2 ^= num;
        
        // rightMostSetBit: to partition all nums into two groups
        // one has num1 (ith bit of 0) and the other has num2 (ith bit of 1)
        int rightMostSetBit = 1;
        while ((rightMostSetBit & n1xn2) == 0) {
            rightMostSetBit <<= 1;  // right shift by one
        }
        
        int num1 = 0, num2 = 0;
        for (int num : nums) {
            if ((num & rightMostSetBit) == 0) { // ith bit in num has value of 0
                num1 ^= num;
            }
            else { // ith bit in num has value of 1
                num2 ^= num;  
            } 
        }
        
        return {num1, num2};
    }
};

// 1009. Complement of Base 10 Integer
// Input: n = 5 (101);  Output: 2 (010)
class Solution {
public:
    int bitwiseComplement(int num) {
        // corner case
        if (num == 0) return 1;
        // complement = number ^ all_bits_set
        int bitCnt = 0, tmp = num;
        while (tmp > 0) {
            bitCnt++;
            tmp >>= 1;
        }
        int all_bits_set = pow(2, bitCnt) - 1;
        return num ^ all_bits_set;
    }
};

// 287. Find the Duplicate Number
// Input: nums = [3,1,3,4,2]; Output: 3
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
            sort(nums.begin(), nums.end());

            int n = nums.size(), left = 0, right = n - 1;
            while (left < right) {
                int mid = left + (right - left) / 2;
                if ((0 < mid && nums[mid - 1] == nums[mid])
                   || (mid < n - 1 && nums[mid + 1] == nums[mid])) return nums[mid];

                if (mid >= nums[mid]) right = mid - 1;
                else left = mid + 1;
            }

            return nums[right];
    }
};


//########################### 13. Top K Elements #################################//
// 215. Kth Largest Element in an Array
// Time: O(N*log(N)), Space O(N)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> q(nums.begin(), nums.end()); // time: N*logN
        for (int i = k; i > 1; i--) q.pop();  // time: K*log(N)
        return q.top();
    }
};
// Time: O(N*logN), Space: O(1)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) {
            int pos = divide(nums, left, right);
            
            // kth largest elem at (k-1)-th position
            if (pos == k - 1) return nums[pos];
            
            if (pos > k - 1) right = pos - 1;
            else left = pos + 1;
        }
    }
    int divide(vector<int> & nums, int start, int end) { // quicksort
        int pivot = nums[start], left = start + 1, right = end;
        while (left <= right) {
            if (nums[left] < pivot && nums[right] >= pivot) {
                swap(nums[left++], nums[right--]); // swap: O(1)
            }
            else if (nums[left] >= pivot) {
                left++;
            }
            else if (nums[right] < pivot) {
                right--;
            }
        }
        swap(nums[start], nums[right]);
        return right;
    }
};

// 347. Top K Frequent Elements
// Input: nums = [1,1,1,2,2,3], k = 2; Output: [1,2]
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> q; // cnt-num, default maxheap
        unordered_map<int, int> m; // num-cnt
        vector<int> res;
        for (int num : nums) m[num]++;
        for (auto a : m) q.push({a.second, a.first});
        for (int i = 0; i < k; i++) {
            auto tmp = q.top(); q.pop();
            res.push_back(tmp.second);
        }
        return res;
    }
};

// 973. K Closest Points to Origin
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        auto cmp = [](auto& a, auto& b) {
            // min heap, '>', i.e., next elem larger than cur elem
            return (a[0] * a[0] + a[1] * a[1]) > (b[0] * b[0] + b[1] * b[1]);
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        vector<vector<int>> res;
        
        for (auto a : points) q.push(a);
        
        for (int i = k; i > 0; i--) {
            res.push_back(q.top());
            q.pop();
        }
        
        return res;
    }
};

// minimum cost to connect ropes
// every step you pick two shortest ropes and connect them, 
// then put it back to the selections, the process repeat until only one left.
// Input = [3, 4, 5, 6]; Output: 36 = ((3 + 4) + (5 + 6)) = 7 + 11 + 18
int minCostConnectRopes(vector<int>& ropes) {
    if (ropes.size() <= 1) return 0;
    
    auto cmp = [](auto & a, auto & b) {
        return a > b;
    };
    priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
    int cost = 0;
    
    for (auto a : ropes) q.push(a);
    
    while (q.size() > 1) {
        int tmp1 = q.top(); q.pop();
        int tmp2 = q.top(); q.pop();
        cost += tmp1 + tmp2;
        q.push(tmp1 + tmp2);
    }
    
    return cost;
}

// 451. Sort Characters By Frequency
// Input: s = "tree"; Output: "eert"
class Solution {
public:
    string frequencySort(string s) {
        priority_queue<pair<int, char>> q; // frequency-char, max-heap
        unordered_map<char, int> m; //char-freq
        string res = "";
        
        for (char c : s) m[c]++;
        for (auto a : m) q.push({a.second, a.first});
        
        while (!q.empty()) {
            auto tmp = q.top(); q.pop();
            res.append(tmp.first, tmp.second);
        }
        
        return res;
    }
};

// 658. Find K Closest Elements
// Note for duplicates
// Input: arr=[0,1,1,1,2,3,6,7,8,9]; k=9, x=4; Output: [0,1,1,1,2,3,6,7,8]
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        auto cmp = [](pair<int, int> &a, pair<int, int> &b) {
            // sorted ascending arr: (idx1 < idx2) ==> (val1 < val2)
            return (a.second < b.second) 
                || ((a.second == b.second) && (a.first < b.first));
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp); // idx-dist
        unordered_map<int, int> m; // idx-dist
        
        for (int i = 0; i < arr.size(); i++) {
            m[i] = abs(arr[i] - x);
        }
        for (auto a : m) {
            q.push({a.first, a.second});
            if (q.size() > k) q.pop();
        }
        
        vector<int> res;
        while (!q.empty()) {
            res.push_back(arr[q.top().first]);
            q.pop();
        }
        sort(res.begin(), res.end());
        
        return res;
    }
};

// Remove K nums from array to left maximum distinct numbers
// Input: arr = {7, 3, 5, 8, 5, 3, 3}, k = 2; Output: 3
int maxDistinctElemAfterRemoveKElems(vector<int>& nums, int k) {
    auto cmp = [](pair<int, int> & a, pair<int, int> & b) {
        return (a.second < b.second) 
                || ((a.second == b.second) && (a.first < b.first));
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, 
                    decltype(cmp)> q(cmp); // num-freq
    unordered_map<int, int> m; // num-freq
    int res = 0;
    
    for (int num : nums) m[num]++;
    for (auto a : m) {
        if (a.second > 1) q.push({a.first, a.second}); // num with freq >= 2
        else res++;
    }
    
    while (k > 0 && !q.empty()) {
        auto tmp = q.top(); q.pop();
        if (k - tmp.second <= 1) {
            k = k - tmp.second + 1; // decrease freq-1 of num to make it distinct
            res++;
        }
    }
    
    // NOTE 
    if (k > 0) res -= k;
    
    return res;
}

// 1481. Least Number of Unique Integers after K Removals
// Input: arr = [4,3,1,1,3,3,2], k = 3;  Output: 2
// Explanation: Remove 4, 2 and either one of the two 1s or three 3s. 1 and 3 will be left.
class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        auto cmp = [](pair<int, int> &a, pair<int, int> &b) {
            return (a.second > b.second)
                || ((a.second == b.second) && (a.first < b.first));
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, 
                        decltype(cmp)> q(cmp);  // minHeap: num-freq
        unordered_map<int, int> m; // num-freq
        
        for (int a : arr) m[a]++;
        for (auto a : m) {
            q.push({a.first, a.second});
        }
        
        while (k > 0 && !q.empty()) {
            auto tmp = q.top(); q.pop();
            if (k - tmp.second < 0) {
				// NOTE
                q.push({tmp.first, tmp.second - k});
                break;
            }
            else {
                k -= tmp.second;
            }
        }
        
        return q.size();
    }
};

// Sum of all elements between k1'th and k2'th smallest elements
// Sort(): Time O(N*logN), Space O(N)
// maxHeap: Time O(N*logk2), Space O(k2)
int sumBetweenK1K2SmallestElem(vector<int> & nums, int k1, int k2) {
    priority_queue<int> q; // maxHeap, contains k2 smallest elems
    for (int num : nums) {
        if (q.size() < k2) {
            q.push(num);
        }
        else if (q.top() > num) {
            q.pop();
            q.push(num);
        }
    }
    
    int res = 0;
    q.pop(); // exclude the k2th elem
    while (q.size() > k1) {
        res += q.top(); q.pop();
    }
    
    return res;
}


// 767. Reorganize String, any two adjacent characters are not the same.
class Solution {
public:
    string reorganizeString(string s) {
        auto cmp = [](pair<char, int> & a, pair<char, int> & b) {
            return (a.second < b.second) 
                || ((a.second == b.second) && a.first > b.first);
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>,
                    decltype(cmp)> q(cmp); // maxHeap: char-freq
        unordered_map<char, int> m; // char-freq
        int len  = s.size();
        string res = "";
        
        for (char c : s) m[c]++;
        for (auto a : m) {
            if (a.second > (len + 1) / 2) return ""; // optimization
            q.push(a);
        }
        
        while (q.size() >= 2) {
            auto t1 = q.top(); q.pop();
            auto t2 = q.top(); q.pop();
            res += t1.first;
            res += t2.first;
            if (--t1.second) q.push(t1);
            if (--t2.second) q.push(t2);
        }
        
        // NOTE
        if (q.size() > 0) res += q.top().first;
        
        return res;
    }
};
// 358. Rearrange String k Distance Apart
class Solution {
public:
    string rearrangeString(string s, int k) {
        if (k <= 1) return s; // corner case: s="a", k=0
        auto cmp = [](pair<char, int> & a, pair<char, int> & b) {
            return (a.second < b.second)
                || ((a.second == b.second) && (a.first > b.first));
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>,
                    decltype(cmp)> q(cmp); // maxHeap: char-freq
        unordered_map<char, int> m; // char-freq
        int len = s.size();
        string res = "";
        
        for (char c : s) m[c]++;
        for (auto a : m) q.push(a);
        
        while (!q.empty()) {
            // num of positions to be filled in
            int cnt = min(k, len);
            vector<pair<char, int>> tmp; 
            for (int i = cnt; i > 0; i--) {
                if (q.empty()) return ""; // not more distinct char
                auto t = q.top(); q.pop();
                res += t.first;
                if (--t.second) tmp.push_back(t);
                --len; // NOTE
            }
            
            for (auto a : tmp) q.push(a);
        }
        
        return res;
    }
};

// 621. Task Scheduler
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        auto cmp = [](pair<char, int> & a, pair<char, int> & b) {
            return (a.second < b.second)
                || ((a.second == b.second) && (a.first > b.first));
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>,
                    decltype(cmp)> q(cmp); // maxHeap: task-num
        unordered_map<char, int> m; // task-num
        string res = "";
        
        for (char c : tasks) m[c]++;
        for (auto a : m) q.push(a);
        
        while (!q.empty()) {
            vector<pair<char, int>> tmp;
            
            for (int i = n + 1; i > 0; i--) { // NOTE, cycle: n+1
                if (q.empty()) {
                    res += '#'; // no distinct char, add 'idle'
                }
                else {
                    auto t = q.top(); q.pop();
                    res += t.first;
                    if (--t.second) tmp.push_back(t);
                    
                    // the very last task
                    if (t.second == 0 && tmp.empty() && q.empty()) break;
                }
            }
            
            for (auto a : tmp) q.push(a); // remaining tasks
        }
        
        return res.size();
    }
};

// 895. Maximum Frequency Stack
// Input
// ["FreqStack", "push", "push", "push", "push", "push", "push", "pop", "pop", "pop", "pop"]
// [[], [5], [7], [5], [7], [4], [5], [], [], [], []]
// Output: [null, null, null, null, null, null, null, 5, 7, 5, 4]
class FreqStack {
public:
    FreqStack() { }
    
    void push(int val) {
        maxFreq = max(maxFreq, ++freq[val]); // update maxFreq
        m[freq[val]].push_back(val); // 
    }
    
    int pop() {
        int x = m[maxFreq].back(); // pop the most recent one
        m[maxFreq].pop_back();
        --freq[x]; // update freq map
        if (m[maxFreq].empty()) { // update freq-values map
            m.erase(maxFreq);
            --maxFreq;
        }
        return x;
    }
private:
    int maxFreq; // max
    unordered_map<int, int> freq; // num-freq
    unordered_map<int, vector<int>> m; // freq-valuesHavingSameFreq
};


//########################### 14. K way merge #################################//
// 23. Merge k Sorted Lists, Time: O(N*logK), Space: O(K)
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* & a, ListNode* & b) {
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>,
                decltype(cmp)> q(cmp); // minHeap
        ListNode * res = new ListNode(-1), *cur = res; // res to return
        
        for (auto root : lists) {
            if (root) q.push(root);
        }
        
        while (!q.empty()) {
            auto t = q.top(); q.pop();
            
            cur->next = t;
            cur = cur->next;
            if (t->next) q.push(t->next); // add next small value
        }
        
        return res->next;
    }
};

// Find kth smallest element in N arrays
int kthSmallestInNarrays(vector<vector<int>>& nums, int k) {
    auto cmp = [](pair<int, vector<int>> & a, pair<int, vector<int>> & b) {
        return (a.first > b.first) 
            || ((a.first == b.first) && a.second[0] > b.second[0]);
    };
    priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>,
                    decltype(cmp)> q(cmp); // val-(rowIdx, colIdx)
    int n = nums.size();
                    
    for (int i = 0; i < n; i++) {
        q.push({nums[i][0], {i, 0}});
    }
    
    while (k > 1 && !q.empty()) {
        k--;
        
        auto t = q.top(); q.pop();
        int row = t.second[0], col = t.second[1];
        
        if (col + 1 < nums[row].size()) {
            q.push({nums[row][col + 1], {row, col + 1}});
        }
    }
    
    return (k > 1) ? -1 : q.top().first;
}


// 76. Minimum Window Substring
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> m; // char-freq
        int left = 0, minLen = INT_MAX, cnt = 0;
        string res = "";
        
        for (char c : t) m[c]++;
        
        for (int i = 0; i < s.size(); i++) {
            if (--m[s[i]] >= 0) cnt++; // s[i] in t, increase cnt
            // substring includes the whole t 
            while (cnt == t.size()) {
                // update substring
                if (i - left + 1 < minLen) {
                    minLen = i - left + 1;
                    res = s.substr(left, minLen);
                }
                // shift subwindow right, and s[left] in t
                if (++m[s[left]] > 0) cnt--;
                ++left;
            }
        }
        
        return res;
    }
};















