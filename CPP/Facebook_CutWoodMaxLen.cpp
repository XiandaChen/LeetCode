/*
Given an int array wood representing the length of n pieces of wood and an int k. 
It is required to cut these pieces of wood such that more or equal to k pieces of the same length len are cut. 
What is the longest len you can get?
*/

// ref. Q875. Koko Eating Bananas, Binary Search
int cutWoodMaxLen(vector<int> & woods, int k) {
    int left = 1, right = *max_element(woods.begin(), woods.end()); // #include <algorithm>
    while (left < right) {
        int mid = left + (right - left) / 2, cnt = 0;
        for (int wood : woods) {
            cnt += wood / mid; // num of pieces when cutting wood in lenght of mid
        }
		// increasing piece length
        if (cnt > k) left = mid + 1;  // error: if (cnt >= k)
        else right = mid;
    } 
    return right;
}


/*
cpp.sh test:

int main()
{
    vector<int> woods = {5, 9, 7};
    
    cout << "k = 1: " << cutWoodMaxLen(woods, 1) << endl;
    cout << "k = 3: " << cutWoodMaxLen(woods, 3) << endl;
    cout << "k = 4: " << cutWoodMaxLen(woods, 4) << endl;
 
    return 0;
}
*/
































