class Solution {
public:
    Solution(vector<vector<int>>& rects) {
        _rects = rects;
    }
    // randomly select a rect, then generate random point within the selected rect
    vector<int> pick() {
        vector<int> selected;
        int sumarea = 0;
        // srand(time(0)); // error
        // step 1: select random rect
        for (auto rect : _rects) {
            // num of points covered by rect
            int area = (rect[2] - rect[0] + 1) * (rect[3] - rect[1] + 1);
            sumarea += area;
            if (rand() % sumarea < area) {
                selected = rect;
                // break; // error
            }                
        }
        // step 2: generate point
        int x = rand() % (selected[2] - selected[0] + 1) + selected[0];
        int y = rand() % (selected[3] - selected[1] + 1) + selected[1];
        return {x, y};
    }
private:
    vector<vector<int>> _rects;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */