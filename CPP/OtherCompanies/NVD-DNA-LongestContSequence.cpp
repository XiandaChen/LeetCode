//################# 1. ####################//
/* 
DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG Task.
1 . Generate random DNA sequences for a seq length
2. Use the generated sequence and write a function to 
find all the 10-letter-long sequences (substrings) that occur more than once in a DNA
*/
// What if the input data is a long data stream, that's "unordered_set<string> st;" may lead to memory overflow?
// Solution: encoding substring using 2-bit for each A (00), C(01), G(10), and T(11), then 
// the 10-letter-long substring (e.g., "ACGAATTCCG", each char takes 8bit, total 80bits) 
// can be encoded as "000110001111010110" (2bit for each letter), then 
// converted this 20-bit binary as a int number (i.e., 32bit), thus we save space (1 - 32/80)=60%.

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <unordered_set>

using namespace std; // string

// random: A, C, G, T
// each position of string, rand()%4 => A, C, G, T
// encoding A(0), C(1), G(2), T(3) => numerical
string randomGenerate(int len) { 
  string res = "";
  
  for (int i = 0; i < len; i++) {
    int r = rand() % 4; // 0, 1, 2, 3
    
    switch (r) {
      case 0: res += 'A'; break;
      case 1: res += 'C'; break;
      case 2: res += 'G'; break;
      case 3: res += 'T'; break;
    }
  }
  
  return res;
}

vector<string> occurMoreThanOnce (string & s) {
  // corner case
  if ((int)s.size() <= 10) return {""};
  
  unordered_set<string> st; // record the previous substring
  
  vector<string> res;
  
  // move window of 10-letter 
  // add the substring into res, if it occur before
  int n = (int)s.size(), i = 0;
  while (i + 10 < n) {
    string str = s.substr(i, 10);
    
    if (st.count(str)) {
      res.push_back(str); // occur than once
    }
    else {
      st.insert(str); // first occurence
    }
    
    i++;
  }
  
  return res;
}

int main() {
  
  string str = randomGenerate(10000);
  
  vector<string> res = occurMoreThanOnce(str);
  
  for (int i = 0; i < (int)res.size(); i++) {
    cout << res[i] << " ";
  }
  
  cout << endl;
  
  return 0;
}


//################# 2. ####################//
// design a class that offers two public functions/methods, 
// AddNumber(int num): return void
// LongestConsecutive(): return the length of the longest consecutive element sequence 
// from the number num that were added by AddNumber(int num).

// e.g. 
// LongestConvsecutive() Output: 0
// AddNumber(1)
// AddNumber(2)
// LongestConvsecutive() Output: 2
// AddNumber(4)
// LongestConvsecutive() Output: 2
// AddNumber(3)
// LongestConvsecutive() Output: 4

// 128. Longest Consecutive Sequence
// Input: nums = [100,4,200,1,3,2]; Output: 4
// Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. 
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int res = 0;
        unordered_set<int> s(nums.begin(), nums.end());
        for (int val : nums) {
            if (!s.count(val)) continue;
            s.erase(val);
            int pre = val - 1, next = val + 1;
            while (s.count(pre)) s.erase(pre--);
            while (s.count(next)) s.erase(next++);
            res = max(res, next - pre  - 1);
        }
        return res;
    }
};







































