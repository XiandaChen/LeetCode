#include <cstdio>
#include <ctime>

// ####################### 1. Prime ########################################
bool prime(int n) {
    // for (int i = 2; i < n; i++) {  // time: 1.863second
    for (int i = 2; i * i <= n; i++) { // time: 0.001second, 10,000000 => 3000
         
         // n/i == integer ==> dividable
        if (n % i == 0) {
            return false;  // dividable , not prime
        }
        
        // for (int j = 2; i * j < n; j++) {  // time: O(n^2)
        //     if (i * j == n) return true;
        // }
    }
    
    return true;
}

int main() {
    int start = 10000000;
    int stop = 10001000;
    clock_t begin = clock();
    for (int i=start; i <= stop; i++) {
        if (prime(i)) {
            printf("%d\n", i);
        }
    }
    printf("Time = %.3f seconds\n", double(clock() - begin)/CLOCKS_PER_SEC);
}

// 204. Count Primes (check each number can be TLE, e.g., n=50000)
// Input: n = 10; Output: 4
// Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
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

// ###############################################################
1) Want to multiply 1K x 1K FP32 matrices on a GPU that can do 521 FP32 FMA
operations per cycle, running at 2 GHz. What is the memory bandwidth needed
to keep the GPU busy?
==> number of multiply operations for each cell in result matrix: 1K;
	there are 1K x 1K cells in result matrix, then, 
	total FMA openrations: 1K x 1K x 1K = 1G
==> total cycles: 1G / 512 = 2M
==> time used: 2M / 2GHz = 0.001 sec = 1ms
==> bandwidth to keep GPU busy (data/time): (1K x 1K x 2 x 4Byte) / 1ms = 8 GB/s

What if 2K x 2K matrices?
==> total FMA openrations: 2K x 2K x 2K = 8G
==> total cycles: 8G / 512 = 16M
==> time used: 16 / 2GHz = 0.008 sec = 8ms
==> bandwidth to keep GPU busy (data/time): (2K x 2K x 2 x 4Byte) / 8ms = 4 GB/s


2) Have a 64KB cache with 64B line size. If it's 4-way set associative and 
I have a 32-bit address, how will access this cache to get a 4-byte word using this address.
==> Address (32-it):   [X-bit tag] + [Y-bit index] + [Z-bit offset]
==> 1). Z-bit offset = log2(64) = 6
==> Number of cache lines: 64KB / 64B = 1K
==> Number of sets: 1K / 4 = 256 
==> 2). Y-bit index = log2(256) = 8
==> 3). X-bit tag = 32 - 8 - 6 = 18

Access the cache: 
查找时按照中间的8位index确定在哪个组/set，
然后比较最高18位确定是哪一路（共4路），
取出整个cache line以后按照offset访问具体的byte


3) While running an ML model on 8-GPU DGX system, we see that overall GPU utilization = 10%.
How would you go about debugging what the issues might be.
(Tools you would use, hypotheses you would come up with, testing those hypotheses etc).




























