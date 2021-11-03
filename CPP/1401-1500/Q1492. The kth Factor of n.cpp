class Solution {
public:
    int kthFactor(int n, int k) {
        vector<int> factors;
        int sqrtN = (int) sqrt(n);
        for (int i = 1; i <= sqrtN; i++) { // O(sqrt(N))
            if (n % i == 0) {
                factors.push_back(i);
                k--;
                if (k == 0) return i;
            }
        }
        // if n is perfect square, skip duplicate in factors
        // n=16,k=5: 1, 2, 4, 8, 16
        // factors=[1, 2, 4] , k=(5-3)+1=3, [nDiv - k]=[0]
        if (sqrtN * sqrtN == n) k++;
        int nDiv = factors.size();
        return (k <= nDiv) ? n / factors[nDiv - k] : -1;
        
        // for (int i = 1; i <= n; i++) { // O(N)
        //     if (n % i == 0) k--;
        //     if (k == 0) return i;
        // }
        // return -1;
    }
};

