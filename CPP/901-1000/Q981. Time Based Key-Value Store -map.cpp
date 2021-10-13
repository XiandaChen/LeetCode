class TimeMap {
public:
    TimeMap() {
    }
    
    void set(string key, string value, int timestamp) {
        data[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        if (!data.count(key)) return "";
        
        auto it = data[key].upper_bound(timestamp); // upper_bound: the first larger than timestamp
        if (it == data[key].begin()) return "";
        --it; // return value of timestamp_prev <= timestamp
        return it->second;
    }
private:
    unordered_map<string, map<int, string>> data; // key-[time, value]
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */