/*
Given boolean array of days at work, [T, F, T, T, F, F, F, T] and pto (number of PTOs one can take) - 
where boolean T means paid holiday and F means you can take a PTO. 

Find the maximum length of vacation an employee can take.
*/

// ref. Q1004, sliding window 
int maxVacation(vector<bool> & days, int ptos) {
	int left = 0, numFalse = 0, res = 0;
	// count num of F within sliding window [left, right]
	for (int right = 0; right < days.size(); ++right) {
		if (!days[right]) ++numFalse;
		// shift the window to right if numFalse > ptos
		while (numFalse > ptos){
			if (!days[left++]) --numFalse; 
		}
		// update the length of maximum vacation
		res = max(res, right - left + 1);
	}
	return res;
}

/*
int main () {
    vector<bool> A = {true, false, true, true, false, false, false, true};
    vector<bool> B = {false, true, true, true, false, true, true, true, true};
    vector<bool> C = {false, true, true, true,  false, true, true, false};
    
    cout << "A: " << maxVacation(A, 2) << endl;
    cout << "B: " << maxVacation(B, 2) << endl;
    cout << "C: " << maxVacation(C, 2) << endl;
    
    return 0;
}
*/