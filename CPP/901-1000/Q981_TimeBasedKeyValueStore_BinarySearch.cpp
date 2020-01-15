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

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */