/*
Find maximum meetings in one room.
Find the maximum number of meetings that can be accommodated in the meeting room.

Greedy
Sort all meetings in increasing order of second number(Finish time) of each pair.
Selected not-overlapped intervals
*/

// ref: Q1353. Maximum Number of Events That Can Be Attended
int maxMeetingRooms(vector<vector<int>> & meetings) {
    if (meetings.size() == 0) return -1;
    
    auto cmp = [] (vector<int> & a, vector<int> & b) {
        return a[1] < b[1]; // sort increasing by end time  
    };
    // Sorting of meeting according to their finish time. 
    sort(meetings.begin(), meetings.end(), cmp);
    
    // vector for storing selected meetings
    // vector<int> m = {0};
	int res = 1;
    int endtime = meetings[0][1];
    
    for (int i = 1; i < meetings.size(); ++i) {
        if (meetings[i][0] >= endtime) {
            // m.push_back(i);
			++res;
            endtime = meetings[i][1];
        }
    }
    
    // return m.size();
	return res;
}

/*
int main () {
    vector<vector<int>> m1 = {{1, 2}, {2, 4}, {2, 3}, {3, 5}};
    vector<vector<int>> m2 = {{1, 2}, {2, 3}, {3, 4}, {3, 5}};
    
    cout << maxMeetingRooms(m1) << endl;
    cout << maxMeetingRooms(m2) << endl;
    
	return 0;
}
*/