#include <iostream>

// job-priority
// job: int id
// priority: 3: high, 2: medium, 1:low
// input vector<vetor<int>> <job-id, priority>: [[1, 3], [2, 1]...]
// output: vector<int> list of job-ids ordered by prioriyt

// [1, 3] [2, 3]  => 1, random, 2. sort by id

// method 1: sort time: O(NlogN)   no
// method 2: maxHeap, by priroity, time construct O(logN), O(N), downside space : extrac O(N)

// method 3: in-place, negilible NOT space O(N)

// job size : 100 mill

// you: negilible space (1000), time < o(nlogn)

#include <vector>

void printPriority(vector<vector<int>> & jobs, int n) {
    // modify in-place, jobs

    // [1, 3] [2, 3]

    // 100 maxHeap, top 100 priot
    // [1, 3] [2, 3] ==> [-1, 3] [-1, 3]
    // jobNum = 100 mill

    //  method 3:
    // while (jobNum > 0) {
    //     // 1000 space => maxHeap    
    //     // add to res

    //     // vector erase take ==> jobs->-1

    //     // jobNum

    // }

    // modify in-place
    // vector<int> res3, res2, res1;

    // int num_high jobs, num_mid jobs, num_low
    // time O(n), o(1)  => two passes
    
    // one pass?? 
    // pseudo code:

    // step 1: search from the begining to find a job that is not hight prri
    // jobi == mid, then
    // step 2: search from the end to find a higpro job (jobj)
    // step 3: swap(jobi, jobj)

    // job1 == low, swap(jobi, an)

}


vector<int> nums = {3, 3, 2, 1, 3, 2, 1, 1, 1, 3, 2, 3, 1}
Output ==>  nums = {3, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1}
Requirement: Time O(N), should be only one pass, not two passes!
             Modify in-place


// 75. Sort Colors
// Input: nums = [2,0,2,1,1,0]; Output: [0,0,1,1,2,2]
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, cur = 0, right = nums.size() - 1;
        while (cur <= right) {
            if (nums[cur] == 0) {
                swap(nums[left++], nums[cur++]); // NOTE, cur++
            }
            else if (nums[cur] == 2) {
                swap(nums[right--], nums[cur]); // NOTE, cur
            }
            else {
                cur++;
            }
        }
    }
};












