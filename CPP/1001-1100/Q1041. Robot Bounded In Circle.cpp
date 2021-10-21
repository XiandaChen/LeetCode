class Solution {
public:
    bool isRobotBounded(string instructions) {
        int face = 0; // 0-north, 1-east, 2-south, 3-west
        vector<vector<int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // 0-north, 1-east, 2-south, 3-west
        vector<int> cur = {0, 0};
        for (char c : instructions) {
            if (c == 'G') {
                cur = {cur[0] + dirs[face][0], cur[1] + dirs[face][1]};
            }
            else if (c == 'L') {
                face = (face + 4 - 1) % 4; // +4 : in case negatives
            }
            else {
                face = (face + 1) % 4;
            }
        }
        // circle: if returns to (0,0), or face other direction other initial north
        return (cur[0] == 0 && cur[1] == 0) || face != 0;
    }
};