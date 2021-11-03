class LRUCache {
public: LRUCache(int capacity) {
        cap = capacity;    }
    int get(int key) {
        if (!m.count(key)) return -1;
        int val = m[key]->second;
        // move this key-val to cache front
        // void splice (iterator position, list& x, iterator i);
        cache.splice(cache.begin(), cache, m[key]);  // NOTE, time O(1)
        // cache.erase(m[key]);  // NOTE, time O(n)
        // cache.push_front({key, val});  // time O(1)
        return val;    }
    void put(int key, int value) {
        if (m.count(key)) {
            cache.erase(m[key]);        }
        cache.push_front({key, value});
        m[key] = cache.begin();
        if (cache.size() > cap) { // NOTE: cache.size(), not m.size()
            int k = cache.rbegin()->first;  // LRU key
            m.erase(k);
            cache.pop_back();        }    }
private: int cap;
    list<std::pair<int, int>> cache; //cache: key-val
    unordered_map<int, list<std::pair<int, int>>::iterator> m; // key-iterator in cache
};
