// Jumping Numbers
// Given a positive int n, get jumping numbers smaller than or equal to n. 
// A number is called a jumping number if all adjacent digits in it differ by 1.
// For example, 8987 and 4343456 are jumping numbers, but 796 and 89098 are not. 
// All single digit numbers are considered as jumping numbers.
// Input: 105
// Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 21, 23, 32, 34, 43, 45, 54, 56, 65, 67, 76, 78, 87, 89, 98, 101]
// O(k), where k is number of Jumping Numbers smaller than or equal to x
void dfs(int k, int num, set<int>& st) {
    if (num > k) return;
    if (st.count(num)) return;
    st.insert(num);
    int last_digit = num % 10;
    if (last_digit == 0) {
        dfs(k, num * 10 + (last_digit + 1), st);
    }
    else if (last_digit == 9) {
        dfs(k, num * 10 + (last_digit - 1), st);
    }
    else {
        dfs(k, num * 10 + (last_digit + 1), st);
        dfs(k, num * 10 + (last_digit - 1), st);
    }
}
vector<int> jumpingNumber(int n) {
    set<int> st;
    for (int i = 0; i < 10; ++i) {
        dfs(n, i, st);
    }

    vector<int> res(st.begin(), st.end());

    return res;
}

// Given a string S, returns the maximum number of letters a 
// that can be inserted into S (including at the front and end of S) 
// so that the resulting string doesn’t contain three consecutive letters a. 
// If string S already contains the substring aaa, then your function should return -1.
// Input: aabab; Output: 3; Explanation: A string aabaabaa can be made
int numInserts(string s) {
    // all chars in s are not 'a', then 2*(n+1), that is, in general
    // 2 * (number of possible places to insert + 1) — number of found As.
    int numA = 0, nonA = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a') {
            ++numA;
        }
        else {
            ++nonA;
            numA = 0; // new start
        }
        
        if (numA == 3) return -1;
    }
    
    return 2 * (nonA + 1) - (n - nonA);
}

// The smallest number with given digit sum s and number of digits d? 
// Input : s = 9, d = 2; Output : 18
// Input: s = 20, d = 3; Output : 299
int findSmallest(int d, int s) {
    if (s == 0)
        return (d == 1) ? 0 : -1;
    if (s > 9*d)
        return -1; // not feasible 
 
    // Create an array to store digits of result
    int res[d];
 
    // deduct sum by one to account for cases later
    // (There must be 1 left for the most significant digit)
    s -= 1;
 
    // Fill last d-1 digits (from right to left)
    for (int i = d-1; i > 0; --i) {
        // If sum is still greater than 9,
        // digit must be 9.
        if (s > 9) {
            res[i] = 9;
            s -= 9;
        }
        else {
            res[i] = s;
            s = 0;
        }
    }
 
    // Whatever is left should be the most significant digit
    res[0] = s + 1;  // The initially subtracted 1 is incorporated here.
 
    int val = 0;
    for (int i = 0; i < d; ++i)
        val = val * 10 + res[i];
        
    return val;
}

// wanshu: 6 = 1+2+3
#include "stdio.h"
int main(){
 static int k[10];
 int i,j,n,s;
 for(j=2;j<1000;j++)
 {
  n=-1;
  s=j;
  for(i=1;i<j;i++)
  {
   if((j%i)==0)
   { 
    n++;
    s=s-i;
    k[n]=i;
   }
  }
  if(s==0)
  {
   printf("%d is a wanshu: ",j);
   for(i=0;i<n;i++)
    printf("%d,",k[i]);
   printf("%d\n",k[n]);
  }
 }}

// 10. Regular Expression Matching
// Given an input string (s) and a pattern (p), 
// implement regular expression matching with support for '.' and '*'
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.size() == 0) 
            return (s.size() == 0);
        
        if (p.size() == 1) 
            return ((s.size() == 1) && (p[0] == '.' || p[0] == s[0]));
        
        if (p[1] != '*') {  // recurse searching until 2nd char in p is *
            if (s.size() == 0) 
                return false;
            return ((p[0] == '.' || p[0] == s[0]) && isMatch(s.substr(1), p.substr(1)));
        }
        
        while (s.size() != 0 && (p[0] == '.' || p[0] == s[0])) {
            if (isMatch(s, p.substr(2)))    // if true when remove first two char in p
                return true;
            s = s.substr(1);    // else, remove first char is and then recurse
        }
        
        return isMatch(s, p.substr(2));
    }
};
