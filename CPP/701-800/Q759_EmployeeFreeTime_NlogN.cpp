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
