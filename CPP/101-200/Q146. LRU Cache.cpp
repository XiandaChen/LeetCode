class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        auto it = m.find(key);
        if (it == m.end()) return -1;
        // Move this key to the front of the cache
        cache.splice(cache.begin(), cache, it->second);
        // cache.erase(it->second);
        // cache.emplace_front(it->second)
        return it->second->second;
    }
    
    void put(int key, int value) {
        auto it = m.find(key);
        // key exists, erase old <key, val>
        if (it != m.end()) cache.erase(it->second);
        // insert new <key, val> to front
        cache.push_front({key, value});
        m[key] = cache.begin();
        // Reached the capacity, remove the oldest entry
        if (cache.size() > cap) {
            int k = cache.rbegin()->first; // the last one
            cache.pop_back(); // update cache
            m.erase(k); // update interator map
        }
    }
private:
    int cap;
    list<pair<int, int>> cache; // key-val
    unordered_map<int, list<pair<int, int>>::iterator> m; // key-iterator in cache, O(1)
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */