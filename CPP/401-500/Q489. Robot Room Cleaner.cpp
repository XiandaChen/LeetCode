// /**
//  * // This is the robot's control interface.
//  * // You should not implement it, or speculate about its implementation
//  * class Robot {
//  *   public:
//  *     // Returns true if the cell in front is open and robot moves into the cell.
//  *     // Returns false if the cell in front is blocked and robot stays in the current cell.
//  *     bool move();
//  *
//  *     // Robot will stay in the same cell after calling turnLeft/turnRight.
//  *     // Each turn will be 90 degrees.
//  *     void turnLeft();
//  *     void turnRight();
//  *
//  *     // Clean the current cell.
//  *     void clean();
//  * };
//  */

class Solution {
public:
    vector<vector<int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // up, right, down, left
    void cleanRoom(Robot& robot) {
        unordered_set<string> visited;
        helper(robot, 0, 0, 0, visited); // assume robot initial location as (0,0) and face up
    }
    void helper(Robot & robot, int x, int y, int dir, unordered_set<string> & visited) {
        robot.clean();
        visited.insert(to_string(x) + "_" + to_string(y));
        
        for (int i = 0; i < 4; i++) { // search up, right, down, left
            int cur = (i + dir) % 4, newX = x + dirs[cur][0], newY = y + dirs[cur][1];
            
            // if <newX, newY> is not visited, and reachable
            if (!visited.count(to_string(newX) + "_" + to_string(newY)) && robot.move()) {
                // move forward
                helper(robot, newX, newY, cur, visited); 
                
                // return backward
                robot.turnRight();
                robot.turnRight();
                robot.move();  // return to previous locatioin
                robot.turnRight();
                robot.turnRight(); // turn 180degree to previous direction
            }
            
            // move forward (UP) ->  turnRight -> move forward (RIGHT) 
            //     -> turnRight -> move forward (DOWN) -> turnRight -> move forward (LEFT)
            robot.turnRight();
        }
    }
};

