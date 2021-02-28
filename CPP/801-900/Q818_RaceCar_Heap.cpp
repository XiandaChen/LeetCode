class Solution {
public:
    int racecar(int target) {
        int res = 0;
        queue<pair<int, int>> q{{{0, 1}}}; // position-speed
        unordered_set<string> visited{{"0,1"}}; // states: "pos,speed"
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                int pos = q.front().first, speed = q.front().second;
                q.pop();
                if (pos == target) return res;

                // instruction accelerate: position += speed, speed *= 2
                int newPos = pos + speed, newSpeed = speed * 2;
                string state = to_string(newPos) + "," + to_string(newSpeed);
                if (!visited.count(state) && 0 < newPos && newPos <= target * 2) {
                    q.push({newPos, newSpeed});
                    visited.insert(state);
                }

                // instruction reverse: position stays the same; 
                // speed is positive then speed = -1 , otherwise speed = 1
                newPos = pos;
                newSpeed = (speed > 0) ? -1 : 1;
                state = to_string(newPos) + "," + to_string(newSpeed);
                if (!visited.count(state) && 0 < newPos && newPos <= target * 2) {
                    q.push({newPos, newSpeed});
                    visited.insert(state);
                }
            }
            ++res;
        }
        return -1;
    }
};