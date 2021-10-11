// put, get, remove: O(n)
// need to be O(1)
class MyHashMap {
public:
    MyHashMap() {
    }
    
    void put(int key, int value) {
        int idx = 0, n = keys.size();
        bool keyExist = false;
        
        for (; idx < n; idx++) {
            if (keys[idx] == key) {
                keyExist = true;
                break;
            }
        }
        
        if (keyExist) { // key exists, update its value
            values[idx] = value;
            return ;
        }
        
        keys.push_back(key);
        values.push_back(value);
    }
    
    int get(int key) {
        int idx = 0, n = keys.size();
        bool keyExist = false;
        
        for (; idx < n; idx++) {
            if (keys[idx] == key) {
                keyExist = true;
                break;
            }
        }
        
        if (keyExist) return values[idx];
        
        return -1;
    }
    
    void remove(int key) {
        int idx = 0, n = keys.size();
        bool keyExist = false;
        
        for (; idx < n; idx++) {
            if (keys[idx] == key) {
                keyExist = true;
                break;
            }
        }
        
        if (keyExist) {
            keys.erase(keys.begin() + idx);
            values.erase(values.begin() + idx);
        }
    }
private:
    vector<int> keys, values;
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */