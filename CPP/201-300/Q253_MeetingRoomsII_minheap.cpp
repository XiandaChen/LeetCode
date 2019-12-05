class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        auto cmp = [] (vector<int> & a, vector<int> & b) {
            return a[0] < b[0]; };
        sort(intervals.begin(), intervals.end(), cmp);
        priority_queue<int, vector<int>, greater<int>> q;
        for (auto intvl : intervals) {
            // being-used room gets free for new meeting
            if (!q.empty() && q.top() <= intvl[0]) q.pop();
            q.push(intvl[1]);
        }
        return q.size();
    }
};