class Solution {
public:
    int countPrimes(int n) {
        int res = 0;
        vector<bool> prime(n, true);
        
        // prime 2: remove 4,6,8,10,...
        // prime 3: remove 6,9,12,15,...
        for (int i = 2; i < n; i++) {
            if (!prime[i]) continue; // i is not prime, and removed prviously
            res++;
            for (int j = 2; i * j < n; j++) {
                prime[i * j] = false;  // j times i is not a prime
            }
        }
        
        return res;
    }
};