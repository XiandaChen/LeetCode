class LRUCache {
public:
    LRUCache(int capacity) {
        m_cap = capacity;
    }
    
    int get(int key) {
        auto it = m_map.find(key);
        if (it == m_map.end()) return -1;
        m_list.splice(m_list.begin(), m_list, it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        auto it = m_map.find(key);
        if (it != m_map.end()) m_list.erase(it->second);
        m_list.push_front(make_pair<key, value>);
        m_map[key] = m_list.begin();
        if (m_map.size() > m_cap) {
            int k = m_list.rbegin()->first;
            m_list.pop_back();
            m_map.erase(k);
        }
    }
private:
    int m_cap;
    list<pair<int, int>> m_list;
    unordered_map<int, list<pair<int, int>>> m_map;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */