// Q1: merge two strings
// Input: s = "aaaaa", t = "bbb"; Output: mergeString(s,t)="abababaa"
string mergeString(string s, string t) {	
	int n = s.size(), m = t.size(), i = 0;
	string res = "";
	
	while (0 < n && 0 < m) {
		res += s[i];
		res += t[i];
		++i; --n; --m;
	}
	
	while (0 < n) {
		res += s[i];
		++i; --n;
	}
	
	while (0 < m) {
		res += t[i];
		++i; --m;
	}
	
	return res;
}

// Q2: check if it is cyclic shift
// Input: numbers=[3,4,1,2]; Output: True, since after shifting, we can get [1,2,3,4]
// Input: numbers=[3,2,1,5,4]; Output: True, since after shifting, we can get [5,4,3,2,1]
// Input: numbers=[3,1,4,2]; Output: False, 
// 	since all shift [[3,1,4,2], [2,3,1,4], [4,2,3,1], [1,4,2,3]] are not monotone increasing or decreasing
bool cyclicShift (vector<int> numbers) {
	int n = numbers.size();
	// increasing
	if (numbers[0] < numbers[1]) {
		int i = 1;
		while (i < n && numbers[i - 1] < numbers[i]) ++i;
		
		if (i == n) return true;
		
		++i; 
		while (i < n && numbers[i - 1] < numbers[i]) ++i;
		
		return (i == n) && (numbers[0] > numbers[n - 1]);
	}
	else {
		int i = 1;
		while (i < n && numbers[i - 1] > numbers[i]) ++i;
		
		if (i == n) return true;
		
		++i; 
		while (i < n && numbers[i - 1] > numbers[i]) ++i;
		
		return (i == n) && (numbers[0] < numbers[n - 1]);
	}
	return false;
}


// Q3: fill cell with replacement
// check if matrix t can be inserted into matrix s
// matrix includes '.' being available and '*' being obstacle,
// t can be inserted to s if only if not '*' in t is overlapped with '*' in s,
// at most k '*' in s are allowed to changed to be '.'.
// return the upper left indics, if more available then return the leftmost one
// Input: s=[['.', '*', '.', '.']		t=[['*', '*', '*']  k=1;  Output: indics <0,0>
//			 ['.', '*', '.', '.']		   ['*', '.', '*']
// 			 ['*', '.', '.', '*']]


// Q4: longest subarray, such that -diff <= numbers[i+1] - numbers[i] <= diff
// Input: numbers=[-1,4,6,2,8,4,7,12], diff=5; Output: indics <0, 3>
// Input: numbers=[33,13,15,22,29,26,3,7], diff=4; Output: indics <1, 2>
vector<int> longestDiffSubarray(vector<int> numbers, int diff) {
	int n = numbers.size();
	int i = 0, j = 1, maxI = 0, maxJ = 0, maxLen = -1;
	
	while (j < n) {
	    if ((-diff <= numbers[j] - numbers[j - 1]) 
        && (numbers[j] - numbers[j - 1] <= diff)) {
            int curLen = j - i + 1;
            if (curLen > maxLen) {
                maxLen = curLen;
                maxI = i;
                maxJ = j;
            }
            ++j;
        }
        else {
            i = j; 
            ++j;
        }
	}
	
	return {maxI, maxJ};
}


















