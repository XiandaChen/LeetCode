/*
Handle degenerate case of all 0s separately.
Start from top right. Keep doing until we reach last row: go down if current element is 0, go left otherwise.
Column number of final ptr is our answer.
*/

/* test 
int main()
{
	vector<vector<int>> m1 = {{0, 0, 0, 1},
						  {0, 0, 1, 1},
						  {0, 1, 1, 1},
						  {0, 0, 0, 0}};
	vector<vector<int>> m2 = {{0, 0, 0, 0},
						  {0, 0, 0, 0},
						  {0, 0, 0, 0},
						  {0, 0, 0, 0}};
	vector<vector<int>> m3 = {{0, 0, 0, 0},
						  {0, 0, 0, 0},
						  {0, 0, 0, 0},
						  {0, 0, 0, 1}};
                          
	cout << "m1: " << findLeftMostColumnOfOne(m1) << endl;
	cout << "m2: " << findLeftMostColumnOfOne(m2) << endl;
	cout << "m3: " << findLeftMostColumnOfOne(m3) << endl;
 
	return 0;
}
*/

// In a binary matrix (all elements are 0 and 1), every row is sorted in ascending order (0 to the left of 1). 
// Find the leftmost column index with a 1 in it.
// ref: Q1004 Max Consecutive Ones III, Sliding Window
int findLeftMostColumnOfOne(vector<vector<int>> & matrix) {
    // handle edge cases
    if (matrix.empty() || matrix[0].empty()) return -1;
    int rows = matrix.size(), cols = matrix[0].size();
    int res = -1;
    // Search from top right: go down if current element is 0, go left otherwise
    // Keep doing until we reach last row
    for (int r = 0, c = cols - 1; r < rows && c >= 0; ) {
        if (matrix[r][c] == 1) {
            res = c;
            --c;
        }
        else {
            ++r;
        }
    }
    return res;
}