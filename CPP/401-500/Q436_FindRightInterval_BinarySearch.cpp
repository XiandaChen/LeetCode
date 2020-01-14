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