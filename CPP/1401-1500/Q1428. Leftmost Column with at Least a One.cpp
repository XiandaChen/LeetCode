/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> dim = binaryMatrix.dimensions();
        int rows = dim[0], cols = dim[1];
        int res = -1;
        int r = 0, c = cols - 1;
        while (r < rows && c >= 0) {
            if (binaryMatrix.get(r, c) == 1) {
                res = c;
                --c;
            }
            else {
                ++r;
            }
        }
        return res;
    }
};