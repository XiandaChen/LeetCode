class TopVotedCandidate {
public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        int n = persons.size(), lead = 0;
        vector<int> cnt(n + 1); // votes person i has
        for (int i = 0; i < n; ++i) {
            // update lead at time i
            if (++cnt[persons[i]] >= cnt[lead]) lead = persons[i];
            m[times[i]] = lead;
        }
    }
    
    int q(int t) {
        // map sort key as a binary tree
        // upper_bound: the immediate next element just greater than key
        // [[0,1,1,0,0,1,0],[0,5,10,15,20,25,30]]
        // t=12, find the first larger time 15, then '--' back to find lead pre-time
        return (--m.upper_bound(t))->second;
    }
private:
    map<int, int> m; // time-lead, sorted by times
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */