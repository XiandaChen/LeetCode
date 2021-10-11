class AutocompleteSystem {
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        for (int i = sentences.size() - 1; i >= 0; i--) {
            freq[sentences[i]] = times[i];
        }
        data = "";
    }
    
    vector<string> input(char c) {
        // the user finished the input
        if (c ==  '#') {
            freq[data]++; // NOTE, not freq[data] = 1
            data = "";
            return {};
        }
        
        // update the prefix with input c
        data += c;
        
        // construct minHeap to hold top-3 hot sentences with prefic data
        // when minHeap.size > 3, evict the top elem that has min freq
        auto cmp = [] (pair<string, int> & a, pair<string, int> & b) {
            return a.second > b.second 
                || (a.second == b.second && a.first < b.first); // same hot degree, maintain ASCII smaller one
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> q(cmp);
        
        for (auto & f : freq) {
            int len1 = data.size(), len2 = f.first.size();
            if (len1 > len2) continue; // input data is longer than the sentence
            
            bool isPrefix = true;
            for (int i = 0; i < len1; i++) {
                if (data[i] != f.first[i]) { // data is not prefix in the sentence
                    isPrefix = false;
                    break; 
                }
            }
            
            if (isPrefix) {
                q.push(f);
                
                if (q.size() > 3) {
                    q.pop();
                }
            }
        }
        
        // results
        vector<string> res(q.size());
        for (int i = q.size() - 1; i >= 0; i--) { // reversed order, since minHeap
            auto t = q.top(); q.pop();
            res[i] = t.first;
        }
        
        return res;
    }
private:
    unordered_map<string, int> freq; // sentence-time
    string data; // to hold input data
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */