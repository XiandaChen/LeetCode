class FreqStack {
public:
    FreqStack() { }
    
    void push(int val) {
        maxFreq = max(maxFreq, ++freq[val]); // update maxFreq
        m[freq[val]].push_back(val); // 
    }
    
    int pop() {
        int x = m[maxFreq].back(); // pop the most recent one
        m[maxFreq].pop_back();
        --freq[x]; // update freq map
        if (m[maxFreq].empty()) { // update freq-values map
            m.erase(maxFreq);
            --maxFreq;
        }
        return x;
    }
private:
    int maxFreq; // max
    unordered_map<int, int> freq; // num-freq
    unordered_map<int, vector<int>> m; // freq-valuesHavingSameFreq
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */