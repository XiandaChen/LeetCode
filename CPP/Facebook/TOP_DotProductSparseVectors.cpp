class SparseVector {
public:
	SparseVector(vector<int> &nums) {
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (nums[i] != 0) m[i] = nums[i]; }  }
    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        int res = 0, size1 = m.size(), size2 = vec.m.size();
        if (size1 < size2) {
            for (auto a : m) {
                if (vec.m.count(a.first))
                    res += a.second * vec.m[a.first];  }  }
        else {
            for (auto a : vec.m) {
                if (m.count(a.first))
                    res += a.second * m[a.first]; }  }
        return res;
    }
private:
    unordered_map<int, int> m; // index-val
};
